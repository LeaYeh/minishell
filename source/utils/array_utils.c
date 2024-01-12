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

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

void	free_array(char **array, int len)
{
	int	i;

	if (array == NULL)
		return ;
	if (len == -1)
		len = get_array_len(array);
	if (len == 0)
		return ;
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
	while (list)
	{
		str_array[i] = ft_strdup(list->content);
		if (!str_array[i])
			return (free_array(str_array, -1), NULL);
		list = list->next;
		i++;
	}
	return (str_array);
}
