/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:14:48 by lyeh              #+#    #+#             */
/*   Updated: 2024/05/05 13:28:52 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"

void	print_error(char *format, ...)
{
	char	buffer[ERROR_MAX_LEN];
	va_list	ap;

	va_start(ap, format);
	ft_vsnprintf(buffer, ERROR_MAX_LEN, format, ap);
	va_end(ap);
	ft_dprintf(STDERR_FILENO, "%s", buffer);
}
