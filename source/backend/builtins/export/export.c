/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:41:38 by lyeh              #+#    #+#             */
/*   Updated: 2024/03/18 17:41:39 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export.h"
#include "utils.h"

static bool	handle_var_export(char *str, t_list **env_list);
static void	change_export_flag(t_list *env_list, char *key, t_expt export);

int	exec_export(char *args[], t_list **env_list)
{
	int	i;
	int	ret;

	if (get_array_len(args) < 2)
		return (print_exported_env(*env_list));
	ret = SUCCESS;
	i = 1;
	while (args[i])
	{
		if (!is_valid_varname(args[i]))
		{
			ft_dprintf(STDERR_FILENO, ERROR_EXPORT_INVALID_IDENTIFIER,
				PROGRAM_NAME, args[i]);
			ret = GENERAL_ERROR;
		}
		else if (!handle_var_export(args[i], env_list))
			return (BUILTIN_ERROR);
		i++;
	}
	return (ret);
}

static bool	handle_var_export(char *str, t_list **env_list)
{
	char	*key;
	char	*old_value;
	char	*value;

	if (!extract_env_key(&key, str))
		return (false);
	if (is_key_in_env_list(*env_list, key))
	{
		if (!extract_env_value(&value, str))
			return (free(key), false);
		if (value && replace_env_value(*env_list, key, value, &old_value))
			free(old_value);
		change_export_flag(*env_list, key, EXPORT_YES);
		free(key);
	}
	else
	{
		free(key);
		if (!process_str_to_env_list(str, env_list, EXPORT_YES))
			return (false);
	}
	return (true);
}

static void	change_export_flag(t_list *env_list, char *key, t_expt export)
{
	t_env	*env_node;

	while (env_list)
	{
		env_node = env_list->content;
		if (ft_strcmp(env_node->key, key) == 0)
		{
			env_node->export = export;
			return ;
		}
		env_list = env_list->next;
	}
}
