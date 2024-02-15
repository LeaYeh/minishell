/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 09:43:44 by ldulling          #+#    #+#             */
/*   Updated: 2024/01/20 02:29:25 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

// Enums should be used in such a case bc it allows the compiler to enforce that only values from this enumeration are used.
// TODO: Go through all enums and if an argument of a function can only be an enum, modify like here.
// Don't do word splitting for heredoc.
int	ft_expander(char *str, t_list **lst, t_shell *shell, t_expander_op op_mask)
{
	char	*new_str;

	if (!str)
		return (SUCCESS);
	new_str = ft_strdup(str);
	if (!new_str)
		return (MALLOC_ERROR);
	if (is_bad_substitution(new_str, op_mask))
		return (free(new_str), BAD_SUBSTITUTION);
	if (!expand(&new_str, lst, shell, op_mask))
		return (free(new_str), MALLOC_ERROR);
	if (!ft_lstnew_back(lst, new_str))
		return (free(new_str), MALLOC_ERROR);
	return (SUCCESS);
}
