/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:02:03 by lyeh              #+#    #+#             */
/*   Updated: 2023/12/31 18:33:47 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include "defines.h"

void	ft_show_env_list(t_shell *shell);
void	ft_show_token_list(t_shell *shell);
void	print_ast_bfs(t_ast *root);
void	print_cmd_table_list(t_list_d *cmd_table_list);
void	print_cmd_table(t_cmd_table *cmd_table);

/* Expander */
bool	print_expanded_cmd_table_list(t_shell *shell);

#endif