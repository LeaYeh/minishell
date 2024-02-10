#include "defines.h"
#include "utils.h"
#include "clean.h"

// TODO: Add the assignments to the local shell variables list
// TODO: Also add flags if a variable is exported or not
bool	handle_assignment(t_shell *shell)
{
	char		**assignment_array;

	assignment_array = shell->final_cmd_table->assignment_array;
	if (!assignment_array)
		return (true);
	printf("handle_assignment\n");
}
