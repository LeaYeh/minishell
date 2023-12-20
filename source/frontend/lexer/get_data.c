/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 11:30:35 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/20 12:11:56 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

bool	get_data_list(t_list **data_list, char *input_line)
{
	char	*data;
	t_list	*new_node;
	size_t	i;

	i = 0;
	while (input_line[i])
	{
		while (input_line[i] && ft_strchr(WHITESPACE, input_line[i]))
			i++;
		if (!input_line[i])
			break ;
		data = get_data(input_line, &i);
		if (!data)
			return (ft_lstclear(data_list, free), false);
		new_node = ft_lstnew(data);
		if (!new_node)
			return (ft_lstclear(data_list, free), free(data), false);
		ft_lstadd_back(data_list, new_node);
	}
	return (true);
}

char	*get_data(char *input_line, size_t *i)
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
