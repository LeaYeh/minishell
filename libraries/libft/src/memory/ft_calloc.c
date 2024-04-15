/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:02:33 by ldulling          #+#    #+#             */
/*   Updated: 2023/09/24 16:21:21 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	multiplication_is_overflow(size_t n1, size_t n2);

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*ptr;
	size_t			bytes;

	if (multiplication_is_overflow(nmemb, size))
		return (NULL);
	bytes = nmemb * size;
	ptr = (unsigned char *) malloc(bytes);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, bytes);
	return ((void *) ptr);
}

static int	multiplication_is_overflow(size_t n1, size_t n2)
{
	size_t	max_size;

	max_size = (size_t) -1;
	if (n1 == 0 || n2 == 0)
		return (0);
	if (n1 > max_size / n2)
		return (1);
	else
		return (0);
}
