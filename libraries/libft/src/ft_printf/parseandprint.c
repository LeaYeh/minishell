/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseandprint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 13:41:25 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/17 13:42:32 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	parseandprint(const char *format, int *i, t_format *f, va_list *ap)
{
	int	printed;
	int	parsed;

	printed = 0;
	parsed = 1;
	if (format[(*i)++] == '%')
	{
		parsed += set_format(format, i, f, ap);
		if (format[*i] == '\0' && !f->specifier && !f->unresolved)
			return (-1);
		if (f->specifier)
			printed += print_argument(f, ap);
	}
	if (!f->specifier)
		printed += print_parsed(&format[*i - parsed], parsed, f);
	return (printed);
}

int	print_argument(t_format *f, va_list *ap)
{
	int	printed;

	printed = 0;
	if (f->specifier == 'c')
		printed = print_char((unsigned char) va_arg(*ap, int), f);
	else if (f->specifier == 's')
		printed = print_str(va_arg(*ap, const char *), f);
	else if (f->specifier == 'p')
		printed = print_ptr((size_t) va_arg(*ap, void *), f);
	else if (f->specifier == 'd' || f->specifier == 'i')
		printed = print_nbr((long) va_arg(*ap, int), f);
	else if (f->specifier == 'u')
		printed = print_nbr((long) va_arg(*ap, unsigned int), f);
	else if (f->specifier == 'x' || f->specifier == 'X')
		printed = print_nbr((long) va_arg(*ap, unsigned int), f);
	else if (f->specifier == '%')
		printed = ft_putnchar_fd('%', 1, f->fd);
	return (printed);
}

void	reset_format(t_format *f)
{
	f->hash = 0;
	f->plus = 0;
	f->space = 0;
	f->minus = 0;
	f->zero = 0;
	f->width = 0;
	f->precision = NO_PRECISION_SET;
	f->specifier = '\0';
	return ;
}
