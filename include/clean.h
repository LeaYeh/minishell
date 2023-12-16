/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 19:06:22 by lyeh              #+#    #+#             */
/*   Updated: 2023/12/16 15:44:07 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEAN_H
# define CLEAN_H

void	ft_clean_shell(t_shell *shell);
void	free_env_node(void *content);

#endif
