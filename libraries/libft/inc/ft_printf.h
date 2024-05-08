/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 19:26:08 by ldulling          #+#    #+#             */
/*   Updated: 2024/05/05 17:21:20 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"

# define SPECIFIERS				"cspdiuxX%"
# define FLAGS					"#+- 0"
# define NULL_PRINTOUT_PTR		"(nil)"
# define NULL_PRINTOUT_STR		"(null)"
# define FROM_NEGATIVE_WIDTH	2
# define NO_PRECISION_SET		-1
# define NEGATIVE_PRECISION		-2

typedef struct s_format
{
	int		hash;
	int		plus;
	int		space;
	int		minus;
	int		zero;
	int		width;
	int		precision;
	char	specifier;
	int		unresolved;
	int		fd;
}	t_format;

typedef struct s_sformat
{
	int		hash;
	int		plus;
	int		space;
	int		minus;
	int		zero;
	int		width;
	int		precision;
	char	specifier;
	int		unresolved;
	char	*str;
	size_t	size;
	int		sprinted;
}	t_sformat;

\
/* ft_printf + ft_dprintf */

int		ft_printf(const char *format, ...);
int		ft_dprintf(int fd, const char *format, ...);
int		parseandprint(const char *format, int *i, t_format *f, va_list *ap);
int		print_argument(t_format *f, va_list *ap);
int		print_char(unsigned char c, t_format *f);
int		print_nbr(long nbr, t_format *f);
int		print_parsed(const char *format, int parsed, t_format *f);
int		print_ptr(size_t ptr, t_format *f);
int		print_str(const char *str, t_format *f);
void	reset_format(t_format *f);
int		set_format(const char *format, int *i, t_format *f, va_list *ap);

\
/* ft_snprintf + ft_vsnprintf */

int		ft_snprintf(char *str, size_t size, const char *format, ...);
int		ft_vsnprintf(char *str, size_t size, const char *format, va_list ap);
bool	check_args(char *str, size_t size, const char *format, t_sformat *f);
void	parseandsprint(const char *format, int *i, t_sformat *f, va_list *ap);
void	sprint_argument(t_sformat *f, va_list *ap);
void	sprint_char(unsigned char c, t_sformat *f);
void	sprint_nbr(long nbr, t_sformat *f);
void	sprint_parsed(const char *format, int parsed, t_sformat *f);
void	sprint_ptr(size_t ptr, t_sformat *f);
void	sprint_str(const char *str, t_sformat *f);
size_t	max_size(t_sformat *f, size_t size);
void	reset_sformat(t_sformat *f);
int		set_sformat(const char *format, int *i, t_sformat *f, va_list *ap);

#endif
