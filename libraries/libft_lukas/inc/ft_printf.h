/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 19:26:08 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/02 20:16:30 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <unistd.h>

# ifndef FD
#  define FD 1
# endif
# define SPECIFIERS "cspdiuxX%"
# define FLAGS "#+- 0"
# define NULL_PRINTOUT_PTR "(nil)"
# define NULL_PRINTOUT_STR "(null)"
# define FROM_NEGATIVE_WIDTH 2
# define NO_PRECISION_SET -1
# define NEGATIVE_PRECISION -2

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
}	t_format;

int		ft_printf(const char *format, ...);
int		print_char(unsigned char c, t_format *f);
int		print_nbr(long nbr, t_format *f);
int		print_parsed(const char *format, int parsed, t_format *f);
int		print_ptr(size_t ptr, t_format *f);
int		print_str(const char *str, t_format *f);
int		set_format(const char *format, int *i, t_format *f, va_list *ap);

#endif
