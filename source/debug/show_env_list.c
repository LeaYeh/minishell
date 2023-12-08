/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_env_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:00:04 by lyeh              #+#    #+#             */
/*   Updated: 2023/12/08 20:59:57 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_show_env_list(t_shell *shell)
{
	t_list	*curr;
	t_env	*env;

	curr = shell->env_list;
	while (curr)
	{
		env = (t_env *)curr->content;
		ft_printf("%s=%s\n", env->key, env->value);
		curr = curr->next;
	}
}
