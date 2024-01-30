/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 19:26:03 by ldulling          #+#    #+#             */
/*   Updated: 2024/01/29 15:46:40 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_snprintf(char *str, size_t size, const char *format, ...)
{
	int			i;
	t_sformat	f;
	va_list		ap;

	if (!check_args(str, size, format, &f))
		return (f.sprinted);
	f.str = str;
	f.size = size - 1;
	va_start(ap, format);
	f.unresolved = 0;
	f.sprinted = 0;
	i = 0;
	while (format[i] && f.sprinted < (int) f.size)
	{
		reset_sformat(&f);
		parseandsprint(format, &i, &f, &ap);
		if (f.sprinted == -1)
			break ;
	}
	if (f.sprinted != -1)
		f.str[f.sprinted] = '\0';
	return (va_end(ap), f.sprinted);
}

bool	check_args(char *str, size_t size, const char *format, t_sformat *f)
{
	if (format == NULL)
	{
		if (size > 0)
			str[0] = '\0';
		f->sprinted = -1;
		return (false);
	}
	if (size == 0)
	{
		f->sprinted = 0;
		return (false);
	}
	return (true);
}
