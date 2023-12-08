/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 19:57:56 by lyeh              #+#    #+#             */
/*   Updated: 2023/12/08 21:53:20 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef enum e_token_type
{
	T_END = -2,
	T_WORD = 0,
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
