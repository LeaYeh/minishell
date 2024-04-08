/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:00:04 by lyeh              #+#    #+#             */
/*   Updated: 2024/04/04 22:59:25 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

static char	*get_token_type_str(t_tok_typ type);

void	print_env_list(t_sh *shell)
{
	printf("--------- ENV LIST ---------\n");
	ft_lstiter(shell->env_list, (void *)print_env);
	printf("----------------------------\n\n");
}

void	print_env(t_env *env)
{
	printf("%s=%s\n", env->key, env->value);
}

void	print_token_list(t_list *token_list)
{
	printf("-------- TOKEN LIST --------\n");
	ft_lstiter(token_list, (void *)print_token);
	printf("----------------------------\n\n");
}

void	print_token(t_tok *token)
{
	printf("(type: %s, data: %s)\n",
		get_token_type_str(token->type), token->data);
}

static char	*get_token_type_str(t_tok_typ type)
{
	if (type == T_WORD)
		return ("WORD");
	else if (type == T_ASSIGNMENT_WORD)
		return ("ASSIGNMENT_WORD");
	else if (type == T_RED_IN)
		return ("RED_IN");
	else if (type == T_RED_OUT)
		return ("RED_OUT");
	else if (type == T_HERE_DOC)
		return ("HEREDOC");
	else if (type == T_APPEND)
		return ("APPEND");
	else if (type == T_PIPE)
		return ("PIPE");
	else if (type == T_OR)
		return ("OR");
	else if (type == T_AND)
		return ("AND");
	else if (type == T_L_BRACKET)
		return ("L_BRACKET");
	else if (type == T_R_BRACKET)
		return ("R_BRACKET");
	else if (type == T_END)
		return ("END");
	return (NULL);
}
