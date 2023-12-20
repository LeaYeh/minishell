/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 08:31:35 by codespace         #+#    #+#             */
/*   Updated: 2023/12/20 10:20:40 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"

/*
NOTES:
- END token at the end
- echo>out should be split into 3 tokens
- Assignment word!
	[x] =abc -> WORD
	[x] abc=abc -> ASSIGNMENT_WORD
	[x] a"b"c=456 -> WORD (unspecified)
	[ ] export >a=def -> a=def will be a WORD
		! Need to test with parser what will happen here
*/

// TODO
// [x] 1. First separate input_line by whitespace into data_array
// [x] An empty string in the data does not mean T_END of the token_list!

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

bool	is_assignment_word(char *str)
{
	size_t	i;

	i = 0;
	if (str && !ft_isdigit(str[i]))
	{
		while(str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
			i++;
		if (i != 0 && str[i] == '=')
			return (true);
	}
	return (false);
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
		else if (is_assignment_word(data))
			token->type = T_ASSIGNMENT_WORD;
		else
			token->type = T_WORD;
		lst_node = lst_node->next;
	}
}

bool	split_node(t_list *lst_node1, size_t i)
{
	char	**data_node1;
	char	**data_split;
	t_list	*lst_node2;
	t_token	*new_token;

	data_node1 = &((t_token *) lst_node1->content)->data;
	data_split = ft_split_at_index(*data_node1, i);
	if (!data_split)
		return (false);
	free(*data_node1);
	*data_node1 = data_split[0];
	new_token = init_token_node(-1, data_split[1]);
	if (!new_token)
		return (free(data_split[1]), free(data_split), false);
	lst_node2 = ft_lstnew(new_token);
	if (!lst_node2)
		return (free_token_node(new_token), free(data_split), (false));
	ft_lstinsert_after(&lst_node1, lst_node2);
	free(data_split);
	return (true);
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

void	skip_operator(char *data, size_t *i)
{
	if (data[*i] == '<' || data[*i] == '>' || data[*i] == '|' || data[*i] == '&')
	{
		(*i)++;
		if (data[*i] == data[*i - 1])
			(*i)++;
	}
	else if (data[*i] == '(' || data[*i] == ')')
		(*i)++;
}

bool	separate_operators(t_list *lst_node)
{
	char	*data;
	size_t	i;

	data = ((t_token *) lst_node->content)->data;
	i = 0;
	while (data[i])
	{
		if (ft_strchr(TOK_SYMBOLS, data[i]))
		{
			if (i == 0)
				skip_operator(data, &i);
			if (data[i])
			{
				if (!split_node(lst_node, i))
					return (false);
				lst_node = lst_node->next;
				data = ((t_token *) lst_node->content)->data;
				i = 0;
			}
		}
		else if (ft_strchr(QUOTES, data[i]))
			skip_past_same_quote(data, &i);
		else
			i++;
	}
	return (true);
}

bool	get_data_list(t_list **data_list, char *input_line)
{
	char	*data;
	t_list	*new_node;
	size_t	i;
	size_t	start;

	*data_list = NULL;
	i = 0;
	while (input_line[i])
	{
		while (input_line[i] && ft_strchr(WHITESPACE, input_line[i]))
			i++;
		if (!input_line[i])
			break ;
		start = i;
		while (input_line[i] && !ft_strchr(WHITESPACE, input_line[i]))
		{
			if (ft_strchr(QUOTES, input_line[i]))
				skip_past_same_quote(input_line, &i);
			else
				i++;
		}
		data = ft_substr(input_line, start, i - start);
		if (!data)
			return (ft_lstclear(data_list, free), false);
		new_node = ft_lstnew(data);
		if (!new_node)
			return (ft_lstclear(data_list, free), free(data), false);
		ft_lstadd_back(data_list, new_node);
	}
	return (true);
}

bool	add_end_node(t_list	**token_list)
{
	t_list	*new_node;
	t_token	*token;

	token = init_token_node(T_END, NULL);
	if (!token)
		return (false);
	new_node = (ft_lstnew(token));
	if (!new_node)
		return (free(token), false);
	ft_lstadd_back(token_list, new_node);
	return (true);
}

bool	create_token_list(t_shell *shell, char *input_line)
{
	t_list	*data_list;
	t_list	*new_nodes;
	t_token	*token;

	if (!shell || !input_line)
		return (NULL);
	if (!get_data_list(&data_list, input_line))
		return (false);
	new_nodes = NULL;
	while (data_list)
	{
		token = init_token_node(-1, data_list->content);
		if (!token)
			break ;
		new_nodes = ft_lstnew(token);
		if (!new_nodes || !separate_operators(new_nodes))
			break ;
		get_type(new_nodes);
		ft_lstadd_back(&shell->token_list, new_nodes);
		free(ft_lstpop(&data_list));
	}
	if (data_list)
		return (ft_lstclear(&data_list, free), free_token_node(token), ft_lstclear(&new_nodes, free), false);
	return (add_end_node(&shell->token_list));
}

bool	ft_lexer(t_shell *shell)
{
	if (!create_token_list(shell, shell->input_line))
		return (false);
	return (true);
}
