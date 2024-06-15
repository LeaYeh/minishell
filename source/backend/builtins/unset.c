/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:40:21 by lyeh              #+#    #+#             */
/*   Updated: 2024/03/18 17:40:22 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	exec_unset(char *args[], t_list **env_list)
{
	int	i;

	i = 1;
	while (args[i])
	{
		remove_env_node(env_list, args[i], NULL);
		i++;
	}
	return (SUCCESS);
}
