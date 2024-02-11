#include "utils.h"
#include "clean.h"

static t_list	*convert_assignment_to_env_list(t_list *assignment_list);
static void		remove_duplicate_keys(
					t_list **env_list, t_list *assignment_list);
static int		get_env_size(t_list *env_list);
static int		get_env_strlen(t_env *env_node);

bool	update_env_list(t_list **env_list, t_list *assignment_list)
{
	t_list	*assignment_env_list;

	assignment_env_list = convert_assignment_to_env_list(assignment_list);
	if (!assignment_env_list)
		return (false);
	remove_duplicate_keys(env_list, assignment_env_list);
	ft_lstadd_front(env_list, assignment_env_list);
	return (true);
}

char	**convert_env_list_to_array(t_list *env_list)
{
	char	**env;
	t_env	*env_node;
	int		i;
	char	*tmp;

	env = (char **)malloc(
			(get_env_size(env_list) + 1) * sizeof(char *));
	if (!env)
		return (NULL);
	i = 0;
	while (env_list)
	{
		env_node = (t_env *)env_list->content;
		if (env_node->state && env_node->value)
		{
			tmp = (char *)malloc((get_env_strlen(env_node) + 1) * sizeof(char));
			if (!tmp)
				return (free_array(&env), NULL);
			sprintf(tmp, "%s=%s", env_node->key, env_node->value);	// TODO: This is really dangerous, bc the user could set a very long key or value and go beyond the memory of size PATH_MAX.
			env[i++] = tmp;
		}
		env_list = env_list->next;
	}
	env[i] = NULL;
	return (env);
}

// Last assignment -> first in env
static t_list	*convert_assignment_to_env_list(t_list *assignment_list)
{
	t_list	*env_list;
	t_list	*new_node;

	env_list = NULL;
	while (assignment_list)
	{
		new_node = NULL;
		if (!process_str_to_env_list(assignment_list->content,
				&new_node, V_EXPORT_YES))
			return (ft_lstclear(&assignment_list, (void *)free_env_node),
				NULL);
		ft_lstadd_front(&env_list, new_node);
		assignment_list = assignment_list->next;
	}
	return (env_list);
}

// Remove duplicates from env_list
static void	remove_duplicate_keys(t_list **env_list, t_list *assignment_list)
{
	t_list	*cur;
	t_env	*env_node;

	cur = *env_list;
	while (cur)
	{
		env_node = (t_env *)cur->content;
		if (is_key_in_env_list(assignment_list, env_node->key))
			ft_lstdrop_node(env_list, &cur, (void *)free_env_node);
		else
			cur = cur->next;
	}
}

static int	get_env_size(t_list *env_list)
{
	t_env	*env_node;
	int		size;

	size = 0;
	while (env_list)
	{
		env_node = (t_env *)env_list->content;
		if (env_node->state && env_node->value)
			size++;
		env_list = env_list->next;
	}
	return (size);
}

static int	get_env_strlen(t_env *env_node)
{
	int	len;

	len = ft_strlen(env_node->key) + 1;
	if (env_node->value)
		len += ft_strlen(env_node->value);
	return (len);
}
