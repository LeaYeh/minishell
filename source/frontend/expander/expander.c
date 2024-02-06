/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 09:43:44 by ldulling          #+#    #+#             */
/*   Updated: 2024/01/20 02:29:25 by ldulling         ###   ########.fr       */
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
 * [ ] Word Splitting
 *
*/

#include "expander.h"

// Enums should be used in such a case bc it allows the compiler to enforce that only values from this enumeration are used.
// TODO: Go through all enums and if an argument of a function can only be an enum, modify like here.
int	ft_expander(char *str, t_list **lst, t_shell *shell, t_expander_op op_mask)
{
	char	*dup;

	if (!str)
		return (SUCCESS);
	dup = ft_strdup(str);
	if (!dup)
		return (MALLOC_ERROR);
	if (op_mask & (E_EXPAND | E_HEREDOC))
	{
		if (is_bad_substitution(str, op_mask))
			return (free(dup), BAD_SUBSTITUTION);
		if (!handle_parameter_expansion(&dup, lst, shell, op_mask))
			return (free(dup), MALLOC_ERROR);
		// TODO: Potentially split into multiple nodes by whitespace here.
		// The keyword in the bash manual is "Word Splitting".
		// Don't do it for heredoc.
	}
	else
	{
		*lst = ft_lstnew(dup);
		if (!*lst)
			return (free(dup), MALLOC_ERROR);
	}
	if (op_mask & E_RM_QUOTES)
		if (!handle_remove_quotes(lst))
			return (MALLOC_ERROR);
	return (SUCCESS);
}
