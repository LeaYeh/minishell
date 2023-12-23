/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:00:04 by lyeh              #+#    #+#             */
/*   Updated: 2023/12/23 23:59:46 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

void	ft_print_env(void *env)
{
	printf("%s=%s\n", ((t_env *) env)->key, ((t_env *) env)->value);
}

void	ft_print_token(void *token)
{
	printf("(type: %s, data: %s)\n",
		ft_get_token_type_str(((t_token *) token)->type), \
			((t_token *) token)->data);
}

void	ft_show_token_list(t_shell *shell)
{
	printf("-------- TOKEN LIST --------\n");
	ft_lstiter(shell->token_list, ft_print_token);
	printf("----------------------------\n\n");
}

void	ft_show_env_list(t_shell *shell)
{
	printf("--------- ENV LIST ---------\n");
	ft_lstiter(shell->env_list, ft_print_env);
	printf("----------------------------\n\n");
}
