/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 19:57:56 by lyeh              #+#    #+#             */
/*   Updated: 2023/12/10 01:33:50 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef enum e_action_type
{
	A_REJECT = -1,
	A_ACCEPT = 0,
	A_SHIFT,
	A_REDUCE
}	t_action_type;

typedef enum e_rules
{
	R_PIPE_SEQ = 100,
	R_AND_OR,
	R_SUBSHELL,
	R_CMD,
	R_RED_LIST,
	R_SIMPLE_CMD,
	R_CMD_NAME,
	R_CMD_WORD,
	R_CMD_PREFIX,
	R_CMD_SUFFIX,
	R_IO_RED,
	R_IO_FILE,
	R_FILENAME,
	R_IO_HERE,
	R_HERE_END
}	t_rules;

typedef enum e_token_type
{
	T_END = -2,
	T_WORD = 0,
	T_ASSIGNMENT_WORD,
	T_RED_IN,
	T_RED_OUT,
	T_HEREDOC,
	T_APPEND,
	T_PIPE,
	T_OR,
	T_AND,
	T_L_BRACKET,
	T_R_BRACKET
}	t_token_type;

#endif
