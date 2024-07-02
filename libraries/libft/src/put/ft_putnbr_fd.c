/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:12:10 by ldulling          #+#    #+#             */
/*   Updated: 2023/09/24 16:22:26 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	putnbr_fd_recursive(int n, int fd);

void	ft_putnbr_fd(int n, int fd)
{
	if (fd < 0)
		return ;
	if (n == INT_MIN)
	{
		if (write(fd, "-2147483648", 11) == -1)
			return ;
	}
	else if (n < 0)
	{
		if (write(fd, "-", 1) == -1)
			return ;
		putnbr_fd_recursive(-n, fd);
	}
	else
		putnbr_fd_recursive(n, fd);
	return ;
}

static void	putnbr_fd_recursive(int n, int fd)
{
	if (n >= 10)
		putnbr_fd_recursive(n / 10, fd);
	n = n % 10 + '0';
	if (write(fd, &n, 1) == -1)
		return ;
	return ;
}
