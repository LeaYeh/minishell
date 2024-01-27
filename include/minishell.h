/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:43:22 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/17 10:11:52 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "defines.h"

bool	ft_init_shell(t_shell *shell, char **env);
bool	ft_append_env(t_list **env_list, char *key, char *value);

bool	mock_lexer(t_shell *shell);

char	*ft_get_token_type_str(int type);

int 	ft_exec_env(t_shell *shell);

#endif
