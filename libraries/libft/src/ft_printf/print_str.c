/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 19:27:17 by ldulling          #+#    #+#             */
/*   Updated: 2024/01/29 05:07:36 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print(const char *str, int len, t_format *f);

int	print_str(const char *str, t_format *f)
{
	int	len;
	int	printed;

	printed = 0;
	if (!str)
	{
		len = ft_strlen(NULL_PRINTOUT_STR);
		if (f->precision >= 0 && len > f->precision)
			len = 0;
		printed += print(NULL_PRINTOUT_STR, len, f);
	}
	else
	{
		len = ft_strlen(str);
		if (f->precision >= 0 && len > f->precision)
			len = f->precision;
		printed += print(str, len, f);
	}
	return (printed);
}

static int	print(const char *str, int len, t_format *f)
{
	int	printed;

	printed = 0;
	if (!f->minus && f->width > len)
		printed += ft_putnchar_fd(' ', f->width - len, f->fd);
	printed += ft_putnstr_fd(str, len, f->fd);
	if (f->minus && f->width > len)
		printed += ft_putnchar_fd(' ', f->width - len, f->fd);
	return (printed);
}
