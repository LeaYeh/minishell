/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 21:05:20 by codespace         #+#    #+#             */
/*   Updated: 2024/01/26 02:35:16 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * [x] 1. If no directory arg given and HOME not set, undefined behavior. - (Error message)
 *
 * [x] 2. If no directory arg given and HOME is set to non-empty value, behave like HOME was given as arg.
 *
 * [x] 3. If arg begins with ˋ/ˋ, ...
 *
 * [x] 4. If ?first component? of arg is ˋ.ˋ or ˋ..ˋ, ...
 *
 * [ ] 5. Do CDPATH checks. (OPTIONAL)
 *
 * [x] 6. Set curpath to directory
 *
 * [x] 7. If curpath does not begin with ˋ/ˋ, concatenate curpath with PWD, optionally a ˋ/ˋ if needed, and curpath.
 *
 * [x] 8. CONVERSION
 * 		[x] a. Delete dot components and ALL their slash characters following them.
 * 		[x] b. For all dot-dot components that are not preceded by root or dot-dot:
 * 			[x] i. If the preceding component is not a directory (like a file), display `%s: Not a directory`, and stop.
 * 			[x] ii. Simplify dot-dots by deleting them if they have a preceding component.
 *
 * [x] 9. PATH_MAX considerations and conversion
 *
 * [x] 10. Execute with chdir(curpath).
*/

/*
 * TODO:
 *
 * [x] Implement `cd -` (change to previous directory - get the value from OLDPWD).
 *     If OLDPWD is not set, print "<PROGRAM_NAME>: cd: OLDPWD not set".
 * [ ] Permission checks!
 * [ ] Add ft_strstr to libft.
 * [ ] Move replace_part_of_str() to libft.
 * [ ] Test cd with symbolic links, especially for step 8.b.i.
 * [ ] Test inside a directory that then got deleted from another shell.
*/

/*
 * ERROR MESSAGES:
 *
 * [x] ˋbash: cd: too many argumentsˋ - If more than one argument.
 * [x] ˋbash: cd: <argument>: No such file or directoryˋ
*/

/*
 * BUGS:
 *
// //  * [x] We decided to leave it like that, bash non-POSIX also does it this way, and it makes more sense and seems safer from a security perspective.
//  *     If the current directory got all its permissions removed and the argument is for a subdirectory, the error message is incorrect:
//  *     It should be:	"cd: <subdir-name>: Not a directory".
//  *     But it is:		"cd: <subdir-name>: Permission denied".
 *
// //  * [x] If the current directory got all its permissions removed and the argument is "" (an empty string), the error message is incorrect:
//  *     It should be:	"cd: : Permission denied".
//  *     But it is:		"cd: : No such file or directory".
 *
 * [ ] If inside a directory that gets deleted, my cd never recovers bc it always tries to get the pwd from getcwd().
*/

/*
 * NAME_MAX = 255
 * PATH_MAX = 4096
*/

#include "cd.h"
#include "clean.h"
#include "minishell.h"
#include "utils.h"

int	exec_cd(char **args, t_list **env_list)
{
	char	*final_path;
	char	*new_pwd;
	int		ret;
	char	*target_dir;

	target_dir = get_target_dir(args, *env_list);
	if (!target_dir)
		return (MISUSE_BUILTIN);
	if (!is_abs_path(target_dir) && !is_dot_cmpnt(target_dir))
		// Do step 5 - check CDPATH env variable
		(void)NULL;
	ret = set_final_path(&final_path, &new_pwd, target_dir);
	if (ret != SUCCESS)
		return (ret);
	printf("final_path: %s\n", final_path);
	if (chdir(final_path) == -1)
		return (free(final_path), free(new_pwd),
			handle_chdir_error(errno, target_dir));
	free(final_path);
	if (!update_pwd_env(env_list, new_pwd))
		return (free(new_pwd), GENERAL_ERROR);
	if (args[1] && ft_strcmp(args[1], "-") == 0)
		ft_printf("%s\n", new_pwd);
	return (EXIT_SUCCESS);
}
