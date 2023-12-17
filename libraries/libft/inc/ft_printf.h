/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 19:26:08 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/17 13:45:49 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"

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
	int		fd;
}	t_format;

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

#endif
