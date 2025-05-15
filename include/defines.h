/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:56:26 by lyeh              #+#    #+#             */
/*   Updated: 2024/05/30 23:48:09 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# ifndef _DEFAULT_SOURCE
#  define _DEFAULT_SOURCE
# endif

# include <dirent.h>
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

# ifndef PARSING_TABLE
#  define PARSING_TABLE		0
#  define DEFINITIONS_OK	false
# else
#  define DEFINITIONS_OK	true
# endif

# ifndef WELCOME_ART1
#  define WELCOME_ART1		""
# endif

# ifndef WELCOME_ART2
#  define WELCOME_ART2		""
# endif

# define PROGRAM_NAME		"crash"
# if NO_COLOR
#  define PRETTY_PROG_NAME	"🌊rash"
# else
#  define PRETTY_PROG_NAME	"\e[3;34m🌊\e[0m\e[1;34mrash\e[0m"
# endif

# if NO_COLOR
#  define PROMPT			"🌊rash$ "
#  define HEREDOC_PROMPT	"> "
# else
// '🌊' is a 4-byte character, but only takes up width of 2 characters ->
// use hexcode of '🌊' to mark 2 bytes as invisible characters
#  define PROMPT			\
	"\1\e[3;34m\2\xf0\x9f\1\x8c\x8a\2\1\e[0m\2\1\e[1;34m\2rash$\1\e[0m\2 "
#  define HEREDOC_PROMPT	"\e[1;37m> \e[0m"
# endif

# define EXIT_MSG			"exit\n"

# define WELCOME_MSG		"\
                    ╭───────────🌊🌊🌊───────────╮\n\
                    │  Dive deep into the shell  │\n\
                    ╰───────────🌊🌊🌊───────────╯\n"

# if NO_COLOR
#  define VALERIA_MSG		"\
           Big thank you to @ValeriaGart for the pixel art!\n"
# else
#  define VALERIA_MSG		"\
           Big thank you to \e[1m@ValeriaGart\e[0m for the pixel art!\n"
# endif

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
# define FORK_ERROR			254

/* Text-Style Escape Codes */
# if NO_COLOR
#  define STY_RES			""
#  define STY_BOL			""
#  define STY_ITA			""
#  define STY_UND			""
#  define STY_RED			""
#  define STY_GRE			""
#  define STY_YEL			""
#  define STY_BLU			""
#  define STY_MAG			""
#  define STY_CYA			""
#  define STY_WHI			""
#  define STY_GRA			""
#  define STY_WHI_BRI		""
#  define STY_BLA_BG		""
#  define STY_RED_BG		""
#  define STY_GRE_BG		""
#  define STY_YEL_BG		""
#  define STY_BLU_BG		""
#  define STY_MAG_BG		""
#  define STY_CYA_BG		""
#  define STY_WHI_BG		""
#  define STY_GRA_BG		""
#  define STY_WHI_BRI_BG	""
# else
#  define STY_RES			"\e[0m"
#  define STY_BOL			"\e[1m"
#  define STY_ITA			"\e[3m"
#  define STY_UND			"\e[4m"
#  define STY_RED			"\e[31m"
#  define STY_GRE			"\e[32m"
#  define STY_YEL			"\e[33m"
#  define STY_BLU			"\e[34m"
#  define STY_MAG			"\e[35m"
#  define STY_CYA			"\e[36m"
#  define STY_WHI			"\e[37m"
#  define STY_GRA			"\e[90m"
#  define STY_WHI_BRI		"\e[97m"
#  define STY_BLA_BG		"\e[41m"
#  define STY_RED_BG		"\e[41m"
#  define STY_GRE_BG		"\e[42m"
#  define STY_YEL_BG		"\e[43m"
#  define STY_BLU_BG		"\e[44m"
#  define STY_MAG_BG		"\e[45m"
#  define STY_CYA_BG		"\e[46m"
#  define STY_WHI_BG		"\e[47m"
#  define STY_GRA_BG		"\e[100m"
#  define STY_WHI_BRI_BG	"\e[107m"
# endif

/* Symbols */
# define WORD_SEPERATORS	" \t\n"
# define QUOTES				"'\""
# define OPENING_BRACE		'{'
# define CLOSING_BRACE		'}'
# define DOLLAR_BRACE		"${"

/* Parsing Table */
# define PT_COL_NUM			5
# define PT_ROW_NUM			192
# define UNDEFINED_STATE	-1

/* User Input */
# define MAX_INPUT_RETRIES	5

/* Export */
# define EXPORT_PREFIX		"export "

/* Error Messages */
# define ERROR_MAX_LEN 131072
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
	HD_SUCCESS		= 0,
	HD_ABORT,
	HD_ERROR
}	t_hd_st;

typedef enum e_signal_state
{
	SIG_DEFAULT		= 0,
	SIG_IGNORE,
	SIG_STANDARD,
	SIG_RECORD
}	t_sig;

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
	T_L_PAREN,
	T_R_PAREN
}	t_tok_typ;

typedef enum e_parsing_table_column
{
	PT_COL_STATE	= 0,
	PT_COL_ELEMENT,
	PT_COL_ACTION,
	PT_COL_NEXT_STATE,
	PT_COL_NUM_REDUCED
}	t_pt_col;

typedef enum e_parser_element
{
	P_END			= -2,
	P_NONE			= -1,
	P_WORD			= 0,
	P_ASSIGNMENT_WORD,
	P_RED_IN,
	P_RED_OUT,
	P_PIPE,
	P_HERE_DOC,
	P_APPEND,
	P_OR,
	P_AND,
	P_L_PAREN,
	P_R_PAREN,
	P_AND_OR		= 100,
	P_PIPE_SEQ,
	P_CMD,
	P_SUBSHELL,
	P_SIMPLE_CMD,
	P_CMD_NAME,
	P_CMD_WORD,
	P_CMD_PREFIX,
	P_CMD_SUFFIX,
	P_RED_LIST,
	P_IO_RED,
	P_IO_FILE,
	P_FILENAME,
	P_IO_HERE,
	P_HERE_END
}	t_prs_elem;

typedef enum e_parser_action
{
	A_ACCEPT		= 0,
	A_SHIFT			= 0b001,
	A_REDUCE		= 0b010,
	A_GOTO			= 0b100
}	t_prs_act;

typedef enum e_command_table_type
{
	C_NONE			= -1,
	C_SIMPLE_CMD	= 0,
	C_PIPE,
	C_AND,
	C_OR,
	C_SUBSHELL_START,
	C_SUBSHELL_END
}	t_ct_typ;

typedef enum e_open_pair_operator
{
	OP_GET			= 0,
	OP_SET,
	OP_RESET,
	OP_CLEAN
}	t_pair_op;

typedef enum e_expander_operator
{
	E_PARAM			= 0b0001,
	E_SPLIT_WORDS	= 0b0010,
	E_WILDCARD		= 0b0100,
	E_RM_QUOTES		= 0b1000
}	t_expd_op;

typedef enum e_expander_task_type
{
	ET_VAR			= 0,
	ET_VAR_NO_SPLIT,
	ET_EXIT_CODE,
	ET_SHELL_PID,
	ET_WILDCARD,
	ET_QUOTE
}	t_expd_tsk_typ;

typedef enum e_export
{
	EXPORT_NO		= 0,
	EXPORT_YES
}	t_expt;

typedef enum e_exit_argument_error
{
	EX_NO_ARGS		= -1,
	EX_NORM_ARGS	= 0,
	EX_TOO_MANY_ARGS,
	EX_NOT_NUMERIC
}	t_exit_err;

typedef struct s_environment_node
{
	char			*key;
	char			*value;
	t_expt			export;
}	t_env;

typedef struct s_token
{
	t_tok_typ		type;
	char			*data;
}	t_tok;

typedef struct s_expander_task
{
	t_expd_tsk_typ	type;
	char			**base_str;
	int				start;
	int				replace_len;
	char			*varname;
	int				result_len;
}	t_expd_tsk;

typedef struct s_abstract_syntax_tree
{
	t_prs_elem		element;
	char			*data;
	t_list			*children;
}	t_ast;

typedef struct s_relational_abstract_syntax_tree
{
	int				level;
	t_ast			*parent;
	t_ast			*current;
	t_list			*children;
}	t_rel_ast;

typedef struct s_parser_data
{
	t_list			*token_list;
	t_list			*state_stack;
	t_list			*parse_stack;
}	t_prs_data;

typedef struct s_parsing_table_node
{
	int				state;
	t_prs_elem		element;
	t_prs_act		action;
	int				next_state;
	int				num_reduced;
}	t_pt_node;

typedef struct s_io_redirection
{
	t_tok_typ		type;
	char			*filename;
	char			*here_end;
}	t_io_red;

typedef struct s_command_table
{
	int				id;
	t_ct_typ		type;
	int				subshell_level;
	int				read_fd;
	int				write_fd;
	t_list			*simple_cmd_list;
	t_list			*assignment_list;
	t_list			*io_red_list;
}	t_ct;

typedef struct s_final_command_table
{
	char			**simple_cmd;
	char			*exec_path;
	char			**assignment_array;
	char			**env;
	int				read_fd;
	int				write_fd;
}	t_fct;

typedef struct s_pipe
{
	int				pipe_fd[2];
	int				*read_fd;
	int				*write_fd;
}	t_pipe;

typedef struct s_shell
{
	bool			is_interactive;
	pid_t			pid;
	pid_t			subshell_pid;
	int				subshell_level;
	int				signal_record;
	t_pipe			old_pipe;
	t_pipe			new_pipe;
	unsigned char	exit_code;
	char			*input_line;
	t_list			*child_pid_list;
	t_list			*env_list;
	t_list			*token_list;
	t_list_d		*cmd_table_list;
	t_fct			*final_cmd_table;
	void			*builtin_allocation;
}	t_sh;

#endif
