/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 01:15:50 by ldulling          #+#    #+#             */
/*   Updated: 2024/04/03 13:40:27 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"

bool	read_input(
			char **line,
			char *prompt,
			bool add_to_history,
			bool is_interactive)
{
	char	*tmp;

	errno = SUCCESS;
	if (is_interactive)
		*line = readline(prompt);
	else
	{
		tmp = get_next_line(STDIN_FILENO);
		if (errno != SUCCESS)
			return (free(tmp), false);
		if (tmp)
		{
			*line = ft_strtrim(tmp, "\n");
			free(tmp);
		}
	}
	if (errno == EINTR || errno == ENOTTY)
		errno = SUCCESS;
	else if (errno != SUCCESS)
		return (false);
	if (add_to_history && is_interactive && *line && **line)
		add_history(*line);
	return (errno == SUCCESS);
}
