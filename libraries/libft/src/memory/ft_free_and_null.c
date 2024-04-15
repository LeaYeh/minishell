/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_and_null.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 03:10:28 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/20 19:12:03 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * The ft_free_and_null function frees the memory pointed to by *ptr and
 * sets *ptr to NULL.
 * It uses a temporary pointer to avoid a double free if the function gets
 * interrupted asynchoronously before it can set *ptr to NULL.
 * A memory leak caused by such an interruption should be handled by exit.
 *
 * @param ptr    A double pointer to the memory to be freed.
 *               If ptr or *ptr is NULL, the function does nothing.
 *
 * @return       No return value.
 *
 */
void	ft_free_and_null(void **ptr)
{
	void	*tmp;

	if (ptr && *ptr)
	{
		tmp = *ptr;
		*ptr = NULL;
		free(tmp);
	}
}
