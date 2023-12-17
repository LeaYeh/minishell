/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 08:31:35 by codespace         #+#    #+#             */
/*   Updated: 2023/12/17 20:23:01 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"

/*
NOTES:
- END token at the end
- echo>out should be split into 3 tokens
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

void	get_type(t_token *token_node)
{
	char	*data;

	data = token_node->data;
	if (*data == '<')
		token_node->type = which_lesser(data);
	else if (*data == '>')
		token_node->type = which_greater(data);
	else if (*data == '|')
		token_node->type = which_pipe(data);
	else if (ft_strcmp("&&", data) == 0)
		token_node->type = T_AND;
	else if (*data == '(')
		token_node->type = T_L_BRACKET;
	else if (*data == ')')
		token_node->type = T_R_BRACKET;
	else if (*data == '\0')
		token_node->type = T_END;
	else
		token_node->type = T_WORD;
}

void	skip_until_same_quote(char *data, size_t *i)
{
	char	open_quote;

	open_quote = data[*i];
	while (data[*i] && data[*i] != open_quote)
		(*i)++;
}

bool	split_node(t_list *lst_node1, size_t i)
{
	char	**data_ptr;
	char	**data_split;
	t_list	*lst_node2;
	t_token	*token_node;

	data_ptr = &((t_token *) lst_node1->content)->data;
	data_split = ft_split_at_index(*data_ptr, i);
	if (!data_split)
		return (false);
	ft_free_and_null((void **) data_ptr);
	token_node = init_token_node(-1, data_split[0]);
	if (!token_node)
		return (free(data_split[0]), free(data_split[1]),
			free(data_split), false);
	lst_node2 = ft_lstnew(token_node);
	if (!lst_node2)
		return (free(data_split[0]), free(data_split[1]),
			free(data_split), free(token_node), false);
	ft_lstinsert_after(&lst_node1, lst_node2);
	free(data_split);
	return (true);
}

bool	split_token(t_list *lst_node, size_t i)
{
	t_list	*cur;
	char	*data;

	data = ((t_token *) lst_node->content)->data;
	cur = lst_node;
	if (i != 0)
	{
		if (!split_node(cur, i))
			return (false);
		cur = cur->next;
	}
	if (data[i] == '<' || data[i] == '>' || data[i] == '|' || data[i] == '&')
	{
		i++;
		if (data[i] == data[i - 1])
			i++;
	}
	if (data[i])
		if (!split_node(cur, i))
			return (false);
	return (true);
}

bool	split_by_symbols(t_list *lst_node)
{
	char	*data;
	size_t	i;

	data = ((t_token *) lst_node->content)->data;
	i = 0;
	while (data[i])
	{
		if (ft_strchr(TOK_SYMBOLS, data[i]))
			break ;
		else if (ft_strchr(QUOTES, data[i]))
			skip_until_same_quote(data, &i);
		i++;
	}
	if (data[i] != '\0')
		if (!split_token(lst_node, i))
			return (false);
	return (true);
}

bool	get_data(char *input_line, size_t *i, t_token *token_node)
{
	char	*open_quote;
	size_t	start;

	while (ft_strchr(WHITESPACE, input_line[*i]))
		(*i)++;
	start = *i;
	open_quote = NULL;
	while (input_line[*i]
		&& (!ft_strchr(WHITESPACE, input_line[*i]) || open_quote))
	{
		if (!open_quote)
			open_quote = ft_strchr(QUOTES, input_line[*i]);
		else if (*open_quote == input_line[*i])
			open_quote = NULL;
		(*i)++;
	}
	token_node->data = ft_substr(input_line, start, *i - start);
	if (!token_node->data)
		return (false);
	return (true);
}

bool	create_token_list(t_shell *shell, char *input_line)
{
	size_t	i;
	t_list	*lst_node;
	t_token	*token_node;

	if (!input_line)
		return (NULL);
	i = 0;
	lst_node = NULL;
	while (true)
	{
		token_node = init_token_node(-1, NULL);
		if (!token_node)
			return (false);
		if (!get_data(input_line, &i, token_node))
			break ;
		lst_node = ft_lstnew(token_node);
		if (!lst_node || !split_by_symbols(lst_node))
			break ;
		get_type(token_node);
		ft_lstadd_back(&shell->token_list, lst_node);
		if (token_node->type == T_END)
			return (true);
	}
	return (free(token_node->data), free(token_node), free(lst_node), false);
}

bool	ft_lexer(t_shell *shell, char *input_line)
{
	if (!create_token_list(shell, input_line))
		return (false);
	return (true);
}
