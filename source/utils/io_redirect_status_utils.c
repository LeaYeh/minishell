#include "defines.h"
#include "utils.h"

int	get_redirect_type_from_list(t_list *io_red_list)
{
	t_io_red	*io_red;

	if (!io_red_list)
		return (T_NONE);
	io_red = io_red_list->content;
	return (io_red->type);
}
