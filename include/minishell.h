/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:43:22 by lyeh              #+#    #+#             */
/*   Updated: 2023/12/17 20:47:50 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "defines.h"

bool	ft_init_shell(t_shell *shell, char **env);
bool	mock_lexer(t_shell *shell);

/* Lexer */
bool	ft_lexer(t_shell *shell);

char	*ft_get_token_type_str(int type);

void	ft_exec_env(t_shell *shell, char **args);

#endif
