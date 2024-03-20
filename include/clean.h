/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 19:06:22 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/05 16:26:06 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEAN_H
# define CLEAN_H

# include "defines.h"

void	clean_shell(t_shell *shell);
void	clean_and_exit_shell(t_shell *shell, int exit_code, char *msg);
void	free_env_node(t_env *env);
void	reset_submodule_variable(t_shell *shell);

#endif
