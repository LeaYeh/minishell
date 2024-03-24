/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:56:26 by lyeh              #+#    #+#             */
/*   Updated: 2024/03/19 15:35:09 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <linux/limits.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sysexits.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

# ifndef TEST_MODE
#  define TEST_MODE false
# endif

# ifndef PARSING_TABLE
#  define DEFINITIONS_OK	false
# else
#  define DEFINITIONS_OK	true
# endif

# define PROGRAM_NAME		"crash"
# define PRETTY_PROG_NAME	"\e[3;34m🌊\e[0m\e[1;34mrash\e[0m"
# define PROMPT				"\e[3;34m🌊\e[0m\e[1;34mrash$\e[0m "

# define HEREDOC_PROMPT		"\e[1;37m> \e[0m"
# define EXIT_MSG			"exit\n"

/* Error Codes */
# define SUCCESS			0
# define EXIT_SUCCESS		0
# define GENERAL_ERROR		1
# define BAD_SUBSTITUTION	1
# define AMBIGUOUS_REDIR	1
# define SYNTAX_ERROR		2
# define MALLOC_ERROR		2
# define CMD_EXEC_FAILED	126
# define CMD_NOT_FOUND		127
# define UNEXPECT_EXIT		128
# define TERM_BY_SIGNAL		128
# define PREPROCESS_ERROR	195
# define BUILTIN_ERROR		196
# define FORK_ERROR			254

/* Text-Style Escape Codes */
# define STY_BLD			"\e[1m"
# define STY_UND			"\e[4m"
# define STY_RED			"\e[31m"
# define STY_GRN			"\e[32m"
# define STY_YEL			"\e[33m"
# define STY_BLU			"\e[34m"
# define STY_MAG			"\e[35m"
# define STY_CYN			"\e[36m"
# define STY_WHT			"\e[37m"
# define STY_GRY			"\e[90m"
# define STY_HWHT			"\e[97m"
# define STY_BLKB			"\e[41m"
# define STY_REDB			"\e[41m"
# define STY_GRNB			"\e[42m"
# define STY_YELB			"\e[43m"
# define STY_BLUB			"\e[44m"
# define STY_MAGB			"\e[45m"
# define STY_CYNB			"\e[46m"
# define STY_WHTB			"\e[47m"
# define STY_GRYB			"\e[100m"
# define STY_HWHTB			"\e[107m"
# define STY_RES			"\e[0m"

/* Symbols */
# define QUOTES				"'\""
# define EXPANDER_SYMBOLS	"$*\"'"
# define OPENING_BRACE		'{'
# define CLOSING_BRACE		'}'
# define DOLLAR_BRACE		"${"

/* Parsing Table */
# define PT_COL_SIZE		5
# define PT_ROW_SIZE		191
# define UNDEFINED_STATE	-1

/* Export */
# define EXPORT_PREFIX		"export "

/* Error Messages */
# define ERROR_LEXER_SYNTAX					\
"%s: syntax error: missing `%c'\n"
# define ERROR_PARSER_SYNTAX				\
"%s: syntax error near unexpected token `%s'\n"
# define ERROR_HEREDOC_UNEXPECTED_EOF		\
"%s: warning: here-document delimited by end-of-file (wanted `%s')\n"
# define ERROR_EXPANDER_BAD_SUBSTITUTION	\
"%s: %s: bad substitution\n"
# define ERROR_EXIT_TOO_MANY_ARGS			\
"%s: %s: too many arguments\n"
# define ERROR_EXIT_NUMERIC_ARG				\
"%s: %s: %s: numeric argument required\n"
# define ERROR_CD_TOO_MANY_ARGS				\
"%s: cd: too many arguments\n"
# define ERROR_CD_HOME_NOT_SET				\
"%s: cd: HOME not set\n"
# define ERROR_CD_OLDPWD_NOT_SET			\
"%s: cd: OLDPWD not set\n"
# define ERROR_EXPORT_INVALID_IDENTIFIER	\
"%s: export: `%s': not a valid identifier\n"
# define ERROR_REMOVE_FILE					\
"%s: warning: failed to remove file `%s'\n"
# define ERROR_CREATE_PIPE					\
"pipe error: Too many open files\n"
# define ERROR_CMD_NOT_FOUND				\
"%s: %s: command not found\n"
# define ERROR_CANNOT_EXEC_FILE				\
"%s: %s: cannot execute file: %s\n"
# define ERROR_AMBIGUOUS_REDIRECT			\
"%s: %s: ambiguous redirect\n"

/* Failure Messages */
# define MALLOC_FMSG						\
"malloc failed"

typedef enum e_heredoc_status
{
	HEREDOC_SUCCESS	= 0,
	HEREDOC_ABORT,
	HEREDOC_ERROR
}	t_heredoc_status;

typedef enum e_state
{
	SIG_DEFAULT		= 0,
	SIG_IGNORE,
	SIG_STANDARD,
	SIG_RECORD
}	t_state;

typedef enum e_pt_col
{
	PT_COL_STATE	= 0,
	PT_COL_TOKEN_TYPE,
	PT_COL_ACTION,
	PT_COL_NEXT_STATE,
	PT_COL_NUM_REDUCED
}	t_pt_col;

typedef enum e_action_type
{
	A_ACCEPT		= 0,
	A_SHIFT			= 0b001,
	A_REDUCE		= 0b010,
	A_GOTO			= 0b100
}	t_action_type;

typedef enum e_token_type
{
	T_END			= -2,
	T_NONE			= -1,
	T_WORD			= 0,
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

typedef enum e_is_open_pair_op
{
	OP_GET			= 0,
	OP_SET,
	OP_RESET,
	OP_CLEAN
}	t_is_open_pair_op;

typedef enum e_expander_op
{
	E_EXPAND		= 0b001,
	E_SPLIT_WORDS	= 0b010,
	E_RM_QUOTES		= 0b100
}	t_expander_op;

typedef enum e_expander_task_type
{
	ET_VAR			= 0,
	ET_VAR_NO_SPLIT,
	ET_EXIT_CODE,
	ET_QUOTE
}	t_expander_task_type;

typedef enum e_export
{
	EXPORT_NO		= 0,
	EXPORT_YES
}	t_export;

typedef enum e_exit_args_error
{
	EX_NO_ARGS		= -1,
	EX_NORM_ARGS	= 0,
	EX_TOO_MANY_ARGS,
	EX_NOT_NUMERIC,
}	t_exit_args_error;

typedef struct s_env
{
	char			*key;
	char			*value;
	t_export		export;
}	t_env;

typedef struct s_token
{
	int				type;
	char			*data;
}	t_token;

typedef struct s_expander_task
{
	t_expander_task_type	type;
	int						start;
	int						replace_len;
	char					*varname;
	int						result_len;
}	t_expander_task;

typedef struct s_ast
{
	int				type;
	char			*data;
	t_list			*children;
}	t_ast;

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
	char			*filename;
	char			*here_end;
}	t_io_red;

typedef struct s_cmd_table
{
	int				id;
	int				subshell_level;
	int				read_fd;
	int				write_fd;
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
	char			**env;
	int				read_fd;
	int				write_fd;
}	t_final_cmd_table;

typedef struct s_pipe
{
	int				pipe_fd[2];
	int				*read_fd;
	int				*write_fd;
}	t_pipe;

typedef struct s_shell
{
	pid_t				pid;
	pid_t				subshell_pid;
	int					subshell_level;
	int					signal_record;
	t_pipe				old_pipe;
	t_pipe				new_pipe;
	int					exit_code;
	char				*input_line;
	t_list				*child_pid_list;
	t_list				*env_list;
	t_list				*token_list;
	t_list_d			*cmd_table_list;
	t_final_cmd_table	*final_cmd_table;
}	t_shell;

#endif
