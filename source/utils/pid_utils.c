/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 17:54:03 by ldulling          #+#    #+#             */
/*   Updated: 2024/04/20 17:54:05 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"

pid_t	getpid_asm(void)
{
	pid_t	pid;

	pid = 0;
	__asm__ volatile (
		"movq $39, %%rax;"
		"syscall;"
		"movl %%eax, %0;"
		: "=r" (pid)
		:
		: "rax", "eax", "memory"
	);
	return (pid);
}
