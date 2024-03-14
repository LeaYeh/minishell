/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_at_index.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 12:00:03 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/26 19:42:22 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * The ft_split_at_index function splits a string at a given index into two
 * parts.
 *
 * @param str      The string to be split.
 * @param index    The position at which to split the string.
 *
 * @return         On success, it returns a pointer to a NULL-terminated array
 *                 of two strings:
 *                 The first string is the part before the index, and the second
 *                 string is the part from the index to the end of the original
 *                 string.
 *                 If the input string is NULL, the index is out of bounds, or
 *                 memory allocation fails, it returns NULL.
 *
 */
char	**ft_split_at_index(char *str, size_t index)
{
	size_t	len;
	char	**str_array;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (index > len)
		return (NULL);
	str_array = (char **)malloc(3 * sizeof(char *));
	if (!str_array)
		return (NULL);
	str_array[0] = ft_substr(str, 0, index);
	if (!str_array[0])
		return (free(str_array), NULL);
	str_array[1] = ft_substr(str, index, len);
	if (!str_array[1])
		return (free(str_array[0]), free(str_array), NULL);
	str_array[2] = NULL;
	return (str_array);
}
