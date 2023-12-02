/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:15:09 by ldulling          #+#    #+#             */
/*   Updated: 2023/09/25 17:41:19 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*strj;
	size_t	len1;
	size_t	len2;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	strj = (char *) malloc(len1 + len2 + 1);
	if (strj == NULL)
		return (NULL);
	if (len1)
		(void) ft_memcpy(&strj[0], s1, len1);
	if (len2)
		(void) ft_memcpy(&strj[len1], s2, len2);
	strj[len1 + len2] = '\0';
	return (strj);
}
