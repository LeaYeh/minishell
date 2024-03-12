#include "expander.h"

static int	trim_whitespace(char **new_str, size_t *i, size_t *end)
{
	int	trimmed_len;

	while (ft_strchr(" \t\n", (*new_str)[*i]) && *i < *end)
		(*i)++;
	if (!ft_strrplc_part(new_str, "", 0, *i))
		return (-1);
	trimmed_len = *i;
	*end -= trimmed_len;
	*i = 0;
	return (trimmed_len);
}

static char	*split(char **new_str, size_t *i, size_t *end)
{
	char	**halves;
	char	*word;

	halves = ft_split_at_index(*new_str, *i);
	if (!halves)
		return (NULL);
	word = halves[0];
	free(*new_str);
	*new_str = halves[1];
	free(halves);
	*end -= *i;
	*i = 0;
	return (word);
}

static char	*extract_word(
	char **new_str, t_list *task_list, size_t *i, size_t *end)
{
	int		trimmed_len;
	char	*word;

	word = split(new_str, i, end);
	if (!word)
		return (NULL);
	trimmed_len = trim_whitespace(new_str, i, end);
	if (trimmed_len == -1)
		return (NULL);
	update_expander_tasks(task_list, 0 - ft_strlen(word) - trimmed_len);
	return (word);
}

static bool	handle_word_splitting(
	char **new_str, t_list *task_list, t_list **lst)
{
	size_t			end;
	size_t			i;
	t_expander_task	*task;
	char			*word;

	task = task_list->content;
	end = task->start + task->result_len;
	i = task->start;
	while (i < end)
	{
		if (ft_strchr(" \t\n", (*new_str)[i]))
		{
			word = extract_word(new_str, task_list, &i, &end);
			if (!word || !ft_lstnew_back(lst, word))
				return (free(word), false);
		}
		else
			i++;
	}
	return (true);
}

bool	split_words(t_list **lst, char **new_str, t_list *task_list)
{
	t_expander_task	*task;

	while (task_list)
	{
		task = task_list->content;
		if (task->type == ET_VAR)
		{
			if (!handle_word_splitting(new_str, task_list, lst))
				return (false);
		}
		task_list = task_list->next;
	}
	return (ft_lstnew_back(lst, *new_str));
}
