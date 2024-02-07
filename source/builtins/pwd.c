#include "defines.h"
#include "utils.h"

int	ft_exec_pwd(char **envp)
{
	char	*env_pwd;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_dprintf(2, "%s: %s: ", PROGRAM_NAME, "pwd");
		perror(NULL);
		return (CMD_EXEC_FAILED);
	}
	env_pwd = get_value_from_env(envp, "PWD");
	if (ft_strncmp(env_pwd, "//", 2) == 0)
		printf("/%s\n", pwd);
	else
		printf("%s\n", pwd);
	free(pwd);
	return (EXIT_SUCCESS);
}
