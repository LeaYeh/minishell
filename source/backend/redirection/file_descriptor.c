/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_descriptor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 22:26:59 by ldulling          #+#    #+#             */
/*   Updated: 2024/04/04 22:26:59 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	safe_close(int *fd)
{
	if (*fd > STDERR_FILENO)
	{
		close(*fd);
		*fd = -1;
	}
}

void	replace_fd(int *from_end, int *to_end)
{
	if (*from_end == -1)
		return ;
	safe_close(to_end);
	*to_end = *from_end;
	*from_end = -1;
}
