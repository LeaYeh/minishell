/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 23:25:46 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/28 23:35:14 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "defines.h"

/* expander.c */
char	**ft_expander(char *data, t_shell *shell);

/* replace_part_of_str.c */
bool	replace_part_of_str(
			char **str, char *replacement, size_t start, size_t end);
char	*join_front_and_replacement(char *str, char *replacement, size_t start);
char	*join_new_and_back(char *str_new, char *str, size_t end);

#endif
