/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 13:38:17 by lyeh              #+#    #+#             */
/*   Updated: 2023/12/17 13:48:35 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "defines.h"

bool	drop_num_stack(t_stack **stack, int num);

t_token	*init_token_node(int type, char *data);
void	free_token_node(void *content);

char	*ft_get_token_type_str(int type);

#endif