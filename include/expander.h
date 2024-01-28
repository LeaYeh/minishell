/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 23:25:46 by ldulling          #+#    #+#             */
/*   Updated: 2024/01/27 22:07:39 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "defines.h"

enum e_is_open_pair_operations
{
	GET = 0,
	TOGGLE,
	RESET,
	CLEAN
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
int		ft_expander(char *str, t_list **lst, t_shell *shell);

/* expander_utils.c */
size_t	count_offset(char *str);
size_t	count_replace_len(char *str);
bool	is_open_pair(unsigned char c, int operation);
void	skip_to_dollar_not_in_single_quotes(char *str, size_t *i);

/* parameter_expansion.c */
bool	parameter_expansion(char **str, t_shell *shell);
bool	expand_parameter(char **str, size_t *i, t_shell *shell);
bool	handle_dollar_quotes(char **str, size_t *i);

/* quote_removal.c */
bool	quote_removal(char **str);

#endif
