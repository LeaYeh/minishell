/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 09:43:44 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/27 00:29:57 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * DOLLAR SIGN:
 *
 * [ ] Only expand
 * 		- valid names (combination of letters, numbers, and underscores; must start with a letter or an underscore)
 * 		- special arguments ($?)
 * 		- braces ${}
 *
 *   [ ] If no valid name is encountered, just leave $ in the string.
 *
 *     [ ] $ and space leaves one space with the $.
 *
 * [ ] $ directly followed by any quote should just leave the quoted string with the $ removed.
 *
 *   ( [ ] OUT OF SCOPE: $[Single quotes] allows escape sequences like \n for newline.
 * 			'\\' -> \\ ; $'\\' -> \ )
 *
 * [ ] Take everything that comes after a dollar sign until the first non-valid name or the ending brace }.
 *
 * QUOTES:
 *
 * [ ] Inside of double-quotes expansion still happens, inside of single quotes not.
 *
 * [ ] Empty strings like "" or '' should be kept as empty strings even after quote removal.
 * 			echo "" a != echo a
 * 		[?] However, why is this: '''' != '' ''
 *
 * WILDCARD:
 *
 */

#include "defines.h"

char	**ft_expander(char *data, t_shell *shell)
{

}
