#include "init.h"
#include "utils.h"

bool	setup_env_list(t_shell *shell)
{
	extern char	**environ;
	int			i;
	t_list		*tmp_list;

	if (!setup_default_env_list(shell))
		return (false);
	if (!environ)
		return (true);
	i = 0;
	while (environ[i])
	{
		tmp_list = NULL;
		if (!append_str_to_env_list(&tmp_list, environ[i], ENV_EXPORT))
			return (false);
		if (!check_special_env_vars(&tmp_list))
			return (ft_lstclear(&tmp_list, free), false);
		ft_lstadd_back(&shell->env_list, tmp_list);
		i++;
	}
	return (true);
}

/*
 * PWD should always be set by current shell.
 * If OLDPWD exists and its value is not a real directory,
 * delete OLDPWD entirely (permissions don't matter).
 */
bool	check_special_env_vars(t_list **tmp_list)
{
	t_env	*env_node;

	env_node = (*tmp_list)->content;
	if (ft_strcmp(env_node->key, "PWD") == 0)
	{
		free(env_node->value);
		env_node->value = getcwd(NULL, 0);
		if (!env_node->value)
			return (false);
	}
	else if (ft_strcmp(env_node->key, "OLDPWD") == 0 && \
			env_node->value && !is_dir(env_node->value))
		ft_lstclear(tmp_list, free);
	return (true);
}
