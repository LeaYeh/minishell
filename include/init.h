/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:37:34 by lyeh              #+#    #+#             */
/*   Updated: 2024/03/18 18:37:35 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "defines.h"

bool	init_shell(t_sh *shell);
bool	setup_env_list(t_sh *shell);
bool	setup_default_env_list(t_sh *shell);

#endif
