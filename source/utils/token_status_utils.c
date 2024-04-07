/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_status_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 23:53:21 by lyeh              #+#    #+#             */
/*   Updated: 2024/02/17 23:53:22 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"

t_tok	*get_token_from_list(t_list *token_list)
{
	if (!token_list)
		return (NULL);
	return ((t_tok *)token_list->content);
}

t_tok_typ	get_token_type_from_list(t_list *token_list)
{
	if (!token_list)
		return (T_NONE);
	return (((t_tok *)token_list->content)->type);
}

char	*get_token_data_from_list(t_list *token_list)
{
	if (!token_list)
		return (NULL);
	return (((t_tok *)token_list->content)->data);
}
