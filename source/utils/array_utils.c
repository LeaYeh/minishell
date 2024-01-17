/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:59:32 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/15 12:24:30 by ldulling         ###   ########.fr       */
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

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
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
		if (list->content != NULL)
		{
			str_array[i] = ft_strdup(list->content);
			if (!str_array[i])
				return (free_array(str_array), NULL);
			i++;
		}
		list = list->next;
	}
	return (str_array);
}

bool	append_string_array(char ***array, char *str)
{
	char	**tmp;
	int		i;

	tmp = *array;
	*array = ft_calloc(get_array_len(tmp) + 2, sizeof(char *));
	if (!*array)
		return (false);
	i = 0;
	while (tmp && tmp[i])
	{
		(*array)[i] = ft_strdup(tmp[i]);
		if (!(*array)[i])
			return (free_array(tmp), false);
		i++;
	}
	(*array)[i] = ft_strdup(str);
	if (!(*array)[i])
		return (free_array(tmp), false);
	free_array(tmp);
	return (true);
}
