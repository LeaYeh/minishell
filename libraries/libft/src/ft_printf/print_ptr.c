/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 19:27:12 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/17 18:08:57 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_nullptr(t_format *f);
static int	ptrlen(size_t ptr);
static int	fullptrlen(int len_ptr, t_format *f);
static int	puthex(size_t ptr, t_format *f);

int	print_ptr(size_t ptr, t_format *f)
{
	int	len_ptr;
	int	len_full;
	int	printed;

	if (!ptr)
		return (print_nullptr(f));
	printed = 0;
	len_ptr = ptrlen(ptr);
	len_full = fullptrlen(len_ptr, f);
	if (!f->minus && f->width > len_full && !(f->zero && f->precision < 0))
		printed += ft_putnchar_fd(' ', f->width - len_full, f->fd);
	if (f->plus)
		printed += ft_putnchar_fd('+', 1, f->fd);
	else if (f->space)
		printed += ft_putnchar_fd(' ', 1, f->fd);
	printed += ft_putnstr_fd("0x", 2, f->fd);
	if (f->precision > len_ptr)
		printed += ft_putnchar_fd('0', f->precision - len_ptr, f->fd);
	else if (f->zero && !f->minus && f->precision < 0 && f->width > len_full)
		printed += ft_putnchar_fd('0', f->width - len_full, f->fd);
	printed += puthex(ptr, f);
	if (f->minus && f->width > len_full)
		printed += ft_putnchar_fd(' ', f->width - len_full, f->fd);
	return (printed);
}

static int	print_nullptr(t_format *f)
{
	int	len;
	int	printed;

	len = ft_strlen(NULL_PRINTOUT_PTR);
	printed = 0;
	if (!f->minus && f->width > len)
		printed += ft_putnchar_fd(' ', f->width - len, f->fd);
	printed += ft_putnstr_fd(NULL_PRINTOUT_PTR, len, f->fd);
	if (f->minus && f->width > len)
		printed += ft_putnchar_fd(' ', f->width - len, f->fd);
	return (printed);
}

static int	ptrlen(size_t ptr)
{
	int	len_ptr;

	len_ptr = 0;
	while (ptr)
	{
		ptr /= 16;
		len_ptr++;
	}
	return (len_ptr);
}

static int	fullptrlen(int len_ptr, t_format *f)
{
	int	len_full;

	len_full = len_ptr;
	if (len_full < f->precision)
		len_full = f->precision;
	if (f->plus || f->space)
		len_full++;
	len_full += ft_strlen("0x");
	return (len_full);
}

static int	puthex(size_t ptr, t_format *f)
{
	int	printed;

	printed = 0;
	if (ptr >= 16)
		printed += puthex(ptr / 16, f);
	ptr %= 16;
	if (ptr >= 10)
		printed += ft_putnchar_fd(ptr - 10 + 'a', 1, f->fd);
	else
		printed += ft_putnchar_fd(ptr + '0', 1, f->fd);
	return (printed);
}
