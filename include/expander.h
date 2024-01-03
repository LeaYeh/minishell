/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 23:25:46 by ldulling          #+#    #+#             */
/*   Updated: 2024/01/03 01:41:59 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "defines.h"

# define GET	0
# define TOGGLE	1
# define RESET	2

/* bad_substitution.c */
bool	bad_substitution(char *str);

/* expander.c */
bool	ft_expander(char **str, t_shell *shell);
void	skip_to_dollar_not_in_single_quotes(char *str, size_t *i);

/* expander_utils.c */
void	free_and_reset(char *dup);
bool	is_open_pair(unsigned char c, int operation);

/* parameter_expansion.c */
bool	parameter_expansion(char **str, t_shell *shell);

/* quote_removal.c */
bool	quote_removal(char **str);

/* replace_part_of_str.c */
bool	replace_part_of_str(
			char **str, char *replacement, size_t start, size_t len);
char	*join_front_and_replacement(char *str, char *replacement, size_t start);
char	*join_new_and_back(char *str_new, char *str, size_t end);

#endif
