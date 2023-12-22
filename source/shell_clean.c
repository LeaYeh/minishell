/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 19:02:15 by lyeh              #+#    #+#             */
/*   Updated: 2023/12/21 22:15:52 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"

void	ft_free_input_line(char **input_line)
{
	if (!input_line)
		return ;
	free(*input_line);
	*input_line = NULL;
}

void	free_env_node(void *content)
{
	t_env	*env;

	env = (t_env *)content;
	free(env->key);
	free(env->value);
	free(env);
}

void	ft_clean_shell(t_shell *shell)
{
	ft_lstclear(&shell->env_list, free_env_node);
	ft_lstclear(&shell->token_list, free_token_node);
	ft_free_input_line(&shell->input_line);
	exit(shell->exit_code);
}
