/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_cmd_table_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:02:02 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/18 23:52:07 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "defines.h"
#include "utils.h"
#include "debug.h"

bool	setup_simple_cmd(t_final_cmd_table *final_cmd_table, t_list *simple_cmd_list)
{
	final_cmd_table->simple_cmd = NULL;
	if (!simple_cmd_list)
		return (true);
	final_cmd_table->simple_cmd = convert_list_to_string_array(simple_cmd_list);
	if (!final_cmd_table->simple_cmd)
		return (false);
	return (true);
}

bool	setup_exec_path(t_final_cmd_table *final_cmd_table)
{
	if (is_builtin(final_cmd_table->simple_cmd[0]) || \
		!final_cmd_table->simple_cmd[0]) // What if it will expand to nothing and only the next word is a builtin?
	{
		final_cmd_table->exec_path = NULL;
		return (true);
	}
	final_cmd_table->exec_path = get_exec_path(final_cmd_table->simple_cmd[0],
		final_cmd_table->envp);
	if (!final_cmd_table->exec_path)
		return (false);
	return (true);
}

bool	setup_assignment(
	t_final_cmd_table *final_cmd_table, t_list *assignment_list)
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
	char	tmp[PATH_MAX];
	int		i;

	final_cmd_table->envp = NULL;
	if (!env_list)
		return (true);
	final_cmd_table->envp = (char **)malloc( \
								(ft_lstsize(env_list) + 1) * sizeof(char *));
	if (!final_cmd_table->envp)
		return (false);
	i = 0;
	while (env_list)
	{
		env_node = (t_env *)env_list->content;
		sprintf(tmp, "%s=%s", env_node->key, env_node->value);	// TODO: This is really dangerous, bc the user could set a very long key or value.
		final_cmd_table->envp[i] = ft_strdup(tmp);
		if (!final_cmd_table->envp[i])
			return (free_array(&final_cmd_table->envp), false);
		env_list = env_list->next;
		i++;
	}
	final_cmd_table->envp[i] = NULL;
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
		!setup_simple_cmd(final_cmd_table, cmd_table->simple_cmd_list) || \
		!setup_exec_path(final_cmd_table) || \
		!setup_assignment(final_cmd_table, cmd_table->assignment_list))
		return (free_final_cmd_table(&final_cmd_table), NULL);
	return (final_cmd_table);
}

void	free_final_cmd_table(t_final_cmd_table **final_cmd_table)
{
	free_array(&(*final_cmd_table)->envp);
	free_array(&(*final_cmd_table)->simple_cmd);
	free((*final_cmd_table)->exec_path);
	free_array(&(*final_cmd_table)->assignment_array);
	ft_free_and_null((void **)final_cmd_table);
}

t_final_cmd_table	*get_final_cmd_table(
						t_shell *shell,
						t_cmd_table *cmd_table)
{
	t_final_cmd_table	*final_cmd_table;

	// Maybe expansion should happen before the init of the rest of the final_cmd_table
	final_cmd_table = init_final_cmd_table(shell, cmd_table);
	if (!final_cmd_table)
		return (NULL);
	// TODO: expand assignment array
	if (!expand_final_cmd_table(shell, final_cmd_table))
		return (free_final_cmd_table(&final_cmd_table), NULL);
	if (final_cmd_table->simple_cmd[0] == NULL && final_cmd_table->assignment_array)
		handle_assignment(shell, final_cmd_table);
	print_final_cmd_table(final_cmd_table);
	// do assginments
	// do redirections
	return (final_cmd_table);
}
