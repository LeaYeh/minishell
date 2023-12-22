/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 19:16:10 by lyeh              #+#    #+#             */
/*   Updated: 2023/12/21 23:06:27 by lyeh             ###   ########.fr       */
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

void	free_ast_data(t_ast *ast)
{
	if (!ast)
		return ;
	if (ast->data)
		ft_free_and_null((void **)&ast->data);
}

// Free all the children recursively and then free the node
void	free_ast_node(t_ast **ast)
{
	static int	depth = -1;
	t_list	*child;

	if (!ast || !*ast)
		return ;
	printf("here %d\n", depth++);
	child = (*ast)->children;
	printf("here %d\n", depth);
	while (child)
	{
		depth++;
		free_ast_node(((t_ast **)&(child->content)));
		child = child->next;
	}
	free_ast_data(*ast);
	ft_free_and_null((void **)ast);
}

void	print_ast(t_ast *node, int depth)
{
	t_list	*child;
	int		i;

	if (node == NULL)
		return ;
	i = 0;
	while (i < depth)
	{
		printf("  ");
		i++;
	}
	printf("%d\n", node->type);
	child = node->children;
	while (child)
	{
		print_ast((t_ast *)child->content, depth + 1);
		child = child->next;
	}
}
