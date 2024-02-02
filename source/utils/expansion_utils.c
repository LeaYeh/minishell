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
	t_list	*tmp_list;

	ret = SUCCESS;
	while (list)
	{
		tmp_list = NULL;
		ret = ft_expander(list->content, &tmp_list, shell, E_EXPAND | E_RM_QUOTES);
		if (ret != SUCCESS)
		{
			ft_lstclear(&tmp_list, free);
			break ;
		}
		else
			ft_lstadd_back(expanded_list, tmp_list);
		list = list->next;
	}
	return (ret);
}

int	expand_array(t_shell *shell, char ***array)
{
	t_list	*expanded_list;
	int		i;
	int		ret;
	t_list	*tmp_list;

	expanded_list = NULL;
	ret = SUCCESS;
	i = 0;
	while ((*array)[i] && ret == SUCCESS)
	{
		tmp_list = NULL;
		ret = ft_expander((*array)[i++], &tmp_list, shell, E_EXPAND | E_RM_QUOTES);
		if (ret == MALLOC_ERROR)
			return (ft_lstclear(&tmp_list, free),
				ft_lstclear(&expanded_list, free), ret);
		else
			ft_lstadd_back(&expanded_list, tmp_list);
	}
	if (ret == BAD_SUBSTITUTION)
		ft_lstclear(&expanded_list, free);
	free_array(array);
	*array = convert_list_to_string_array(expanded_list);
	if (!*array)
		return (ft_lstclear(&expanded_list, free), MALLOC_ERROR);
	return (ft_lstclear(&expanded_list, free), ret);
}
