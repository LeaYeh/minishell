#include "export.h"
#include "utils.h"

/* string_utils.c */
// is_valid_varname()
// is_valid_varname_start()

/* setup_env_list.c */
// bool	process_env_str_to_env_list(char *env_str, t_list **env_list)

// void	handle_invalid_identifier(char *arg, int *ret)
// {

// }

int	exec_export(char *args[], t_list **env_list)
{
	if (get_array_len(args) < 2)
		return (print_exported_env(*env_list));
	return (SUCCESS);
}
