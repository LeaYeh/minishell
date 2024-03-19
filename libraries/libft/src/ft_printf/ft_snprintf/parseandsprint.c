/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseandsprint.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 13:41:25 by ldulling          #+#    #+#             */
/*   Updated: 2024/03/19 16:04:27 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	parseandsprint(const char *format, int *i, t_sformat *f, va_list *ap)
{
	int	parsed;

	parsed = 1;
	if (format[(*i)++] == '%')
	{
		parsed += set_sformat(format, i, f, ap);
		if (format[*i] == '\0' && !f->specifier && !f->unresolved)
		{
			f->str[f->sprinted] = '\0';
			f->sprinted = -1;
			return ;
		}
		if (f->specifier)
			sprint_argument(f, ap);
	}
	if (!f->specifier)
		sprint_parsed(&format[*i - parsed], parsed, f);
}

void	sprint_argument(t_sformat *f, va_list *ap)
{
	if (f->specifier == 'c')
		sprint_char((unsigned char) va_arg(*ap, int), f);
	else if (f->specifier == 's')
		sprint_str(va_arg(*ap, const char *), f);
	else if (f->specifier == 'p')
		sprint_ptr((size_t) va_arg(*ap, void *), f);
	else if (f->specifier == 'd' || f->specifier == 'i')
		sprint_nbr((long) va_arg(*ap, int), f);
	else if (f->specifier == 'u')
		sprint_nbr((long) va_arg(*ap, unsigned int), f);
	else if (f->specifier == 'x' || f->specifier == 'X')
		sprint_nbr((long) va_arg(*ap, unsigned int), f);
	else if (f->specifier == '%')
		f->sprinted += ft_sputnchar(&f->str[f->sprinted], '%', max_size(f, 1));
}

void	reset_sformat(t_sformat *f)
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
