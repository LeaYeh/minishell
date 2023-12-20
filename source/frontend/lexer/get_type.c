/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 10:28:00 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/20 10:53:19 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

void	get_type(t_list *lst_node)
{
	char	*data;
	t_token	*token;

	while (lst_node)
	{
		token = (t_token *) lst_node->content;
		data = token->data;
		if (*data == '<')
			token->type = which_lesser(data);
		else if (*data == '>')
			token->type = which_greater(data);
		else if (*data == '|')
			token->type = which_pipe(data);
		else if (ft_strcmp("&&", data) == 0)
			token->type = T_AND;
		else if (*data == '(')
			token->type = T_L_BRACKET;
		else if (*data == ')')
			token->type = T_R_BRACKET;
		else if (is_assignment_word(data))
			token->type = T_ASSIGNMENT_WORD;
		else
			token->type = T_WORD;
		lst_node = lst_node->next;
	}
}

int	which_lesser(char *data)
{
	if (ft_strcmp("<<", data) == 0)
		return (T_HERE_DOC);
	else
		return (T_RED_IN);
}

int	which_greater(char *data)
{
	if (ft_strcmp(">>", data) == 0)
		return (T_APPEND);
	else
		return (T_RED_OUT);
}

int	which_pipe(char *data)
{
	if (ft_strcmp("||", data) == 0)
		return (T_OR);
	else
		return (T_PIPE);
}

bool	is_assignment_word(char *str)
{
	size_t	i;

	i = 0;
	if (str && !ft_isdigit(str[i]))
	{
		while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
			i++;
		if (i != 0 && str[i] == '=')
			return (true);
	}
	return (false);
}
