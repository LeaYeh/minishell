/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 11:45:40 by ldulling          #+#    #+#             */
/*   Updated: 2024/05/05 17:21:32 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
