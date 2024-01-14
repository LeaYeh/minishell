/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:59:32 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/11 21:36:50 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"

int	get_array_len(char **arr)
{
	int	i;

	if (!arr)
		return (0);
	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	ft_free_and_null((void **)&array);
}

char	**convert_list_to_string_array(t_list *list)
{
	char	**str_array;
	int		i;

	i = 0;
	str_array = ft_calloc(ft_lstsize(list) + 1, sizeof(char *));
	if (!str_array)
		return (NULL);
	while (list)
	{
		str_array[i] = ft_strdup(list->content);
		if (!str_array[i])
			return (free_array(str_array), NULL);
		list = list->next;
		i++;
	}
	return (str_array);
}
