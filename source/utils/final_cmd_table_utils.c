/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_cmd_table_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:02:02 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/23 04:06:48 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "defines.h"
#include "utils.h"
#include "expander.h"
#include "debug.h"
#include "signals.h"

bool	expand_simple_cmd(t_shell *shell, t_list *simple_cmd_list)
{
	t_list		*expanded_list;
	int			ret;

	expanded_list = NULL;
	ret = expand_list(
			shell, simple_cmd_list, &expanded_list, E_EXPAND | E_RM_QUOTES);
	if (ret == MALLOC_ERROR)
		return (ft_lstclear(&expanded_list, free), false);
	else if (ret == BAD_SUBSTITUTION)
		ft_lstclear(&expanded_list, free);
	shell->final_cmd_table->simple_cmd = \
		convert_list_to_string_array(expanded_list);
	ft_lstclear(&expanded_list, free);
	if (!shell->final_cmd_table->simple_cmd)
		return (false);
	return (true);
}

bool	setup_simple_cmd(t_shell *shell, t_list *simple_cmd_list)
{
	if (!expand_simple_cmd(shell, simple_cmd_list))
		return (false);
	return (true);
}

bool	setup_exec_path(t_final_cmd_table *final_cmd_table)
{
	if (is_builtin(final_cmd_table->simple_cmd[0]) || \
		!final_cmd_table->simple_cmd[0]) //? What if it will expand to nothing and only the next word is a builtin?
	{
		final_cmd_table->exec_path = NULL;
		return (true);
	}
	final_cmd_table->exec_path = get_exec_path(
			final_cmd_table->simple_cmd[0], final_cmd_table->envp);
	if (!final_cmd_table->exec_path)
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

int	get_envp_size(t_list *env_list)
{
	t_env	*env_node;
	int		size;

	size = 0;
	while (env_list)
	{
		env_node = (t_env *)env_list->content;
		if (env_node->export && env_node->value)
			size++;
		env_list = env_list->next;
	}
	return (size);
}

bool	setup_env(t_final_cmd_table *final_cmd_table, t_list *env_list)
{
	t_env	*env_node;
	char	*tmp;
	int		i;

	final_cmd_table->envp = (char **)malloc(
			(get_envp_size(env_list) + 1) * sizeof(char *));
	if (!final_cmd_table->envp)
		return (false);
	i = 0;
	while (env_list)
	{
		env_node = (t_env *)env_list->content;
		if (env_node->export && env_node->value)
		{
			tmp = (char *)malloc((ft_strlen(env_node->key) + 1
						+ ft_strlen(env_node->value) + 1) * sizeof(char));
			if (!tmp)
				return (free_array(&final_cmd_table->envp), false);
			sprintf(tmp, "%s=%s", env_node->key, env_node->value);	// TODO: This is really dangerous, bc the user could set a very long key or value and go beyond the memory of size PATH_MAX.
			final_cmd_table->envp[i++] = tmp;
		}
		env_list = env_list->next;
	}
	final_cmd_table->envp[i] = NULL;
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

void	free_final_cmd_table(t_final_cmd_table **final_cmd_table, bool close_fd)
{
	if (!final_cmd_table || !*final_cmd_table)
		return ;
	free_array(&(*final_cmd_table)->envp);
	free_array(&(*final_cmd_table)->simple_cmd);
	free((*final_cmd_table)->exec_path);
	free_array(&(*final_cmd_table)->assignment_array);
	if (close_fd)
	{
		safe_close(&(*final_cmd_table)->read_fd);
		safe_close(&(*final_cmd_table)->write_fd);
	}
	ft_free_and_null((void **)final_cmd_table);
}

bool	set_final_cmd_table(t_shell *shell, t_cmd_table *cmd_table)
{
	free_final_cmd_table(&shell->final_cmd_table, false);
	shell->final_cmd_table = ft_calloc(1, sizeof(t_final_cmd_table));
	if (!shell->final_cmd_table || \
		!setup_env(shell->final_cmd_table, shell->env_list) || \
		!setup_simple_cmd(shell, cmd_table->simple_cmd_list) || \
		!setup_exec_path(shell->final_cmd_table) || \
		!setup_assignment_array(
			shell->final_cmd_table, cmd_table->assignment_list))
		return (false);
	setup_fd(shell, shell->final_cmd_table);
	return (true);
}
