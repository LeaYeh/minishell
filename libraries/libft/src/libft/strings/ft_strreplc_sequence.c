/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplc_sequence.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 23:36:36 by ldulling          #+#    #+#             */
/*   Updated: 2024/01/17 09:56:12 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "libft.h"

// char	*ft_strreplc_sequence(const char *str, const char *sequence,
// 								const char *rplcmt)
// {
// 	char	*occurance; // Write documentation
// 	size_t	rplcmt_len;
// 	char	*result;
// 	size_t	seq_len;

// 	if (!str && !sequence && rplcmt)
// 		return (ft_strdup(rplcmt));
// 	if (!str)
// 		return (NULL);
// 	result = ft_strdup(str);
// 	if (!result)
// 		return (NULL);
// 	if (!sequence || !*sequence || !rplcmt)
// 		return (result);
// 	rplcmt_len = ft_strlen(rplcmt);
// 	seq_len = ft_strlen(sequence);
// 	occurance = ft_strnstr(result, sequence, ft_strlen(result));
// 	while (occurance)
// 	{
// 		if (!ft_replc_part_of_str(&result, rplcmt, occurance - result, seq_len))	// Add to libft
// 			return (free(result), NULL);
// 		occurance = ft_strnstr(occurance + rplcmt_len, sequence,
// 						ft_strlen(occurance + rplcmt_len));
// 	}
// 	return (result);
// }
