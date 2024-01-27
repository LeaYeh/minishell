/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_dotslash.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 22:27:13 by ldulling          #+#    #+#             */
/*   Updated: 2024/01/17 09:56:59 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "cd.h"

// bool	remove_starting_dot(char **str)
// {
// 	char	*tmp;

// 	if ((*str)[0] == '.' && (*str)[1] == '/')
// 	{
// 		tmp = ft_substr(*str, 2, ft_strlen(&(*str)[2]));
// 		if (!tmp)
// 			return (false);
// 		if (!reduce_multi_slash(&tmp, 0))
// 			return (free(tmp), false);
// 		free(*str);
// 		*str = tmp;
// 	}
// 	return (true);
// }

// bool	remove_middle_dotslashes(char **str)
// {
// 	char	*occurance;
// 	size_t	rmv_len;

// 	occurance = ft_strnstr(*str, "/./", ft_strlen(*str));
// 	if (!occurance)
// 		return (true);
// 	rmv_len = ft_strlen("/./");
// 	while (occurance)
// 	{
// 		if (!replace_part_of_str(str, "/", occurance - *str, rmv_len))
// 			return (false);
// 		if (!reduce_multi_slash(str, occurance - *str))
// 			return (false);
// 		occurance = ft_strnstr(occurance, "/./", ft_strlen(occurance));
// 	}
// 	return (true);
// }

// bool	remove_ending_dot(char **str)
// {
// 	size_t	end;
// 	char	*tmp;

// 	if (!**str)
// 		return (true);
// 	end = ft_strlen(*str) - 1;
// 	if ((*str)[end] == '.' && (end == 0 || (*str)[end - 1] == '/'))
// 	{
// 		tmp = ft_substr(*str, 0, end);
// 		if (!tmp)
// 			return (false);
// 		free(*str);
// 		*str = tmp;
// 	}
// 	return (true);
// }

// bool	remove_dotslash(char **curpath)
// {
// 	char	*dup;

// 	dup = ft_strdup(*curpath);
// 	if (!dup)
// 		return (false);
// 	if (!remove_starting_dotslash(&dup))
// 		return (free(dup), false);
// 	if (!remove_middle_dotslashes(&dup))
// 		return (free(dup), false);
// 	if (!remove_ending_dot(&dup))
// 		return (free(dup), false);
// 	free(*curpath);
// 	*curpath = dup;
// 	return (true);
// }
