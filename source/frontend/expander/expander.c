/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 09:43:44 by ldulling          #+#    #+#             */
/*   Updated: 2024/03/30 12:24:00 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

int	expander(char *str, t_list **lst, t_shell *shell, t_expander_op op_mask)
{
	char	*new_str;

	if (!str)
		return (SUCCESS);
	new_str = ft_strdup(str);
	if (!new_str)
		return (MALLOC_ERROR);
	if (is_bad_substitution(new_str, op_mask))
		return (free(new_str), BAD_SUBSTITUTION);
	if (!ft_lstnew_back(lst, new_str))
		return (free(new_str), MALLOC_ERROR);
	if (!handle_expansion(lst, shell, op_mask))
		return (MALLOC_ERROR);
	return (SUCCESS);
}

bool	handle_expansion(t_list **lst, t_shell *shell, t_expander_op op_mask)
{
	char	**base_str;
	t_list	*task_list;

	base_str = (char **)&(*lst)->content;
	task_list = NULL;
	if (!set_parameter_expansion_info(&task_list, base_str, op_mask) || \
		!handle_parameter_expansion(&task_list, shell) || \
		!handle_word_splitting(lst, op_mask, &task_list) || \
		!set_quote_wildcard_expansion_info(&task_list, *lst, op_mask) || \
		!handle_quote_removal(&task_list) || \
		!handle_wildcard_expansion(lst, &task_list))
		return (ft_lstclear(&task_list, (void *)free_expander_task), false);
	ft_lstclear(&task_list, (void *)free_expander_task);
	return (true);
}
