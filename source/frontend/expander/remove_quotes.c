/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 12:09:34 by ldulling          #+#    #+#             */
/*   Updated: 2024/01/28 02:12:54 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "utils.h"

bool	handle_remove_quotes(t_list **lst)
{
	t_list	*cur;

	cur = *lst;
	while (cur)
	{
		if (!remove_quotes((char **)&cur->content))
			return (false);
		cur = cur->next;
	}
	return (true);
}

bool	remove_quotes(char **str)
{
	size_t	first_quote;
	size_t	i;

	if (!*str)
		return (true);
	i = 0;
	while ((*str)[i])
	{
		while (!ft_strchr(QUOTES, (*str)[i]))
			i++;
		if (!(*str)[i])
			return (true);
		first_quote = i;
		if (!skip_to_same_quote(*str, &i))
			return (true);
		if (!ft_rplc_part_of_str(str, "", first_quote, 1))
			return (false);
		if (!ft_rplc_part_of_str(str, "", --i, 1))
			return (false);
	}
	return (true);
}
