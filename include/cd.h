/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 22:29:05 by ldulling          #+#    #+#             */
/*   Updated: 2024/01/20 14:06:06 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CD_H
# define CD_H

# include "defines.h"

/* cd_errors.c */
int			handle_cd_error(int error, char *target_dir);

/* cd_utils.c */
bool		check_dir(char *dir, char *target_dir);
bool		ensure_path_not_empty(char **final_path);
bool		is_abs_path(char *path);

/* cmpnt_list.c */
t_list_d	*get_abs_path_cmpnt_list(char *pwd, char *target_dir);
t_list_d	*create_cmpnt_list(char *path);
char		*convert_cmpnt_node_to_path(
				t_list_d *cmpnt_list, t_list_d *cmpnt_node);

/* cmpnt_list_utils.c */
int			check_cmpnt_node_path(
				t_list_d *cmpnt_list, t_list_d *cmpnt_node, char *target_dir);
bool		is_root_cmpnt_node(t_list_d *cmpnt_node);
int			get_path_len_from_cmpnt_node(
				t_list_d *cmpnt_list, t_list_d *cmpnt_node);

/* dot_cmpntns.c */
int			handle_dot_cmpnts(t_list_d **cmpnt_list, char *target_dir);

/* get_target_dir.c */
char		*get_target_dir(char *args[], t_list *env_list);

/* process_path.c */
int			set_final_path(char **final_path, char **new_pwd, char *target_dir);

/* update_pwd_env.c */
bool		update_pwd_env(t_list **env_list, char *new_pwd);

#endif
