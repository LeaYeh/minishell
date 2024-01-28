/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_special_param.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:20:26 by ldulling          #+#    #+#             */
/*   Updated: 2024/01/28 02:12:54 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

bool	expand_exit_code(char **str, size_t *i, int exit_code)
{
	char	*exit_code_str;
	size_t	replace_len;

	exit_code_str = ft_itoa(exit_code);
	if (!exit_code_str)
		return (false);
	replace_len = count_replace_len(&(*str)[*i]);
	if (!ft_rplc_part_of_str(str, exit_code_str, *i, replace_len))
		return (free(exit_code_str), false);
	*i += ft_strlen(exit_code_str);
	return (free(exit_code_str), true);
}
