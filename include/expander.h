/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 23:25:46 by ldulling          #+#    #+#             */
/*   Updated: 2024/01/04 13:49:26 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "defines.h"

enum e_is_open_pair_operations
{
	GET = 0,
	TOGGLE,
	RESET
};

/* bad_substitution.c */
bool	bad_substitution(char *str);

/* expand_special_param.c */
bool	expand_exit_code(char **str, size_t *i, int exit_code);

/* expand_variable.c */
bool	expand_variable(char **str, size_t *i, size_t offset, t_list *env_list);
size_t	count_var_len(char *str);
char	*get_replacement(char *var, t_list *env_list);

/* expander.c */
bool	ft_expander(char **str, t_shell *shell);

/* expander_utils.c */
size_t	count_offset(char *str);
size_t	count_replace_len(char *str);
void	free_and_reset(char *str);
bool	is_open_pair(unsigned char c, int operation);
void	skip_to_dollar_not_in_single_quotes(char *str, size_t *i);

/* parameter_expansion.c */
bool	parameter_expansion(char **str, t_shell *shell);
bool	expand_parameter(char **str, size_t *i, t_shell *shell);
bool	handle_dollar_quotes(char **str, size_t *i);

/* quote_removal.c */
bool	quote_removal(char **str);

/* replace_part_of_str.c */
bool	replace_part_of_str(
			char **str, char *replacement, size_t start, size_t len);
char	*join_front_and_replacement(char *str, char *replacement, size_t start);
char	*join_new_and_back(char *str_new, char *str, size_t end);

#endif
