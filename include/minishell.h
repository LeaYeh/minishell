/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:43:22 by lyeh              #+#    #+#             */
/*   Updated: 2023/12/08 20:42:18 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include "ft_printf.h"

typedef struct s_env
{
	char			*key;
	char			*value;
}	t_env;

typedef struct s_token
{
	int				type;
	char			*data;
}	t_token;

typedef struct s_ast
{
	int				type;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

typedef struct s_io_redirect
{
	char			*redir_in;
	char			*redir_out;
}	t_io_redirect;

typedef struct s_cmd_table
{
	char			*cmd_name;
	char			*args;
	t_io_redirect	*io_redirect;
}	t_cmd_table;

typedef struct s_shell
{
	t_list			*env_list;
	t_list			*token_list;
	t_list			*final_cmd_table;
	t_ast			*ast;
	char			*input_line;
}	t_shell;

bool	ft_init_shell(t_shell *shell, char **env);

#endif
