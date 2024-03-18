/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_cmd_table_setup.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 23:59:56 by lyeh              #+#    #+#             */
/*   Updated: 2024/02/17 23:59:57 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	setup_simple_cmd(t_shell *shell, t_list *simple_cmd_list)
{
	t_list		*expanded_list;
	int			ret;

	expanded_list = NULL;
	ret = expand_list(shell, simple_cmd_list, &expanded_list,
			E_EXPAND | E_SPLIT_WORDS | E_RM_QUOTES);
	if (ret != SUCCESS)
		return (ft_lstclear(&expanded_list, free), ret);
	shell->final_cmd_table->simple_cmd = \
		convert_list_to_string_array(expanded_list);
	ft_lstclear(&expanded_list, free);
	if (!shell->final_cmd_table->simple_cmd)
		return (MALLOC_ERROR);
	return (SUCCESS);
}

bool	setup_exec_path(t_final_cmd_table *final_cmd_table)
{
	if (!final_cmd_table->simple_cmd || \
		!final_cmd_table->simple_cmd[0] || \
		is_builtin(final_cmd_table->simple_cmd[0]))
		final_cmd_table->exec_path = NULL;
	else if (!set_exec_path(&final_cmd_table->exec_path,
			final_cmd_table->simple_cmd[0], final_cmd_table->env))
		return (false);
	return (true);
}

bool	setup_assignment_array(
			t_final_cmd_table *final_cmd_table,
			t_list *assignment_list)
{
	final_cmd_table->assignment_array = NULL;
	if (!assignment_list)
		return (true);
	final_cmd_table->assignment_array = \
		convert_list_to_string_array(assignment_list);
	if (!final_cmd_table->assignment_array)
		return (false);
	return (true);
}

bool	setup_env(t_final_cmd_table *final_cmd_table, t_list *env_list)
{
	t_env	*env_node;
	char	*tmp;
	int		i;

	final_cmd_table->env = (char **)malloc(
			(get_exported_env_size(env_list) + 1) * sizeof(char *));
	if (!final_cmd_table->env)
		return (false);
	i = 0;
	while (env_list)
	{
		env_node = (t_env *)env_list->content;
		if (env_node->export && env_node->value)
		{
			tmp = (char *)malloc((ft_strlen(env_node->key) + 1 + \
					ft_strlen(env_node->value) + 1) * sizeof(char));
			if (!tmp)
				return (free_array(&final_cmd_table->env), false);
			sprintf(tmp, "%s=%s", env_node->key, env_node->value);
			final_cmd_table->env[i++] = tmp;
		}
		env_list = env_list->next;
	}
	final_cmd_table->env[i] = NULL;
	return (true);
}

void	setup_fd(
	t_shell *shell, t_final_cmd_table *final_cmd_table)
{
	final_cmd_table->read_fd = STDIN_FILENO;
	final_cmd_table->write_fd = STDOUT_FILENO;
	if (*shell->old_pipe.read_fd != -1)
		final_cmd_table->read_fd = *shell->old_pipe.read_fd;
	if (*shell->old_pipe.write_fd != -1)
		final_cmd_table->write_fd = *shell->old_pipe.write_fd;
}
