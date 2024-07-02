/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:17:46 by ldulling          #+#    #+#             */
/*   Updated: 2024/06/28 19:31:02 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <limits.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>

# define WHITESPACE	" \f\n\r\t\v"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_list_d
{
	void			*content;
	struct s_list_d	*prev;
	struct s_list_d	*next;
}	t_list_d;

\
/* Chars */

int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_issign(int c);
int			ft_isprint(int c);
int			ft_isspace(int c);
int			ft_tolower(int c);
int			ft_toupper(int c);

\
/* Lists doubly-linked */

void		ft_lstadd_back_d(t_list_d **lst, t_list_d *new);
void		ft_lstadd_front_d(t_list_d **lst, t_list_d *new);
void		ft_lstclear_d(t_list_d **lst, void (*del)(void *));
void		ft_lstdelone_d(t_list_d *lst, void (*del)(void *));
void		ft_lstdrop_node_d(t_list_d **lst, t_list_d **node, \
								void (*del)(void *));
void		ft_lstiter_d(t_list_d *lst, void (*f)(void *));
t_list_d	*ft_lstlast_d(t_list_d *lst);
bool		ft_lstnew_back_d(t_list_d **lst, void *content);
t_list_d	*ft_lstnew_d(void *content);
int			ft_lstsize_d(t_list_d *lst);

\
/* Lists singly-linked */

void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstadd_back_eff(t_list **lst, t_list **tail, t_list *new);
void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstdrop_node(t_list **lst, t_list **node, void (*del)(void *));
t_list		*ft_lstdup(t_list *lst, void *(*dup)(void *), void (*del)(void *));
void		ft_lstinsert_after(t_list **lst, t_list *new);
void		ft_lstinsert_before(t_list **lst, t_list *cur, t_list *new);
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list		*ft_lstnew(void *content);
bool		ft_lstnew_back(t_list **lst, void *content);
bool		ft_lstnew_back_eff(t_list **lst, t_list **tail, void *content);
bool		ft_lstnew_front(t_list **lst, void *content);
t_list		*ft_lstpop_front(t_list **lst);
void		*ft_lstpop_front_content(t_list **lst);
int			ft_lstsize(t_list *lst);
int			ft_lstsize_non_null(t_list *lst);
void		ft_lstsort_bubble(t_list **lst, void *(*cmp)(void *, void *));
void		ft_lstsort_merge(t_list **lst, void *(*cmp)(void *, void *));
void		ft_lstswap_head(t_list **lst);

\
/* Memory */

void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
void		ft_free_and_null(void **ptr);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		*ft_memset(void *s, int c, size_t n);

\
/* Numbers */

double		ft_atof(const char *nptr);
int			ft_atoi(const char *nptr);
long		ft_atol(const char *nptr);
bool		ft_isoverflow_int(const char *nptr);
bool		ft_isoverflow_long(const char *nptr);

\
/* Put */
void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *s, int fd);
size_t		ft_putnbr_base_fd(long n, const char *base, int fd);
void		ft_putnbr_fd(int n, int fd);
size_t		ft_putnchar_fd(unsigned char c, size_t n, int fd);
size_t		ft_putnstr_fd(const char *s, size_t n, int fd);
void		ft_putstr_fd(char *s, int fd);
size_t		ft_snputnbr_base(char *str, long n, const char *base, \
								size_t max_len);
size_t		ft_sputnchar(char *str, unsigned char c, size_t n);
size_t		ft_sputnstr(char *str, const char *s, size_t n);

\
/* Strings */

bool		ft_alphabetic(const char *str1, const char *str2);
char		*ft_itoa(int n);
char		**ft_split(char const *s, char c);
char		**ft_split_at_index(char *str, size_t index);
char		*ft_strchr(const char *s, int c);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strdel_sequence(const char *str, const char *sequence);
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
char		*ft_strndup(const char *s, size_t n);
char		*ft_strnstr(const char *big, const char *little, size_t len);
char		*ft_strrchr(const char *s, int c);
char		*ft_strrnstr(const char *big, const char *little, size_t len);
bool		ft_strrplc_part(char **str, const char *rplcmt, size_t start, \
							size_t len);
char		*ft_strrplc_sequence(const char *str, const char *sequence, \
									const char *rplcmt);
char		*ft_strtok(char *str, const char *delim);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_substr(char const *s, unsigned int start, size_t len);

#endif
