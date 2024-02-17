/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:00:04 by lyeh              #+#    #+#             */
/*   Updated: 2023/12/11 19:48:10 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

void	print_token(t_token *token)
{
	printf("(type: %s, data: %s)\n",
		ft_get_token_type_str(token->type), token->data);
}

void	print_token_list(t_list *token_list)
{
	printf("-------- TOKEN LIST --------\n");
	ft_lstiter(token_list, (void *)print_token);
	printf("----------------------------\n\n");
}

void	ft_print_env(t_env *env)
{
	printf("%s=%s\n", env->key, env->value);
}

void	ft_print_token(t_token *token)
{
	printf("(type: %s, data: %s)\n",
		ft_get_token_type_str(token->type), token->data);
}

void	ft_show_token_list(t_shell *shell)
{
	printf("-------- TOKEN LIST --------\n");
	ft_lstiter(shell->token_list, (void *)ft_print_token);
	printf("----------------------------\n\n");
}

void	ft_show_env_list(t_shell *shell)
{
	printf("--------- ENV LIST ---------\n");
	ft_lstiter(shell->env_list, (void *)ft_print_env);
	printf("----------------------------\n\n");
}
