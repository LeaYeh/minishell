/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 19:26:51 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/02 20:16:30 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_char(unsigned char c, t_format *f)
{
	int	printed;

	printed = 0;
	if (!f->minus && f->width > 1)
		printed += ft_putnchar_fd(' ', f->width - 1, FD);
	printed += ft_putnchar_fd(c, 1, FD);
	if (f->minus && f->width > 1)
		printed += ft_putnchar_fd(' ', f->width - 1, FD);
	return (printed);
}
