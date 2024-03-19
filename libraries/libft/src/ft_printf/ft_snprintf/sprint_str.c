/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprint_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 19:27:17 by ldulling          #+#    #+#             */
/*   Updated: 2024/03/19 16:07:21 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	sprint(const char *str, int len, t_sformat *f);

void	sprint_str(const char *str, t_sformat *f)
{
	int	len;

	if (!str)
	{
		len = ft_strlen(NULL_PRINTOUT_STR);
		if (f->precision >= 0 && len > f->precision)
			len = 0;
		sprint(NULL_PRINTOUT_STR, len, f);
	}
	else
	{
		len = ft_strlen(str);
		if (f->precision >= 0 && len > f->precision)
			len = f->precision;
		sprint(str, len, f);
	}
}

static void	sprint(const char *str, int len, t_sformat *f)
{
	if (!f->minus && f->width > len)
		f->sprinted += ft_sputnchar(&f->str[f->sprinted], ' ',
				max_size(f, f->width - len));
	f->sprinted += ft_sputnstr(&f->str[f->sprinted], str, max_size(f, len));
	if (f->minus && f->width > len)
		f->sprinted += ft_sputnchar(&f->str[f->sprinted], ' ',
				max_size(f, f->width - len));
}
