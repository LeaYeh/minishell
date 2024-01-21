/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 01:17:55 by ldulling          #+#    #+#             */
/*   Updated: 2024/01/20 01:23:59 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "utils.h"

int	expand_list(t_shell *shell, t_list *list, t_list **expanded_list)
{
	int		ret;

	ret = SUCCESS;
	while (list && ret == SUCCESS)
	{
		ret = ft_expander(list->content, expanded_list, shell);
		list = list->next;
	}
	return (ret);
}

int	expand_array(t_shell *shell, char ***array)
{
	t_list	*expanded_list;
	int		i;
	int		ret;

	expanded_list = NULL;
	i = 0;
	while ((*array)[i])
	{
		ret = ft_expander((*array)[i], &expanded_list, shell);
		if (ret != SUCCESS)
		{
			ft_lstclear(&expanded_list, free);
			if (ret == SUBSHELL_ERROR)
				return (ret);
			else if (ret == BAD_SUBSTITUTION)
				break ;
		}
		i++;
	}
	free_array(array);
	*array = convert_list_to_string_array(expanded_list);
	ft_lstclear(&expanded_list, free);
	if (!*array)
		return (SUBSHELL_ERROR);
	return (ret);
}
