/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 19:16:10 by lyeh              #+#    #+#             */
/*   Updated: 2023/12/24 00:13:45 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "utils.h"

t_ast	*init_ast_node(int type, char *data, t_list *children)
{
	t_ast	*node;

	node = (t_ast *)malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	node->data = data;
	node->children = children;
	return (node);
}

void	free_ast_data(void *ast)
{
	if (!(t_ast *) ast)
		return ;
	if (((t_ast *) ast)->data)
		ft_free_and_null((void **) &((t_ast *) ast)->data);
}

// Free all the children recursively and then free the node
void	free_ast_node(void *ast)
{
	t_list	*child;

	if (!ast)
		return ;
	child = ((t_ast *) ast)->children;
	while (child)
	{
		free_ast_data(child->content);
		free_ast_node(child->content);
		free(ft_lstpop_front(&child));
	}
	free_ast_data(ast);
	free(ast);
}
