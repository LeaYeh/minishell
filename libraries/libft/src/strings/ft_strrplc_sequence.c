/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrplc_sequence.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 23:36:36 by ldulling          #+#    #+#             */
/*   Updated: 2024/02/15 02:52:03 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * The ft_strrplc_sequence function replaces all occurrences of a sequence in a
 * string with a replacement string.
 *
 * @param str         The string in which to replace the sequence.
 * @param sequence    The sequence to replace in the string.
 * @param rplcmt      The string to replace the sequence with.
 *
 * @return            A new string with all occurrences of the sequence replaced
 *                    with the replacement string.
 *                    If an error occurs, NULL is returned.
 * 				      If str and the replacement string are NULL, the function
 *                    also returns NULL.
 *                    If just the replacement string is not NULL, the function
 *                    returns a copy of the replacement string.
 *                    If str is not NULL but sequence is NULL or an empty
 *                    string or the replacement string is NULL, the function
 *                    returns a copy of the original string.
 *                    If the sequence is not found in str, the function also
 * 				      returns a copy of the original string.
 *
 */
char	*ft_strrplc_sequence(const char *str, const char *sequence,
								const char *rplcmt)
{
	char	*occurance;
	char	*result;
	size_t	rplcmt_len;
	size_t	seq_len;

	if (!str && !sequence && rplcmt)
		return (ft_strdup(rplcmt));
	if (!str)
		return (NULL);
	result = ft_strdup(str);
	if (!result)
		return (NULL);
	if (!sequence || !*sequence || !rplcmt)
		return (result);
	rplcmt_len = ft_strlen(rplcmt);
	seq_len = ft_strlen(sequence);
	occurance = ft_strnstr(result, sequence, ft_strlen(result));
	while (occurance)
	{
		if (!ft_strrplc_part(&result, rplcmt, occurance - result, seq_len))
			return (free(result), NULL);
		occurance = ft_strnstr(occurance + rplcmt_len, sequence,
				ft_strlen(occurance + rplcmt_len));
	}
	return (result);
}
