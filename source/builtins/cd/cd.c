/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 21:05:20 by codespace         #+#    #+#             */
/*   Updated: 2024/01/20 20:47:08 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * [x] 1. If no directory arg given and HOME not set, undefined behavior. - (Error message)
 *
 * [x] 2. If no directory arg given and HOME is set to non-empty value, behave like HOME was given as arg.
 *
 * [ ] 3. If arg begins with ˋ/ˋ, ...
 *
 * [ ] 4. If ?first component? of arg is ˋ.ˋ or ˋ..ˋ, ...
 *
 * [ ] 5. Do CDPATH checks. (OPTIONAL)
 *
 * [ ] 6. Set curpath to directory
 *
 * [ ] 7. If curpath does not begin with ˋ/ˋ, concatenate curpath with PWD, optionally a ˋ/ˋ if needed, and curpath.
 *
 * [ ] 8. CONVERSION
 * 		[x] a. Delete dot components and ALL their slash characters following them.
 * 		[x] b. For all dot-dot components that are not preceded by root or dot-dot:
 * 			[x] i. If the preceding component is not a directory (like a file), display `%s: Not a directory`, and stop.
 * 			[x] ii. Simplify dot-dots by deleting them if they have a preceding component.
 *
 * [ ] 9. PATH_MAX considerations and conversion
 *
 * [ ] 10. Execute with chdir(curpath).
*/

/*
 * TODO:
 *
 * [ ] Permission checks!
 * [ ] Add ft_strstr to libft.
 * [ ] Move replace_part_of_str() to libft.
 * [ ] Test cd with symbolic links, especially for step 8.b.i.
 * [ ] Implement `cd -` (change to previous directory - get the value from OLDPWD).
 *     If OLDPWD is not set, print "<PROGRAM_NAME>: cd: OLDPWD not set".
*/

/*
 * ERRORS:
 *
 * [x] ˋbash: cd: too many argumentsˋ - If more than one argument.
 * [x] ˋbash: cd: <argument>: No such file or directoryˋ
*/

#include "cd.h"
#include "clean.h"
#include "minishell.h"
#include "utils.h"

#include "expander.h"	// Move replace_part_of_str() to utils or libft

int	ft_exec_cd(char **args, t_list **env_list)
{
	char	*curpath;
	char	*directory;
	char	*pwd;

	if (get_array_len(args) > 2)
		return (ft_dprintf(2, ERROR_CD_TOO_MANY_ARGS, PROGRAM_NAME), MISUSE_BUILTIN);

	// Steps 1 and 2
	if (!args[1])
	{
		directory = get_value_from_env(*env_list, "HOME");
		if (!directory)
			return (ft_dprintf(2, ERROR_CD_HOME_NOT_SET, PROGRAM_NAME), MISUSE_BUILTIN);
	}
	else
		directory = args[1];
	//! BUG: If the argument is "" (empty string), it still does sth bc it should move PWD to OLDPWD (PWD will stay the same bc the directory won't be changed).
	// if (!*directory)	// Should probably better resolve during the flow
	// 	return (EXIT_SUCCESS);	//TODO: Test if it should still update the env variables.

	// Step 3 and 4
	if (directory[0] == '/' || is_dot_component(directory))
		curpath = directory;

	// Step 5
	// CDPATH

	// Step 6
	curpath = directory;

	curpath = ft_strdup(directory);
	if (!curpath)
		return (GENERAL_ERROR);

	// Step 7
	// pwd = get_value_from_env(*env_list, "PWD");
	pwd = getcwd(NULL, 0);
	if (!pwd)	// In my tests so far it seems to get it from getcwd(). F.e. if I modify PWD manually to anything else, it still gets the current directory.
		return (free(curpath), MISUSE_BUILTIN); //! How to differentiate in builtins between malloc errors and more harmless errors?
	// pwd = ft_strdup(pwd);
	// if (!pwd)
	// 	return (free(curpath), GENERAL_ERROR);

	t_list_d	*cmpnt_list;
	t_list_d	*tmp_list;

	cmpnt_list = NULL;
	if (!is_absolute_path(curpath))
	{
		cmpnt_list = create_component_list(pwd);
		if (!cmpnt_list)
			return (free(pwd), GENERAL_ERROR);
	}
	tmp_list = create_component_list(curpath);
	free(curpath);
	if (!tmp_list)
		return (ft_lstclear_d(&cmpnt_list, free), free(pwd), GENERAL_ERROR);
	ft_lstadd_back_d(&cmpnt_list, tmp_list);

	// Step 8
	// if (!remove_dotslash(&curpath))
	// 	return (free(curpath), free(pwd), free(tokenized_path), ft_lstclear_d(cmpnt_list, NULL), GENERAL_ERROR);
	rm_dot_cmpnts(&cmpnt_list);
	int ret = rm_dotdot_cmptnts(&cmpnt_list, directory);
	if (ret != SUCCESS)
		return (ft_lstclear_d(&cmpnt_list, free), free(pwd), ret);

	// Step 9
	// Convert curpath to relative pathname
	char	*final_path;
	final_path = convert_cmpnt_list_to_path(cmpnt_list);
	ft_lstclear_d(&cmpnt_list, free);
	if (!final_path)
		return (free(pwd), GENERAL_ERROR);
	char	*new_pwd;
	new_pwd = ft_strdup(final_path);
	if (!new_pwd)
		return (free(final_path), free(pwd), GENERAL_ERROR);
	if (is_absolute_path(pwd) && is_absolute_path(final_path))
	{
		final_path = try_to_convert_absolute_to_relative_path(final_path, pwd);
		if (!final_path)
			return (free(new_pwd), free(pwd), GENERAL_ERROR);
	}
	free(pwd);

	// Step 10
	printf("final_path: %s\n", final_path);
	if (*final_path)
		if (chdir(final_path) == -1)
			return (ft_dprintf(STDERR_FILENO, "%s: cd: %s: ", PROGRAM_NAME, directory), perror(NULL), free(new_pwd), free(final_path), MISUSE_BUILTIN);	//? Not sure if "chdir: " or not.
	free(final_path);

	// Update PWD and OLDPWD
	// Even just a dot should update OLDPWD
	// I have to use PWD as a reference for OLDPWD, even if it is unset. That's the behaviour of bash.
	// If PWD does not exist, now OLDPWD should not exist anymore.
	// Just cd also updates OLDWD.
	//TODO: PWD should always be canonical, meaning no dot components.
	if (!update_pwd_env(env_list, new_pwd))
		return (free(new_pwd), GENERAL_ERROR);
	return (EXIT_SUCCESS);
}


/* NOT USED AT THE MOMENT */

bool	path_has_trailing_slash(char *path)
{
	if (!path || !*path)
		return (false);
	return (path[ft_strlen(path) - 1] == '/');
}

char	*get_ptr_to_last_cmpnt(char *path)
{
	size_t	i;

	i = ft_strlen(path);
	while (i > 0 && path[i - 1] != '/')
		i--;
	return (&path[i]);
}

bool	reduce_multi_slash(char **str, size_t index)
{
	size_t	rmv_len;

	if (ft_strncmp(&(*str)[index], "//", 2) != 0)
		return (true);
	rmv_len = 2;
	while ((*str)[index + rmv_len] == '/')
		rmv_len++;
	if (!replace_part_of_str(str, "/", index, rmv_len))
		return (false);
	return (true);
}
