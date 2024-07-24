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

#include "clean.h"
#include "utils.h"

static bool	limit_retries(t_sh *shell, bool success);

bool	read_input(
			char **line,
			t_sh *shell,
			char *prompt,
			bool add_to_history)
{
	char	*tmp;

	errno = SUCCESS;
	if (shell->is_interactive)
		*line = readline(prompt);
	else
	{
		tmp = get_next_line(STDIN_FILENO);
		if (errno != SUCCESS)
			return (free(tmp), limit_retries(shell, false));
		if (tmp)
		{
			*line = ft_strtrim(tmp, "\n");
			free(tmp);
		}
	}
	if (errno == EINTR || errno == ENOTTY)
		errno = SUCCESS;
	else if (errno != SUCCESS)
		return (limit_retries(shell, false));
	if (add_to_history && shell->is_interactive && *line && **line)
		add_history(*line);
	return (limit_retries(shell, errno == SUCCESS));
}

static bool	limit_retries(t_sh *shell, bool success)
{
	static int	retries;

	if (success == true)
	{
		retries = 0;
		return (true);
	}
	else if (++retries > 5)
		clean_and_exit_shell(shell, GENERAL_ERROR, "read input failed");
	print_error("%s: read input failed, trying again...\n", PROGRAM_NAME);
	return (false);
}
