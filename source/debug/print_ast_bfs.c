/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast_bfs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 18:58:58 by lyeh              #+#    #+#             */
/*   Updated: 2024/03/27 00:15:38 by ldulling         ###   ########.fr       */
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

bool	append_relation_ast_node(
	t_list **queue, int level, t_ast *parent, t_ast *current)
{
	t_list			*lst;
	t_relation_ast	*tmp;

	tmp = init_relation_ast_node(level, parent, current, current->children);
	if (!tmp)
		return (false);
	lst = ft_lstnew(tmp);
	if (!lst)
		return (free(tmp), false);
	ft_lstadd_back(queue, lst);
	return (true);
}

bool	append_children_to_queue(t_list **queue, t_relation_ast *node)
{
	while (node->children)
	{
		if (!append_relation_ast_node(
				queue, node->level + 1, node->current, node->children->content))
			return (false);
		node->children = node->children->next;
	}
	return (true);
}

int	print_relation_ast_node(t_relation_ast *node, int cur_level)
{
	if (node->level != cur_level)
	{
		printf("\n\n%d: ", node->level);
		cur_level = node->level;
	}
	if (cur_level == 0)
		printf("\n%d: %d ", node->level, node->current->type);
	else
		printf("%d(%d) ", node->current->type, node->parent->type);
	return (cur_level);
}

bool	print_ast_bfs(t_ast *root)
{
	t_list			*queue;
	t_relation_ast	*node;
	int				cur_level;

	if (!root)
		return (true);
	queue = NULL;
	cur_level = 0;
	if (!append_relation_ast_node(&queue, cur_level, NULL, root))
		return (false);
	while (queue)
	{
		node = (t_relation_ast *)ft_lstpop_front_content(&queue);
		cur_level = print_relation_ast_node(node, cur_level);
		if (!append_children_to_queue(&queue, node))
			return (ft_lstclear(&queue, free), false);
		free(node);
	}
	printf("\n\n");
	return (ft_lstclear(&queue, free), true);
}
