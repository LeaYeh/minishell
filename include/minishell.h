/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:43:22 by lyeh              #+#    #+#             */
/*   Updated: 2023/12/16 22:06:20 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "defines.h"

bool	ft_init_shell(t_shell *shell, char **env);
bool	mock_lexer(t_shell *shell);

char	*ft_get_token_type_str(int type);

void	ft_exec_env(t_shell *shell, char **args);

#endif
