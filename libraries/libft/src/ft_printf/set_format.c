/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_format.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 19:27:21 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/02 20:16:30 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	set_flags(const char *format, int *i, t_format *f);
static void	set_width(const char *format, int *i, t_format *f, va_list *ap);
static void	set_precision(const char *format, int *i, t_format *f, va_list *ap);
static void	set_specifier(const char *format, int *i, t_format *f);

int	set_format(const char *format, int *i, t_format *f, va_list *ap)
{
	int	i_original;

	i_original = *i;
	if (format[*i])
	{
		set_flags(format, i, f);
		if (format[*i])
		{
			set_width(format, i, f, ap);
			if (format[*i])
			{
				set_precision(format, i, f, ap);
				if (format[*i])
					set_specifier(format, i, f);
			}
		}
	}
	return (*i - i_original);
}

static void	set_flags(const char *format, int *i, t_format *f)
{
	while (1)
	{
		if (format[*i] == '#')
			f->hash = 1;
		else if (format[*i] == '+')
			f->plus = 1;
		else if (format[*i] == ' ')
			f->space = 1;
		else if (format[*i] == '-')
			f->minus = 1;
		else if (format[*i] == '0')
			f->zero = 1;
		else
			return ;
		(*i)++;
	}
}

static void	set_width(const char *format, int *i, t_format *f, va_list *ap)
{
	int	nbr;

	nbr = 0;
	if (format[*i] == '*')
	{
		nbr = va_arg(*ap, int);
		if (nbr < 0)
		{
			if (!f->minus)
				f->minus = FROM_NEGATIVE_WIDTH;
			nbr *= -1;
		}
		(*i)++;
	}
	else
	{
		while (ft_isdigit(format[*i]))
		{
			nbr = nbr * 10 + (format[*i] - '0');
			(*i)++;
		}
	}
	f->width = nbr;
	return ;
}

static void	set_precision(const char *format, int *i, t_format *f, va_list *ap)
{
	int	nbr;

	if (format[*i] == '.')
	{
		nbr = 0;
		(*i)++;
		if (format[*i] == '*')
		{
			nbr = va_arg(*ap, int);
			if (nbr < 0)
				nbr = NEGATIVE_PRECISION;
			(*i)++;
		}
		else
		{
			while (ft_isdigit(format[*i]))
			{
				nbr = nbr * 10 + (format[*i] - '0');
				(*i)++;
			}
		}
		f->precision = nbr;
	}
	return ;
}

static void	set_specifier(const char *format, int *i, t_format *f)
{
	char	*specifier;

	specifier = ft_strchr(SPECIFIERS, format[*i]);
	if (specifier)
	{
		f->specifier = *specifier;
		(*i)++;
	}
	else
		f->unresolved = 1;
	return ;
}
