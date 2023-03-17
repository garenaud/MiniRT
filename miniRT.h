/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 17:18:06 by grenaud-          #+#    #+#             */
/*   Updated: 2023/03/17 12:05:12 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define RED		"\033[1m\033[31m"
# define GREEN		"\033[1m\033[32m"
# define YEL		"\033[0;33m"
# define PURP		"\033[0;35m"
# define ENDC		"\033[0m"
# define BOLDRED	"\033[31m"
# define BLUE		"\033[1;34m"

# define CANVAS_X	1024
# define CANVAS_Y	1024
# define VIEWPORT_HEIGHT	256
# define VIEWPORT_WIDTH		256
# define MCC		255


# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <math.h>
# include <stdlib.h>

# include "libft/libft.h"
# include "mlx/mlx.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

/* ************************************************************************** */
/* STRUCTS																	  */
/* ************************************************************************** */
typedef struct s_list
{
	char			*data;
	struct s_list	*next;
}	t_list;

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
	double	tr;
}			t_color;

typedef struct	s_rgb
{
	int		rgb[3];
}			t_rgb;

typedef struct	s_vector
{
	double	vec[3];
}			t_vector;

typedef struct s_vecteur
{
	double	arr[3];
	double	norm;
}			t_vecteur;

typedef struct s_readfd
{
	char	**fdcontent;
}			t_readfd;

/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */
//ft_atod.c
int			sign_atod(char c);
double		int_part(char c, double result);
double		frac_part(char *str);
int			frac_len(char *str);
double		ascii_to_double(char *str);

/* ************************************************************************** */
//get_next_line.c
char		*get_next_line(int fd);
int			gnl_read(char **buff_s, char **line, int fd, int bli);
void		ft_strdel(char **str);
char		*ft_strdupcat(char **s1, char *s2);
int			ft_strichr(const char *s, int c);
size_t		ft_strlen(char const *s);

/* ************************************************************************** */
//list_utils1.c
void		push(t_list **top, char *item);
char		*pop(t_list **top);
void		delete(t_list **top);
t_list		*reverse(t_list **top);
int			getpos_c(t_list *top, char *item);
//list_utils2.c
size_t		size_stack(t_list *top);
int			transfer_c(t_list **start, t_list **end);
int			remove_pos_c(t_list **top, size_t pos);
char		*getitem(t_list *top, size_t pos);
//list_utils3.c
void		printll(t_list *lst);
void		print_ic(t_list_i *lst_i, t_list *lst);
//Array_2d.c
t_rgb		**create_2d_rgb(int cols, int rows);
t_vector	**create_2d_vector(int cols, int rows);
void		free_2d_rgb(t_rgb **rgb, int cols);
void		free_2d_vector(t_vector **vec, int cols);


/* ************************************************************************** */
#endif
