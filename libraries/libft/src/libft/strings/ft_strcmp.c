/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:16:22 by ldulling          #+#    #+#             */
/*   Updated: 2024/01/17 12:41:11 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * The ft_strcmp function compares the string pointed to by s1 with the string
 * pointed to by s2.
 *
 * @param s1    A pointer to the first string.
 * @param s2    A pointer to the second string.
 *
 * @return      0 if the strings are identical.
 *              A positive integer if the first character that does not match
 *              has a greater value in s1 than in s2.
 *              A negative integer if the first character that does not match
 *              has a lower value in s1 than in s2.
 *
 * @note        Calling ft_strcmp with s1 or s2 equal to NULL will cause a
 *              segmentation fault (mirrors the behavior of the original
 *              strcmp).
 *
 */
int	ft_strcmp(const char *s1, const char *s2)
{
	const unsigned char	*casted_ptr_s1;
	const unsigned char	*casted_ptr_s2;
	size_t				i;

	casted_ptr_s1 = (const unsigned char *) s1;
	casted_ptr_s2 = (const unsigned char *) s2;
	i = 0;
	while (casted_ptr_s1[i] == casted_ptr_s2[i] && casted_ptr_s1[i])
		i++;
	return ((int) casted_ptr_s1[i] - (int) casted_ptr_s2[i]);
}
