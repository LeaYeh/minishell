/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_at_index.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:00:03 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/17 12:07:55 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_split_at_index(char **str, size_t index)
{
	size_t	len;
	char	*part1;
	char	*part2;

	if (!str || !*str)
		return (NULL);
	len = ft_strlen(*str);
	if (index > len)
		return (NULL);
	part1 = ft_substr(*str, 0, index);
	if (!part1)
		return (NULL);
	part2 = ft_substr(*str, index, len);
	if (!part2)
	{
		free(part1);
		return (NULL);
	}
	free(*str);
	*str = part1;
	return (part2);
}
