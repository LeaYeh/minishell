#include "utils.h"

int	exec_unset(char *args[], t_list **env_list)
{
	int	i;

	i = 1;
	while (args[i])
	{
		remove_env_node(env_list, args[i], NULL);
		i++;
	}
	return (SUCCESS);
}
