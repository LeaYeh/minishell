/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:13:12 by ldulling          #+#    #+#             */
/*   Updated: 2023/09/24 16:14:51 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
