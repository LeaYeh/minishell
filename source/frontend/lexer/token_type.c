/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:20:32 by ldulling          #+#    #+#             */
/*   Updated: 2024/04/08 12:44:36 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"

static t_tok_typ	which_lesser(char *token_data);
static t_tok_typ	which_greater(char *token_data);
static t_tok_typ	which_pipe(char *token_data);
static bool			is_assignment_word(char *str);

void	set_token_type(t_list *token_list)
{
	t_tok	*token;
	char	*token_data;

	while (token_list)
	{
		token = (t_tok *)token_list->content;
		token_data = token->data;
		if (*token_data == '<')
			token->type = which_lesser(token_data);
		else if (*token_data == '>')
			token->type = which_greater(token_data);
		else if (*token_data == '|')
			token->type = which_pipe(token_data);
		else if (ft_strcmp("&&", token_data) == 0)
			token->type = T_AND;
		else if (*token_data == '(')
			token->type = T_L_PAREN;
		else if (*token_data == ')')
			token->type = T_R_PAREN;
		else if (is_assignment_word(token_data))
			token->type = T_ASSIGNMENT_WORD;
		else
			token->type = T_WORD;
		token_list = token_list->next;
	}
}

static t_tok_typ	which_lesser(char *token_data)
{
	if (ft_strcmp("<<", token_data) == 0)
		return (T_HERE_DOC);
	else
		return (T_RED_IN);
}

static t_tok_typ	which_greater(char *token_data)
{
	if (ft_strcmp(">>", token_data) == 0)
		return (T_APPEND);
	else
		return (T_RED_OUT);
}

static t_tok_typ	which_pipe(char *token_data)
{
	if (ft_strcmp("||", token_data) == 0)
		return (T_OR);
	else
		return (T_PIPE);
}

static bool	is_assignment_word(char *str)
{
	int	i;

	i = 0;
	if (str && is_valid_varname_start(str[i]))
	{
		while (is_valid_varname_char(str[i]))
			i++;
		if (str[i] == '=')
			return (true);
	}
	return (false);
}
