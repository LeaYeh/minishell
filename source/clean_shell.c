/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 19:02:15 by lyeh              #+#    #+#             */
/*   Updated: 2023/12/08 20:25:33 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_ast(t_ast **ast)
{
	if (!ast)
		return ;
	if ((*ast)->left)
		ft_free_ast(&(*ast)->left);
	if ((*ast)->right)
		ft_free_ast(&(*ast)->right);
	free(*ast);
	*ast = NULL;
}

void	ft_free_input_line(char **input_line)
{
	if (!input_line)
		return ;
	free(*input_line);
	*input_line = NULL;
}

void	ft_clean_shell(t_shell *shell)
{
	ft_lstclear(&shell->env_list, free);
	ft_lstclear(&shell->token_list, free);
	ft_free_ast(&shell->ast);
	ft_free_input_line(&shell->input_line);
}
