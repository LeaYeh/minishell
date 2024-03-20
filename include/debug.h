/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:02:03 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/11 21:21:46 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include "defines.h"

void	print_env_list(t_shell *shell);
void	print_token_list(t_list *token_list);
void	print_ast_bfs(t_ast *root);
void	print_cmd_table_list(t_list_d *cmd_table_list);
void	print_cmd_table(t_cmd_table *cmd_table);
void	print_final_cmd_table(t_final_cmd_table *final_cmd_table);

/* Expander */
bool	print_expanded_cmd_table_list(t_shell *shell);

#endif