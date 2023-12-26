/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 19:02:15 by lyeh              #+#    #+#             */
/*   Updated: 2023/12/26 19:42:33 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"

void	free_env_node(t_env *env)
{
	if (!env)
		return ;
	free(env->key);
	free(env->value);
	free(env);
}

void	ft_clean_shell(t_shell *shell)
{
	ft_lstclear(&shell->env_list, (void *)free_env_node);
	ft_lstclear(&shell->token_list, (void *)free_token_node);
	free_ast_node(shell->ast);
	ft_free_and_null((void **)&shell->input_line);
	exit(shell->exit_code);
}
