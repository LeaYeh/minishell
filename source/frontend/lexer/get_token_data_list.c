/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_data_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 11:30:35 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/21 20:28:46 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_list	*get_token_data_list(char *input_line)
{
	size_t	i;
	t_list	*new_node;
	char	*token_data;
	t_list	*token_data_list;

	token_data_list = NULL;
	i = 0;
	while (input_line[i])
	{
		while (input_line[i] && ft_strchr(WHITESPACE, input_line[i]))
			i++;
		if (!input_line[i])
			break ;
		token_data = get_token_data(input_line, &i);
		if (!token_data)
			return (ft_lstclear(&token_data_list, free), NULL);
		new_node = ft_lstnew(token_data);
		if (!new_node)
			return (ft_lstclear(&token_data_list, free), free(token_data),
				NULL);
		ft_lstadd_back(&token_data_list, new_node);
	}
	return (token_data_list);
}

char	*get_token_data(char *input_line, size_t *i)
{
	size_t	start;

	start = *i;
	while (input_line[*i] && !ft_strchr(WHITESPACE, input_line[*i]))
	{
		if (ft_strchr(QUOTES, input_line[*i]))
			skip_past_same_quote(input_line, i);
		else
			(*i)++;
	}
	return (ft_substr(input_line, start, *i - start));
}
