#include "expander.h"

#include "debug.h"

void	print_list(t_list *list)
{
	while (list)
	{
		printf("%s\n", (char *)list->content);
		list = list->next;
	}
}

bool	set_file_list(t_list **file_list, char *str)
{
	DIR				*dir;
	struct dirent	*file;
	char			*filename;

	(void)str;

	dir = opendir(".");
	if (dir == NULL)
		return (true);
	file = readdir(dir);
	while (file != NULL)
	{
		filename = ft_strdup(file->d_name);
		if (!filename)
			break ;
		if (!ft_lstnew_front(file_list, filename))
			break ;
		file = readdir(dir);
	}
	if (errno != SUCCESS)
	{
		perror(NULL);
		return (closedir(dir), false);
	}
	return (closedir(dir), true);
}

bool	ascending(const char *str1, const char *str2)
{
	return (ft_strcmp(str1, str2) <= 0);
}

bool	expand_wildcard(char *str)
{
	t_list	*file_list;

	file_list = NULL;
	set_file_list(&file_list, str);

	printf("\n------before sort------\n");
	print_list(file_list);
	ft_lstsort_merge(&file_list, (void *)ascending);
	printf("\n------after sort------\n");
	print_list(file_list);

	ft_lstclear(&file_list, free);
	return (true);
}
