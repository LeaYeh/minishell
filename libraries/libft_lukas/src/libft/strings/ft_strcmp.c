/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:16:22 by ldulling          #+#    #+#             */
/*   Updated: 2023/11/12 11:18:04 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
