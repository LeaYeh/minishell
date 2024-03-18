/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:36:21 by lyeh              #+#    #+#             */
/*   Updated: 2024/03/18 18:36:22 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPORT_H
# define EXPORT_H

# include "defines.h"

/* export.c */

bool	handle_var_export(char *str, t_list **env_list);
void	change_export_flag(t_list *env_list, char *key, t_export export);

/* print_exported_env.c */
int		print_exported_env(t_list *env_list);
int		get_total_export_printout_len(t_list *env_list,
			int prefix_len, int format_len);
int		get_env_str_len(t_env *env_node, int prefix_len, int format_len);
void	fill_export_printout(t_list *env_list, char *export_printout,
			int prefix_len, int format_len);
t_env	*get_next_env_node(t_list *env_list, char *prev_key);

#endif
