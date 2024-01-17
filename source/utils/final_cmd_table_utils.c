/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_cmd_table_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:02:02 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/12 13:14:20 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "defines.h"
#include "utils.h"

bool	setup_cmd_name(
	t_final_cmd_table *final_cmd_table, t_cmd_table *cmd_table)
{
	char	*exec_path;

	if (!cmd_table->cmd_name)
		return (true);
	final_cmd_table->cmd_name = ft_strdup(cmd_table->cmd_name);
	if (!final_cmd_table->cmd_name)
		return (false);
	if (is_builtin(final_cmd_table->cmd_name))
		return (true);
	exec_path = get_exec_path(final_cmd_table->cmd_name, final_cmd_table->envp);
	if (!exec_path)
		return (false);
	free(final_cmd_table->cmd_name);
	final_cmd_table->cmd_name = exec_path;
	return (true);
}

bool	setup_cmd_args(t_final_cmd_table *final_cmd_table, t_list *args_list)
{
	final_cmd_table->cmd_args = NULL;
	if (!args_list || ft_lstsize(args_list) == 0)
		return (true);
	final_cmd_table->cmd_args = convert_list_to_string_array(args_list);
	if (!final_cmd_table->cmd_args)
		return (false);
	return (true);
}

bool	setup_assignment(
	t_final_cmd_table *final_cmd_table, t_list *assignment_list)
{
	final_cmd_table->assignment_array = NULL;
	if (!assignment_list || ft_lstsize(assignment_list) == 0)
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
	char	tmp[PATH_MAX];
	int		i;

	final_cmd_table->envp = NULL;
	if (ft_lstsize(env_list) == 0)
		return (true);
	final_cmd_table->envp = ft_calloc(ft_lstsize(env_list) + 1, sizeof(char *));
	if (!final_cmd_table->envp)
		return (false);
	i = 0;
	while (env_list)
	{
		env_node = (t_env *)env_list->content;
		sprintf(tmp, "%s=%s", env_node->key, env_node->value);
		final_cmd_table->envp[i] = ft_strdup(tmp);
		if (!final_cmd_table->envp[i])
			return (free_array(final_cmd_table->envp), false);
		env_list = env_list->next;
		i++;
	}
	return (true);
}

t_final_cmd_table	*init_final_cmd_table(
						t_shell *shell,
						t_cmd_table *cmd_table)
{
	t_final_cmd_table	*final_cmd_table;

	final_cmd_table = ft_calloc(1, sizeof(t_final_cmd_table));
	if (!final_cmd_table)
		return (NULL);
	if (!setup_env(final_cmd_table, shell->env_list) || \
		!setup_cmd_name(final_cmd_table, cmd_table) || \
		!setup_cmd_args(final_cmd_table, cmd_table->cmd_args) || \
		!setup_assignment(final_cmd_table, cmd_table->assignment_list))
		return (free_final_cmd_table(&final_cmd_table), NULL);
	return (final_cmd_table);
}

void	free_final_cmd_table(t_final_cmd_table **final_cmd_table)
{
	free_array((*final_cmd_table)->envp);
	free((*final_cmd_table)->cmd_name);
	free_array((*final_cmd_table)->cmd_args);
	free_array((*final_cmd_table)->assignment_array);
	ft_free_and_null((void **)final_cmd_table);
}

t_final_cmd_table	*get_final_cmd_table(
						t_shell *shell,
						t_cmd_table *cmd_table)
{
	t_final_cmd_table	*final_cmd_table;

	final_cmd_table = init_final_cmd_table(shell, cmd_table);
	if (!final_cmd_table)
		return (NULL);
	// TODO: expand assignment array
	if (!expand_final_cmd_table(shell, final_cmd_table))
		return (free_final_cmd_table(&final_cmd_table), NULL);
	if (final_cmd_table->cmd_name == NULL && final_cmd_table->assignment_array)
		handle_assignment(shell, final_cmd_table);
	// do assginments
	// do redirections
	return (final_cmd_table);
}
