/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_output.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:41:49 by lyeh              #+#    #+#             */
/*   Updated: 2024/03/21 17:36:32 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export.h"
#include "utils.h"

static int		get_total_export_printout_len(
					t_list *env_list, int prefix_len, int format_len);
static int		get_env_str_len(
					t_env *env_node, int prefix_len, int format_len);
static void		fill_export_printout(
					t_list *env_list,
					char *export_printout,
					int prefix_len,
					int format_len);
static t_env	*get_next_env_node(t_list *env_list, char *prev_key);

/**
 * Print all exported env vars in ASCII order, with "export " prepended.
 * The value gets put in double-quotes.
 *
 * Get the total length of everything that will have to be printed.
 * Malloc once, then use ft_snprintf to fill.
 * Then print once.
 */
int	print_exported_env(t_list *env_list)
{
	char	*export_printout;
	int		format_len;
	int		prefix_len;
	int		total_len;

	prefix_len = ft_strlen(EXPORT_PREFIX);
	format_len = ft_strlen("=\"\"\n");
	total_len = get_total_export_printout_len(env_list, prefix_len, format_len);
	if (total_len == 0)
		return (SUCCESS);
	export_printout = (char *)malloc(total_len + 1);
	if (!export_printout)
		return (BUILTIN_ERROR);
	fill_export_printout(env_list, export_printout, prefix_len, format_len);
	printf("%s", export_printout);
	free(export_printout);
	return (SUCCESS);
}

static int	get_total_export_printout_len(
				t_list *env_list, int prefix_len, int format_len)
{
	t_env	*env_node;
	int		total_len;

	total_len = 0;
	while (env_list)
	{
		env_node = env_list->content;
		if (env_node->export == EXPORT_YES)
			total_len += get_env_str_len(env_node, prefix_len, format_len);
		env_list = env_list->next;
	}
	return (total_len);
}

static int	get_env_str_len(
				t_env *env_node, int prefix_len, int format_len)
{
	int	len;

	len = prefix_len + ft_strlen(env_node->key);
	if (env_node->value)
		len += ft_strlen(env_node->value) + format_len;
	else
		len += 1;
	return (len);
}

static void	fill_export_printout(
				t_list *env_list,
				char *export_printout,
				int prefix_len,
				int format_len)
{
	t_env	*env_node;
	int		i;
	int		size;

	i = 0;
	env_node = get_next_env_node(env_list, NULL);
	while (env_node)
	{
		if (env_node->export == EXPORT_YES)
		{
			size = prefix_len + ft_strlen(env_node->key);
			i += ft_snprintf(&export_printout[i], size + 1, "%s%s",
					EXPORT_PREFIX, env_node->key);
			if (env_node->value)
			{
				size = ft_strlen(env_node->value) + format_len;
				i += ft_snprintf(&export_printout[i], size + 1, "=\"%s\"\n",
						env_node->value);
			}
			else
				i += ft_snprintf(&export_printout[i], 2, "\n");
		}
		env_node = get_next_env_node(env_list, env_node->key);
	}
}

static t_env	*get_next_env_node(t_list *env_list, char *prev_key)
{
	t_env	*env_node;
	t_env	*next_node;

	next_node = NULL;
	while (env_list)
	{
		env_node = env_list->content;
		if (env_node->export == EXPORT_YES && \
			(!prev_key || ft_strcmp(env_node->key, prev_key) > 0) && \
			(!next_node || ft_strcmp(env_node->key, next_node->key) < 0))
			next_node = env_node;
		env_list = env_list->next;
	}
	return (next_node);
}
