/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:12:17 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/04 11:33:09 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_strings(char const *s, char c);
static void		skip_c(char const *s, size_t *pos, char c);
static size_t	strclen(char const *s, size_t *pos, char c);
static char		*protected_malloc(char **str_array, size_t i, size_t len);

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	len;
	size_t	pos;
	size_t	str_count;
	char	**str_array;

	str_count = count_strings(s, c);
	str_array = (char **) malloc((str_count + 1) * sizeof(char *));
	if (str_array == NULL)
		return (NULL);
	i = 0;
	pos = 0;
	while (i < str_count)
	{
		skip_c(s, &pos, c);
		len = strclen(s, &pos, c);
		str_array[i] = protected_malloc(str_array, i, len + 1);
		if (str_array[i] == NULL)
			return (free(str_array), NULL);
		str_array[i] = ft_memcpy(str_array[i], &s[pos - len], len);
		str_array[i][len] = '\0';
		i++;
	}
	str_array[i] = NULL;
	return (str_array);
}

static size_t	count_strings(char const *s, char c)
{
	size_t	pos;
	size_t	str_count;

	if (s == NULL)
		return (0);
	str_count = 0;
	pos = 0;
	while (s[pos])
	{
		skip_c(s, &pos, c);
		if (s[pos])
		{
			str_count++;
			while (s[pos] != c && s[pos])
				pos++;
		}
	}
	return (str_count);
}

static void	skip_c(char const *s, size_t *pos, char c)
{
	while (s[*pos] == c)
		(*pos)++;
}

static size_t	strclen(char const *s, size_t *pos, char c)
{
	size_t	len;

	len = 0;
	while (s[*pos] != c && s[*pos])
	{
		len++;
		(*pos)++;
	}
	return (len);
}

static char	*protected_malloc(char **str_array, size_t i, size_t len)
{
	str_array[i] = (char *) malloc((len) * sizeof(char));
	if (str_array[i] == NULL)
	{
		while (i > 0)
		{
			i--;
			free(str_array[i]);
		}
		return (NULL);
	}
	return (str_array[i]);
}
