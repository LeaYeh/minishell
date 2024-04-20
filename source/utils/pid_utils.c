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

pid_t	getpid_from_proc(void)
{
	DIR				*dir;
	struct dirent	*file;
	pid_t			pid;

	dir = opendir("/proc/self/task");
	if (dir == NULL)
		return (0);
	pid = 0;
	file = readdir(dir);
	while (file != NULL && pid == 0)
	{
		pid = ft_atoi(file->d_name);
		file = readdir(dir);
	}
	closedir(dir);
	return (pid);
}
