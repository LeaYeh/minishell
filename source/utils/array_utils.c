/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:59:32 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/19 00:21:19 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"

int	get_array_len(char *arr[])
{
	int	i;

	if (!arr)
		return (0);
	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	free_array(char **array[])
{
	int	i;

	if (!array || !*array)
		return ;
	i = 0;
	while ((*array)[i])
	{
		ft_free_and_null((void **)&(*array)[i]);
		i++;
	}
	ft_free_and_null((void **)array);
}

char	**convert_list_to_string_array(t_list *list)
{
	char	**str_array;
	int		i;

	i = 0;
	str_array = (char **)malloc(
			(ft_lstsize_non_null(list) + 1) * sizeof(char *));
	if (!str_array)
		return (NULL);
	while (list)
	{
		if (list->content != NULL)
		{
			str_array[i] = ft_strdup(list->content);
			if (!str_array[i])
				return (free_array(&str_array), NULL);
			i++;
		}
		list = list->next;
	}
	str_array[i] = NULL;
	return (str_array);
}

char	**append_string_array(char *array[], char *str)
{
	char	**new_array;
	int		i;

	new_array = (char **)malloc(
			(get_array_len(array) + (str != NULL) + 1) * sizeof(char *));
	if (!new_array)
		return (free_array(&array), NULL);
	i = 0;
	while (array && array[i])
	{
		new_array[i] = ft_strdup(array[i]);
		if (!new_array[i])
			return (free_array(&new_array), free_array(&array), NULL);
		i++;
	}
	free_array(&array);
	if (str)
	{
		new_array[i] = ft_strdup(str);
		if (!new_array[i])
			return (free(new_array), NULL);
		i++;
	}
	new_array[i] = NULL;
	return (new_array);
}
