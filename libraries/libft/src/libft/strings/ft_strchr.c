/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:13:12 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/23 16:59:08 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * The ft_strchr function locates the first occurrence of c (converted to a
 * char) in the string pointed to by s.
 *
 * @param s    The string in which to search for the character.
 * @param c    The character to search for.
 *
 * @return     A pointer to the located character, or NULL if the character does
 *             not appear in the string.
 *
 * @note       Calling ft_strchr with s equal to NULL will cause a segmentation
 *             fault (mirrors the behavior of the original strchr).
 *
 */
char	*ft_strchr(const char *s, int c)
{
	char	casted_c;

	casted_c = (char) c;
	if (casted_c == '\0')
	{
		while (*s)
			s++;
		return ((char *) s);
	}
	else
	{
		while (*s)
		{
			if (*s == casted_c)
				return ((char *) s);
			s++;
		}
		return (NULL);
	}
}
