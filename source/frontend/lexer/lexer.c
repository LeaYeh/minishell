/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 08:31:35 by codespace         #+#    #+#             */
/*   Updated: 2023/12/19 17:03:11 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"

/*
NOTES:
- END token at the end
- echo>out should be split into 3 tokens
- Assignment word!
	- =abc -> WORD
	- abc=abc -> ASSIGNMENT_WORD
	- a"b"c=456 -> WORD (unspecified)
*/

/* < > << >> | || && ( ) */

# define TOK_SYMBOLS "<>|&()"
# define QUOTES "'\""

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

void	get_type(t_list *lst_node)
{
	char	*data;
	t_token	*token;

	while (lst_node)
	{
		token = (t_token *) lst_node->content;
		data = token->data;
		if (!data || *data == '\0')
			token->type = T_END;
		else if (*data == '<')
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
		else
			token->type = T_WORD;
		lst_node = lst_node->next;
	}
}

void	skip_past_same_quote(char *str, size_t *i)
{
	char	*open_quote;

	open_quote = ft_strchr(QUOTES, str[*i]);
	if (open_quote)
	{
		while (str[*i])
		{
			(*i)++;
			if (str[*i] == *open_quote)
			{
				(*i)++;
				break ;
			}
		}
	}
}

bool	split_node(t_list *lst_node1, size_t i)
{
	char	**data_node1;
	char	**data_split;
	t_list	*lst_node2;
	t_token	*token;

	data_node1 = &((t_token *) lst_node1->content)->data;
	data_split = ft_split_at_index(*data_node1, i);
	if (!data_split)
		return (false);
	free(*data_node1);
	*data_node1 = data_split[0];
	token = init_token_node(-1, data_split[1]);
	if (!token)
		return (free(data_split[1]), free(data_split), false);
	lst_node2 = ft_lstnew(token);
	if (!lst_node2)
		return (free_token_node(token), free(data_split), (false));
	ft_lstinsert_after(&lst_node1, lst_node2);
	free(data_split);
	return (true);
}

bool	separate_operator(t_list *lst_node, size_t i)
{
	char	*data;

	data = ((t_token *) lst_node->content)->data;
	if (i != 0)
	{
		if (!split_node(lst_node, i))
			return (false);
		lst_node = lst_node->next;
	}
	if (data[i] == '<' || data[i] == '>' || data[i] == '|' || data[i] == '&')
	{
		i++;
		if (data[i] == data[i - 1])
			i++;
	}
	else if (data[i] == '(' || data[i] == ')')
		i++;
	if (!split_node(lst_node, i))
			return (false);
	return (true);
}

bool	split_nodes_by_data(t_list *lst_node)
{
	char	*data;
	size_t	i;

	while (lst_node)
	{
		data = ((t_token *) lst_node->content)->data;
		i = 0;
		while (data[i])
		{
			if (ft_strchr(TOK_SYMBOLS, data[i]))
				break ;
			else if (ft_strchr(QUOTES, data[i]))
				skip_past_same_quote(data, &i);
			else
				i++;
		}
		if (data[i] != '\0')
			if (!separate_operator(lst_node, i))
				return (false);
		lst_node = ft_lstlast(lst_node)->next;
	}
	return (true);
}

bool	get_data(char *input_line, size_t *i, t_token *token)
{
	size_t	start;

	while (ft_strchr(WHITESPACE, input_line[*i]))
		(*i)++;
	start = *i;
	while (input_line[*i] && !ft_strchr(WHITESPACE, input_line[*i]))
	{
		if (ft_strchr(QUOTES, input_line[*i]))
			skip_past_same_quote(input_line, i);
		else
			(*i)++;
	}
	token->data = ft_substr(input_line, start, *i - start);
	if (!token->data)
		return (false);
	return (true);
}

bool	create_token_list(t_shell *shell, char *input_line)
{
	size_t	i;
	t_list	*new_nodes;
	t_token	*token;

	if (!input_line)
		return (NULL);
	i = 0;
	new_nodes = NULL;
	while (true)
	{
		token = init_token_node(-1, NULL);
		if (!token)
			return (false);
		if (!get_data(input_line, &i, token))
			break ;
		new_nodes = ft_lstnew(token);
		if (!new_nodes || !split_nodes_by_data(new_nodes))
			break ;
		get_type(new_nodes);
		ft_lstadd_back(&shell->token_list, new_nodes);
		if (((t_token *) ft_lstlast(new_nodes)->content)->type == T_END)
			return (true);
	}
	return (free_token_node(token), ft_lstclear(&new_nodes, free), false);
}

bool	ft_lexer(t_shell *shell)
{
	if (!create_token_list(shell, shell->input_line))
		return (false);
	return (true);
}
