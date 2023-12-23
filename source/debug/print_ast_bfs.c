/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bfs_ast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 18:58:58 by lyeh              #+#    #+#             */
/*   Updated: 2023/12/23 19:11:00 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"

t_relation_ast	*init_relation_ast_node(
		int level, t_ast *parent, t_ast *current, t_list *children)
{
	t_relation_ast	*node;

	node = (t_relation_ast *)malloc(sizeof(t_relation_ast));
	if (!node)
		return (NULL);
	node->level = level;
	node->parent = parent;
	node->current = current;
	node->children = children;
	return (node);
}

void	print_ast_bfs(t_ast *root)
{
	t_list			*queue;
	t_relation_ast	*node;
	t_relation_ast	*tmp;
	int				cur_level;

	if (!root)
		return ;
	queue = NULL;
	node = init_relation_ast_node(0, NULL, root, root->children);
	if (!node)
		return ;
	ft_lstadd_back(&queue, ft_lstnew(node));
	cur_level = 0;
	while (queue)
	{
		node = (t_relation_ast *)ft_lstpop_content(&queue);
		if (node->level != cur_level)
		{
			printf("\n\n%d: ", node->level);
			cur_level = node->level;
		}
		if (cur_level == 0)
			printf("\n%d: %d ", node->level, node->current->type);
		else
			printf("%d(%d) ", node->current->type, node->parent->type);
		while (node->children)
		{
			tmp = init_relation_ast_node(
					node->level + 1,
					node->current,
					(t_ast *)node->children->content,
					((t_ast *)(node->children->content))->children);
			if (!tmp)
				return ;
			ft_lstadd_back(&queue, ft_lstnew(tmp));
			node->children = node->children->next;
		}
		free(node);
	}
	printf("\n\n");
}
