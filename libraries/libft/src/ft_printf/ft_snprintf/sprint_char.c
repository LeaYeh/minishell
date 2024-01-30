/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprint_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 19:26:51 by ldulling          #+#    #+#             */
/*   Updated: 2024/01/29 15:44:50 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	sprint_char(unsigned char c, t_sformat *f)
{
	if (!f->minus && f->width > 1)
		f->sprinted += ft_sputnchar(&f->str[f->sprinted], ' ',
				get_max_size(f, f->width - 1));
	f->sprinted += ft_sputnchar(&f->str[f->sprinted], c, get_max_size(f, 1));
	if (f->minus && f->width > 1)
		f->sprinted += ft_sputnchar(&f->str[f->sprinted], ' ',
				get_max_size(f, f->width - 1));
}
