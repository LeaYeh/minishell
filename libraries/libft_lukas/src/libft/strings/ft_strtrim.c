/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:16:51 by ldulling          #+#    #+#             */
/*   Updated: 2023/09/26 12:47:52 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	skip_set(size_t *pos, size_t lim, char const *s1, char const *set);

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str_trimmed;
	size_t	start;
	size_t	end;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = 0;
	end = ft_strlen(s1) - 1;
	skip_set(&start, end, s1, set);
	skip_set(&end, start, s1, set);
	str_trimmed = ft_substr(s1, start, end - start + 1);
	return (str_trimmed);
}

static void	skip_set(size_t *pos, size_t lim, char const *s1, char const *set)
{
	int		direction;
	int		is_found;
	size_t	i;

	if (*pos < lim)
		direction = 1;
	else
		direction = -1;
	lim += direction;
	is_found = 1;
	while (*pos != lim && is_found)
	{
		is_found = 0;
		i = 0;
		while (set[i] && !is_found)
		{
			if (s1[*pos] == set[i])
			{
				*pos += direction;
				is_found = 1;
			}
			i++;
		}
	}
	return ;
}
