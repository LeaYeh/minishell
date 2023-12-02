/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:17:46 by ldulling          #+#    #+#             */
/*   Updated: 2023/11/28 23:53:43 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <limits.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

# define WHITESPACE " \f\n\r\t\v"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

// Adjusted for push_swap
typedef struct s_list_d
{
	void			*content;
	int				pos_origin;
	int				pos_sorted;
	struct s_list_d	*prev;
	struct s_list_d	*next;
}	t_list_d;

/* Chars */
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
int			ft_isspace(int c);
int			ft_tolower(int c);
int			ft_toupper(int c);

/* Lists singly-linked */
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list		*ft_lstnew(void *content);
int			ft_lstsize(t_list *lst);
void		ft_lstsort_bubble(t_list **lst, void *(*cmp)(void *, void *));

/* Lists doubly-linked */
void		ft_lstadd_back_d(t_list_d **lst, t_list_d *new);
void		ft_lstadd_front_d(t_list_d **lst, t_list_d *new);
void		ft_lstclear_d(t_list_d **lst, void (*del)(void *));
t_list_d	*ft_lstlast_d(t_list_d *lst);
t_list_d	*ft_lstnew_d(void *content);

/* Memory */
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		*ft_memset(void *s, int c, size_t n);

/* Numbers */
double		ft_atof(const char *nptr);
int			ft_atoi(const char *nptr);
long		ft_atol(const char *nptr);

/* Put */
void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *s, int fd);
int			ft_putnbr_base_fd(long n, const char *base, int fd);
void		ft_putnbr_fd(int n, int fd);
size_t		ft_putnchar_fd(unsigned char c, size_t n, int fd);
size_t		ft_putnstr_fd(const char *s, size_t n, int fd);
void		ft_putstr_fd(char *s, int fd);

/* Strings */
char		*ft_itoa(int n);
char		**ft_split(char const *s, char c);
char		*ft_strchr(const char *s, int c);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strdup(const char *s);
int			ft_strisdigits(const char *s);
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlen(const char *s);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int			ft_strmatches_any(const char *str, int n, ...);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnstr(const char *big, const char *little, size_t len);
char		*ft_strrchr(const char *s, int c);
char		*ft_strtok(char *str, const char *delim);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_substr(char const *s, unsigned int start, size_t len);

#endif
