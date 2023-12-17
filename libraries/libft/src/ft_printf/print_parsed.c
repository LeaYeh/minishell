/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_parsed.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:12:14 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/17 13:37:42 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_flags(const char *format, int *i, t_format *f);
static int	print_width(const char *format, int *i, t_format *f);
static int	print_precision(const char *format, int *i, t_format *f);

int	print_parsed(const char *format, int parsed, t_format *f)
{
	int	i;
	int	printed;

	i = 0;
	printed = 0;
	if (format[0] == '%')
	{
		printed += ft_putnchar_fd('%', ++i, f->fd);
		printed += print_flags(format, &i, f);
		printed += print_width(format, &i, f);
		printed += print_precision(format, &i, f);
	}
	printed += ft_putnstr_fd(&format[i], parsed - i, f->fd);
	return (printed);
}

static int	print_flags(const char *format, int *i, t_format *f)
{
	int	printed;

	printed = 0;
	if (f->hash)
		printed += ft_putnchar_fd('#', 1, f->fd);
	if (f->plus)
		printed += ft_putnchar_fd('+', 1, f->fd);
	if (f->space && !f->plus)
		printed += ft_putnchar_fd(' ', 1, f->fd);
	if (f->minus)
		printed += ft_putnchar_fd('-', 1, f->fd);
	if (f->zero && (!f->minus || f->minus == FROM_NEGATIVE_WIDTH))
		printed += ft_putnchar_fd('0', 1, f->fd);
	while (format[*i] && ft_strchr(FLAGS, format[*i]))
		(*i)++;
	return (printed);
}

static int	print_width(const char *format, int *i, t_format *f)
{
	int	printed;

	printed = 0;
	if (f->width)
		printed += ft_putnbr_base_fd(f->width, "0123456789", f->fd);
	if (format[*i] == '*')
		(*i)++;
	else
		while (ft_isdigit(format[*i]))
			(*i)++;
	return (printed);
}

static int	print_precision(const char *format, int *i, t_format *f)
{
	int	printed;

	printed = 0;
	if (f->precision >= 0)
	{
		printed += ft_putnchar_fd('.', 1, f->fd);
		(*i)++;
		printed += ft_putnbr_base_fd(f->precision, "0123456789", f->fd);
		if (format[*i] == '*')
			(*i)++;
		else
			while (ft_isdigit(format[*i]))
				(*i)++;
	}
	else if (f->precision == NEGATIVE_PRECISION)
		(*i) += 2;
	return (printed);
}
