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
int			handle_chdir_error(int error, char *target_dir);
int			handle_getcwd_error(int error, char *target_dir);

/* cd_utils.c */
bool		check_dir(char *dir, char *target_dir);
bool		ensure_path_not_empty(char **final_path);
bool		is_abs_path(char *path);

/* cmpnt_list.c */
t_list_d	*get_abs_path_cmpnt_list(char *pwd, char *target_dir);
t_list_d	*create_cmpnt_list(char *path);
bool		create_root_cmpnt_nodes(t_list_d **cmpnt_list, char *path);
char		*convert_cmpnt_node_to_path(t_list_d *cmpnt_list,
				t_list_d *cmpnt_node);
void		convert_root_cmpnt_nodes_to_path(
				t_list_d **cmpnt_list, t_list_d *cmpnt_node,
				char *path, size_t *i);

/* cmpnt_list_utils.c */
int			check_cmpnt_node_path(
				t_list_d *cmpnt_list, t_list_d *cmpnt_node, char *target_dir);
bool		is_root_cmpnt_node(t_list_d *cmpnt_node);
size_t		get_path_len_from_cmpnt_node(
				t_list_d *cmpnt_list, t_list_d *cmpnt_node);

/* dot_cmpntns.c */
int			handle_dot_cmpnts(t_list_d **cmpnt_list, char *target_dir);
void		rm_dot_cmpnts(t_list_d **cmpnt_list);
int			rm_dotdot_cmptnts(t_list_d **cmpnt_list, char *target_dir);
bool		is_dot_cmpnt(char *dir);

/* environment_utils.c */
t_env		*find_env_node(t_list *env_list, char *key, char *value);
char		*get_value_from_env_list(t_list *env_list, char *key);
void		remove_env_node(t_list **env_list, char *key, char *value);
char		*replace_env_value(t_list *env_list, char *key, char *value);

/* get_target_dir.c */
char		*get_target_dir(char **args, t_list *env_list);

/* process_path.c */
int			set_final_path(char **final_path, char **new_pwd, char *target_dir);
int			simplify_path(char **new_path, char *target_dir, char *pwd);
char		*try_to_convert_abs_to_rel_path(char *abs_path, char *pwd);

/* update_pwd_env.c */
bool		update_pwd_env(t_list **env_list, char *new_pwd);
bool		handle_existing_pwd(t_list **env_list, char *old_pwd);
bool		handle_non_existing_pwd(t_list **env_list, char *new_pwd);

#endif
