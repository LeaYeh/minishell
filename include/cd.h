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

bool		is_absolute_path(char *path);
t_list_d	*create_component_list(char *path);

t_env *find_env_node(t_list *env_list, char *key, char *value);
char *replace_env_value(t_list *env_list, char *key, char *value);
bool update_pwd_env(t_list **env_list, char *new_pwd);
bool path_has_trailing_slash(char *path);
char *try_to_convert_absolute_to_relative_path(char *abs_path, char *pwd);
bool check_directory(char *cleaned_path, char *og_path);
size_t get_path_len_from_cmpnt_list(t_list_d *cmpnt_list);
size_t get_path_len_from_cmpnt_node(t_list_d *cmpnt_node);
char *convert_cmpnt_list_to_path(t_list_d *cmpnt_list);
char *convert_cmpnt_node_to_path(t_list_d *cmpnt_list, t_list_d *cmpnt_node);
char *get_ptr_to_last_cmpnt(char *path);
bool rm_dotdot_cmptnts(t_list_d **cmpnt_list, char *og_path);
void rm_dot_cmpnts(t_list_d **cmpnt_list);
bool reduce_multi_slash(char **str, size_t index);
bool convert_relative_to_absolute_path(char **curpath, char *pwd);
char *get_value_from_env(t_list *env_list, char *key);
bool is_dot_component(char *directory);

#endif
