#include "defines.h"

int	ft_exec_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_dprintf(2, "%s: %s: ", PROGRAM_NAME, "pwd");
		perror(NULL);
		return (CMD_EXEC_FAILED);
	}
	printf("%s\n", pwd);
	free(pwd);
	return (EXIT_SUCCESS);
}
