/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:56:26 by lyeh              #+#    #+#             */
/*   Updated: 2024/01/18 23:46:08 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include <fcntl.h>
# include <linux/limits.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include "ft_printf.h"

# define PROGRAM_NAME       "minishell"

/* Error codes */
# define SUCCESS            0
# define EXIT_SUCCESS       0
# define GENERAL_ERROR      1
# define BAD_SUBSTITUTION   2
// # define EXPAND_ERROR       2
# define MISUSE_BUILTIN     2
# define CMD_EXEC_FAILED    126
# define CMD_NOT_FOUND      127
# define TERM_BY_SIGNAL     128
# define UNEXPECT_EXIT      128
# define EXIT_SIGTERM       130

/* Parsing Table */
# define PT_COL_SIZE        5
# define PT_ROW_SIZE        191
# define UNDEFINED_TYPE     -99
# define UNDEFINED_STATE    -1

# define STY_BLD				"\e[1m"
# define STY_UND				"\e[4m"
# define STY_RED				"\e[31m"
# define STY_GRN				"\e[32m"
# define STY_YEL				"\e[33m"
# define STY_BLU				"\e[34m"
# define STY_MAG				"\e[35m"
# define STY_CYN				"\e[36m"
# define STY_WHT				"\e[37m"
# define STY_GRY				"\e[90m"
# define STY_HWHT				"\e[97m"
# define STY_BLKB				"\e[41m"
# define STY_REDB				"\e[41m"
# define STY_GRNB				"\e[42m"
# define STY_YELB				"\e[43m"
# define STY_BLUB				"\e[44m"
# define STY_MAGB				"\e[45m"
# define STY_CYNB				"\e[46m"
# define STY_WHTB				"\e[47m"
# define STY_GRYB				"\e[100m"
# define STY_HWHTB				"\e[107m"
# define STY_RES				"\e[0m"

// TODO: Remove the color codes from the prompt before the evaluations
// # define PROMPT "\033[0;34m🌊>\033[0m"
# define PROMPT				"\033[1;32mminishell$ \033[0m"
# define HEREDOC_PROMPT		"\033[1;37m> \033[0m"
// # define PROMPT				"\001\033[1;32m\002minishell$ \001\033[0m\002"
// # define PROMPT				"minishell$ "

/* Lexer */
# define QUOTES				"'\""
# define TOK_SYMBOLS		"<>|&()"
# define T_UNINITIALIZED	-1		//TODO Replace with Lea's UNDEFINED_TYPE -99

/* Expander */
# define OPENING_BRACE '{'
# define CLOSING_BRACE '}'

/* Error Messages */
// TODO Add minishell name in the front of messages
# define ERROR_PARSER_SYNTAX				\
"%s: syntax error near unexpected token `%s'\n"
# define ERROR_HEREDOC_UNEXPECTED_EOF		\
"%s: warning: here-document delimited by end-of-file (wanted `%s')\n"
# define ERROR_EXPANDER_BAD_SUBSTITUTION	\
"%s: %s: bad substitution\n"

// TODO: Replace with OS error message
# define ERROR_REMOVE_FILE 			"%s: \
warning: failed to remove file `%s'\n"

extern const int	g_parsing_table[][PT_COL_SIZE];

typedef enum e_pt_col
{
	PT_COL_STATE = 0,
	PT_COL_TOKEN_TYPE,
	PT_COL_ACTION,
	PT_COL_NEXT_STATE,
	PT_COL_NUM_REDUCED
}	t_pt_col;

typedef enum e_action_type
{
	A_REJECT	= -2,
	A_ACCEPT	= 0,
	A_SHIFT		= 0b001,
	A_REDUCE	= 0b010,
	A_GOTO		= 0b100
}	t_action_type;

typedef enum e_rules
{
	R_AND_OR = 100,
	R_PIPE_SEQ,
	R_CMD,
	R_SUBSHELL,
	R_SIMPLE_CMD,
	R_CMD_NAME,
	R_CMD_WORD,
	R_CMD_PREFIX,
	R_CMD_SUFFIX,
	R_RED_LIST,
	R_IO_RED,
	R_IO_FILE,
	R_FILENAME,
	R_IO_HERE,
	R_HERE_END
}	t_rules;

typedef enum e_token_type
{
	T_END = -2,
	T_NONE = -1,
	T_WORD = 0,
	T_ASSIGNMENT_WORD,
	T_RED_IN,
	T_RED_OUT,
	T_PIPE,
	T_HERE_DOC,
	T_APPEND,
	T_OR,
	T_AND,
	T_L_BRACKET,
	T_R_BRACKET
}	t_token_type;

typedef enum e_cmdtable_type
{
	C_NONE			= -1,
	C_SIMPLE_CMD	= 0,
	C_PIPE,
	C_AND,
	C_OR,
	C_SUBSHELL_START,
	C_SUBSHELL_END
}	t_cmdtable_type;

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
	char			*data;
	t_list			*children;
}	t_ast;

// TODO: move this one to the test.h
typedef struct s_relation_ast
{
	int				level;
	t_ast			*parent;
	t_ast			*current;
	t_list			*children;
}	t_relation_ast;

typedef struct s_parser_data
{
	t_list			*token_list;
	t_list			*state_stack;
	t_list			*parse_stack;
}	t_parser_data;

typedef struct s_pt_node
{
	int				state;
	int				token_type;
	int				action;
	int				next_state;
	int				num_reduced;
}	t_pt_node;

typedef struct s_io_red
{
	int				type;
	char			*in_file;
	char			*out_file;
	char			*here_end;
	int				red_in;
	int				red_out;
}	t_io_red;

// TODO: Need to record each io_redirect in a list, need to touch the filename
// case: echo 1 | > out1 > out2 cat
// 		- if cmd_table with no cmd_name, just touch the filename in the io_red_list
// 		- in other cases, need execute the cmd_table with io redirect
typedef struct s_cmd_table
{
	int				id;
	int				subshell_level;
	// int				subshell_pid;
	// int				simple_cmd_pid;
	int				pipe_fd[2];
	int				pipe_read_fd;
	int				pipe_write_fd;
	int				type;
	t_list			*simple_cmd_list;
	t_list			*assignment_list;
	t_list			*io_red_list;
}	t_cmd_table;

typedef struct s_final_cmd_table
{
	char			**simple_cmd;
	char			*exec_path;
	char			**assignment_array;
	char			**envp;
}	t_final_cmd_table;

typedef struct s_shell
{
	int				pid;
	int				subshell_pid;
	int				subshell_level;
	int				exit_status;
	int				exit_code;
	t_list			*env_list;
	t_list			*token_list;
	t_list_d		*cmd_table_list;
	// t_ast			*ast;
	char			*input_line;
}	t_shell;

#endif
