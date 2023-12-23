/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:02:03 by lyeh              #+#    #+#             */
/*   Updated: 2023/12/23 19:11:22 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

void	ft_show_env_list(t_shell *shell);
void	ft_show_token_list(t_shell *shell);
void	print_ast_bfs(t_ast *root);

#endif