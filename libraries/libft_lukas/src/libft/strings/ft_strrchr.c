/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:16:32 by ldulling          #+#    #+#             */
/*   Updated: 2023/09/24 16:16:39 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	char		casted_c;
	const char	*last;

	casted_c = (char) c;
	if (casted_c == '\0')
	{
		while (*s)
			s++;
		return ((char *) s);
	}
	else
	{
		last = 0;
		while (*s)
		{
			if (*s == casted_c)
				last = s;
			s++;
		}
		return ((char *) last);
	}
}
