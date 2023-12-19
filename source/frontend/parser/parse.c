/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:28:20 by lyeh              #+#    #+#             */
/*   Updated: 2023/12/19 15:32:35 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "utils.h"

bool	mock_lexer(t_shell *shell)
{
	char	*line;
	char	*term;
	t_token	*token_node;
	t_list	*lst_node;

	line = ft_strdup(shell->input_line);
	term = ft_strtok(line, " ");
	while (term)
	{
		token_node = (t_token *)malloc(sizeof(t_token));
		if (!token_node)
			return (false);
		if (!token_node)
			return (false);
		if (ft_strcmp(term, "=") == 0)
			token_node->type = T_ASSIGNMENT_WORD;
		else if (ft_strcmp(term, "<") == 0)
			token_node->type = T_RED_IN;
		else if (ft_strcmp(term, ">") == 0)
			token_node->type = T_RED_OUT;
		else if (ft_strcmp(term, "<<") == 0)
			token_node->type = T_HERE_DOC;
		else if (ft_strcmp(term, ">>") == 0)
			token_node->type = T_APPEND;
		else if (ft_strcmp(term, "|") == 0)
			token_node->type = T_PIPE;
		else if (ft_strcmp(term, "||") == 0)
			token_node->type = T_OR;
		else if (ft_strcmp(term, "&&") == 0)
			token_node->type = T_AND;
		else if (ft_strcmp(term, "(") == 0)
			token_node->type = T_L_BRACKET;
		else if (ft_strcmp(term, ")") == 0)
			token_node->type = T_R_BRACKET;
		else
			token_node->type = T_WORD;
		token_node->data = ft_strdup(term);
		lst_node = ft_lstnew(token_node);
		if (!lst_node)
			return (free(term), free_token_node(token_node), false);
		ft_lstadd_back(&shell->token_list, lst_node);
		term = ft_strtok(NULL, " ");
	}
	free(line);
	return (true);
}

bool	parse_step(t_pt_node *pt_entry,
	t_list **input_buffer, t_stack **state_stack, t_stack **parse_stack)
{
	bool		ret;

	ret = false;

	if (pt_entry && pt_entry->action == A_SHIFT)
		ret = parse_shift(
				input_buffer, state_stack, parse_stack, pt_entry->next_state);
	else if (pt_entry && pt_entry->action == A_REDUCE)
	{
		if (parse_reduce(state_stack, parse_stack, pt_entry) && \
			parse_goto(state_stack,
				get_token_from_stack(ft_stkpeektop(*parse_stack))->type))
			ret = true;
	}
	else if (pt_entry && pt_entry->action == A_ACCEPT)
		ret = true;
	else
		ret = false;
	return (ret);
}


bool	parse(t_list *token_list, t_stack **state_stack, t_stack **parse_stack)
{
	t_list		*input_buffer;
	t_pt_node	*pt_entry;

	if (!init_parse(token_list, &input_buffer, state_stack, parse_stack))
		return (false);
	while (input_buffer)
	{
		pt_entry = get_next_pt_entry(
				get_state_from_stack(ft_stkpeektop(*state_stack)),
				get_token_type_from_list(input_buffer),
				A_SHIFT | A_REDUCE | A_ACCEPT);
		if (pt_entry && pt_entry->action == A_ACCEPT)
			break ;
		if (!parse_step(pt_entry, &input_buffer, state_stack, parse_stack))
		{
			ft_dprintf(2, "%s: syntax error near unexpected token `%s'\n",
				PROGRAM_NAME,
				((t_token *)input_buffer->content)->data);
			return (false);
		}
		free(pt_entry);
		if (get_token_type_from_list(input_buffer) != T_END)
			input_buffer = input_buffer->next;
	}
	return (true);
}

bool	ft_parse(t_list *token_list)
{
	t_stack		*state_stack;
	t_stack		*parse_stack;

	state_stack = NULL;
	parse_stack = NULL;
	if (!parse(token_list, &state_stack, &parse_stack))
		return (free_parse(&state_stack, &parse_stack), false);
	return (true);
}
