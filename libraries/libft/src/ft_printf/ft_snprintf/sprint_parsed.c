/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprint_parsed.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:12:14 by ldulling          #+#    #+#             */
/*   Updated: 2024/03/19 16:06:06 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	sprint_flags(const char *format, int *i, t_sformat *f);
static void	sprint_width(const char *format, int *i, t_sformat *f);
static void	sprint_precision(const char *format, int *i, t_sformat *f);

void	sprint_parsed(const char *format, int parsed, t_sformat *f)
{
	int	i;

	i = 0;
	if (format[0] == '%')
	{
		f->sprinted += ft_sputnchar(&f->str[f->sprinted], '%',
				max_size(f, ++i));
		sprint_flags(format, &i, f);
		sprint_width(format, &i, f);
		sprint_precision(format, &i, f);
	}
	f->sprinted += ft_sputnstr(&f->str[f->sprinted], &format[i],
			max_size(f, parsed - i));
}

static void	sprint_flags(const char *format, int *i, t_sformat *f)
{
	if (f->hash)
		f->sprinted += ft_sputnchar(&f->str[f->sprinted], '#', max_size(f, 1));
	if (f->plus)
		f->sprinted += ft_sputnchar(&f->str[f->sprinted], '+', max_size(f, 1));
	if (f->space && !f->plus)
		f->sprinted += ft_sputnchar(&f->str[f->sprinted], ' ', max_size(f, 1));
	if (f->minus)
		f->sprinted += ft_sputnchar(&f->str[f->sprinted], '-', max_size(f, 1));
	if (f->zero && (!f->minus || f->minus == FROM_NEGATIVE_WIDTH))
		f->sprinted += ft_sputnchar(&f->str[f->sprinted], '0', max_size(f, 1));
	while (format[*i] && ft_strchr(FLAGS, format[*i]))
		(*i)++;
}

static void	sprint_width(const char *format, int *i, t_sformat *f)
{
	if (f->width)
		f->sprinted += ft_snputnbr_base(&f->str[f->sprinted], f->width,
				"0123456789", f->size - f->sprinted);
	if (format[*i] == '*')
		(*i)++;
	else
		while (ft_isdigit(format[*i]))
			(*i)++;
}

static void	sprint_precision(const char *format, int *i, t_sformat *f)
{
	if (f->precision >= 0)
	{
		f->sprinted += ft_sputnchar(&f->str[f->sprinted], '.', max_size(f, 1));
		(*i)++;
		f->sprinted += ft_snputnbr_base(&f->str[f->sprinted], f->precision,
				"0123456789", f->size - f->sprinted);
		if (format[*i] == '*')
			(*i)++;
		else
			while (ft_isdigit(format[*i]))
				(*i)++;
	}
	else if (f->precision == NEGATIVE_PRECISION)
		(*i) += 2;
}
