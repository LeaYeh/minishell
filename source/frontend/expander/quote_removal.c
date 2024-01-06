/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 12:09:34 by ldulling          #+#    #+#             */
/*   Updated: 2024/01/03 15:28:42 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "utils.h"

bool	quote_removal(char **str)
{
	size_t	first_quote;
	size_t	i;

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
		if (!replace_part_of_str(str, "", first_quote, 1))
			return (false);
		if (!replace_part_of_str(str, "", --i, 1))
			return (false);
	}
	return (true);
}
