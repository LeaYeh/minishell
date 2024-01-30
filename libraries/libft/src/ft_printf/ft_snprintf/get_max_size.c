/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_max_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 01:20:35 by ldulling          #+#    #+#             */
/*   Updated: 2024/01/29 15:44:50 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	get_max_size(t_sformat *f, size_t size)
{
	size_t	max_size;

	if (f->sprinted + size <= f->size)
		max_size = size;
	else
		max_size = f->size - f->sprinted;
	return (max_size);
}
