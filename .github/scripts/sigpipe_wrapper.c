#include <signal.h>
#include <unistd.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	pid_t	child;

	if (argc == 1)
	{
		fprintf(stderr, "Must specify a command to run\n");
		return (1);
	}
	signal(SIGPIPE, SIG_DFL);
	execvp(argv[1], argv + 1);
	perror("execvp");
	return (2);
}
