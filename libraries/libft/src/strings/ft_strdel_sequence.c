/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdel_sequence.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:30:19 by ldulling          #+#    #+#             */
/*   Updated: 2024/01/12 23:43:55 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * The ft_strdel_sequence function removes all occurrences of a sequence from a
 * string.
 *
 * @param str         The string from which to remove the sequence.
 *                    If str is NULL, NULL is returned.
 * @param sequence    The sequence to remove from the string.
 *                    If sequence is NULL or an empty string, a copy of the
 *                    original string is returned.
 *
 * @return            A new string with all occurrences of the sequence removed.
 *                    If an error occurs, NULL is returned.
 *
 */
char	*ft_strdel_sequence(const char *str, const char *sequence)
{
	char	*occurance;
	char	*result;
	size_t	seq_len;
	char	*tmp;
	size_t	unsearched_len;

	if (!str)
		return (NULL);
	tmp = ft_strdup(str);
	if (!tmp)
		return (NULL);
	if (!sequence || !*sequence)
		return (tmp);
	seq_len = ft_strlen(sequence);
	occurance = ft_strnstr(tmp, sequence, ft_strlen(tmp));
	while (occurance)
	{
		unsearched_len = ft_strlen(occurance + seq_len);
		ft_memmove(occurance, occurance + seq_len, unsearched_len + 1);
		occurance = ft_strnstr(occurance, sequence, unsearched_len);
	}
	result = ft_strdup(tmp);
	free(tmp);
	return (result);
}
