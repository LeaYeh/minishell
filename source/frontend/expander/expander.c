/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 09:43:44 by ldulling          #+#    #+#             */
/*   Updated: 2024/01/03 14:41:09 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * TEST CASES
 *
 * - Just for information about order of execution:
 *   bash-5.1$ e{ch,'|','|'}o
 *   > e|o e|o
 *
 *
 *   HERE_DOC:
 *
 * - bash-5.1$ cat << $a
 *   > abc
 *   > $a $a
 *   > echo $a
 *   > $a
 *   abc
 *   123 123
 *   echo 123
 *
 * - bash-5.1$ cat << $b
 *   > '$a'
 *   > '$b'
 *   > $b
 *   '123'
 *   '456'
 *   bash-5.1$ echo '$a'
 *   $a
 *
 *
 * [x] bash-5.1$ echo $"$aa"
 *
 *     bash-5.1$ echo $'$aa'
 *     $aa
 *
 * [x] bash-5.1$ echo "'$USER'"
 *     'ldulling'
 *
 * [x] bash-5.1$ ${USER}=abc
 *     bash: ldulling=abc: command not found
 *
 * [x] bash-5.1$ echo ${?}abc${abc.}
 *     bash: ${?}abc${abc.}: bad substitution
 *       -> Use the original str for the error message.
 *
 * [x] bash-5.1$ echo "${?}abc${abc.}"
 *     bash: ${?}abc${abc.}: bad substitution
 *     bash-5.1$ echo $"{?}abc${abc.}"
 *     bash: {?}abc${abc.}: bad substitution
 *     bash-5.1$ $USER$"USER${abc.}abc"
 *     bash: USER${abc.}abc: bad substitution
 *
*/

/*
 * QUESTIONS
 *
 * [ ] echo ${abc.$USER
 * 		At the moment it will just leave the string as is.
 *         -> Lexer should detect syntax error.
 *
 * [x] Where to handle the "%s: bad substitution" error message?
 *
 * [ ] This test case is terrible, bc it changes the command table:
 *     bash-5.1$ $abc 123
 *     bash: 123: command not found
 *
*/

/*
 * REQUIREMENTS
 *
 * DOLLAR SIGN:
 *
 * [x] Don't expand if $ is inside a single quote.
 * 		Double quote is okay.
 *
 * [x] Don't expand if $ is inside a single quote.
 * 		Double quote is okay.
 *
 * [x] Only expand
 * 		- valid names
 * 			(combination of letters, numbers, and underscores; must start with a letter or an underscore)
 * 		- special arguments: $?
 * 		- braces ${}
 *
 *   [x] If no valid name is encountered, just leave $ in the string.
 *
 * [x] $ directly followed by any quote should just leave the quoted string with the $ removed.
 *
 *   ( [ ] OUT OF SCOPE: $[Single quotes] allows escape sequences like \n for newline.
 * 			'\\' -> \\ ; $'\\' -> \ )
 *
 * [x] Take everything that comes after a dollar sign until the first non-valid name or the ending brace }.
 * 		- bash-5.1$ a=123
 * 		  bash-5.1$ echo a$ab-
 * 		  a-
 *
 * [ ] Braces: Once inside a brace, if no valid name, don't execute current cmd and report:
 * 		e.g. ${1a}: bad substitution
 * 		${} also reports bad substitution
 *
 *
 * QUOTES:
 *
 * [x] Inside of double-quotes expansion still happens, inside of single quotes not.
 *
 * [ ] Empty strings like "" or '' should be kept as empty strings even after quote removal.
 * 			echo "" a != echo a
 * 		[?] However, why is this: '''' != '' ''
 *
 *
 * WILDCARD:
 *
 */

/*
 * IMPLEMENTATION
 *
 * [x] Need a function that replaces the part of a string specified by start and end with another given string.
 *
*/

/*
 * TODO-LIST
 *
 * [x] Handle $<quotes>
 * [x] Assign NULL when executor should do nothing, and empty string for errors.
 * [x] Report %s: bad substitution
 * [x] Handle this case: "$'$USER'" -> $'ldulling'
 *
*/

#include "expander.h"

bool	ft_expander(char **str, t_shell *shell)
{
	char	*dup;

	if (!str || !*str)
		return (true);
	dup = ft_strdup(*str);
	if (!dup)
		return (false);
	if (bad_substitution(dup))
		return (ft_free_and_null((void **)str), free_and_reset(dup), false);
	if (!parameter_expansion(&dup, shell))
		return (free_and_reset(dup), false);
	if (!*dup)
		return (ft_free_and_null((void **)str), free_and_reset(dup), true);
	if (!quote_removal(&dup))
		return (free_and_reset(dup), false);
	free_and_reset(*str);
	*str = dup;
	return (true);
}
