/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 11:34:00 by grenaud-          #+#    #+#             */
/*   Updated: 2023/04/05 16:02:09 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# define FT_INT_MIN -2147483648
# define FT_INT_MAX 2147483647

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <limits.h>
# include <stddef.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct s_listl
{
	void			*content;
	struct s_listl	*next;
}					t_listl;

int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_isspace(int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strdup(const char *s);
char	*ft_strdup_num(char *s1, int start, int end);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*strjoin_gnl(char *left_str, char *buff);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin2(char *left_str, char *buff);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, unsigned int n);
size_t	ft_strlen(char const *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*strchr_gnl(char *s, int c);
char	*ft_strchr(const char *str, int c);
char	*ft_strchr2(char *s, int c);
void	*ft_memset(void *b, int c, size_t len);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
int		ft_memcmp(const void *ptr1, const void *ptr2, size_t size);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_isupper(int c);
int		ft_isprint(int c);
int		ft_isdigit(int c);
int		ft_isdigit2(char c);
int		ft_isascii(int c);
char	ft_isascii_num(char c);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
void	ft_bzero(void *s, size_t n);
int		ft_atoi(const char *str);
t_listl	*ft_lstnew(void *content);
t_listl	*ft_lstlast(t_listl *lst);
t_listl	*ft_lstmap(t_listl *lst, void *(*f)(void *), void (*del)(void *));
int		ft_lstsize(t_listl *lst);
void	ft_lstadd_front(t_listl **alst, t_listl *new);
void	ft_lstadd_back(t_listl **alst, t_listl *new);
void	ft_lstdelone(t_listl *lst, void (*del)(void *));
void	ft_lstclear(t_listl **lst, void (*del)(void *));
void	ft_lstiter(t_listl *lst, void (*f)(void *));
size_t	ft_strlen(const char *s);
void	*wrmalloc(unsigned long size);
int		wrfree(void *ptr);
void	wrdestroy(void);
void	ft_putstr(char *s);
#endif