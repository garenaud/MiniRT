/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 17:18:06 by grenaud-          #+#    #+#             */
/*   Updated: 2023/03/21 14:21:12 by grenaud-         ###   ########.fr       */
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
# include "parsing/get_next_line.h"

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
}			t_list;

typedef struct s_list_i
{
	int				data;
	struct s_list_i	*next;
}		t_list_i;

typedef struct s_dico
{
	char			*key;
	char			*value;
	struct s_dico	*next;
}		t_dico;

typedef struct s_vector
{
	double	vec[3];
	double	norm;
}			t_vector;

typedef struct s_rgb
{
	int		rgb[3];
}			t_rgb;

typedef struct s_ambiant
{
	double		lum;
	t_rgb		color;
}		t_ambiant;

typedef struct s_camera
{
	t_vector	pos;
	t_vector	dir;
	double		fov;
}		t_camera;

typedef struct s_light
{
	double	xyz[3];
	double	lum;
	t_rgb	rgb;
}		t_light;

typedef struct s_readfd
{
	char	**fdcontent;
	t_list	**readfd;
}			t_readfd;

typedef struct s_scene
{
	t_ambiant	a;
	t_camera	c;
	t_light		l;
}			t_scene;
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
char		*ft_get_start(char *raw_line);
char		*ft_get_line(char *raw_line);
char		*ft_get_raw_line(int fd, char *raw_line);
char		*get_next_line(int fd);
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
//void		print_ic(t_list_i *lst_i, t_list *lst);
//dico.c
void		push_dico(t_dico **top, char *key, char *value);
t_dico		*pop_dico(t_dico **top);
void		delete_dico(t_dico **top);
size_t		size_stack_dico(t_dico *top);
int			get_key(t_dico *top, char *item);
//dico_1.c
int			get_value(t_dico *top, char *item);
int			transfer_dico(t_dico **start, t_dico **end);
int			remove_pos_dico(t_dico **top, size_t pos);
t_dico		*reverse_dico(t_dico **top);
t_dico		*getitem_dico(t_dico *top, size_t pos);
//dico_2.c
void		printll_dico(t_dico *dico);
char		*put_key(int *i, int *j, char *env[]);
char		*put_value(int *i, int *j, char *env[]);
void		create_dico_list(t_dico **dico, char *env[]);
/* //dico_3.c
void		clean_dico_32(t_list **p, t_list **raw_tmp, t_list_i **flag_tmp);
void		clean_dico_helper(t_list **p, t_list **raw_tmp, t_list_i **flag_tmp);
void		clean_dico(t_list *p);
size_t		find_min_key(t_dico *dico);
size_t		find_max_key(t_dico *dico); */
//dico_4.c
void		duplicate(t_dico **orig, t_dico **copy);
char		*getword1(t_list **raw, char *search);
char		*delimitateur(t_list **raw);
//parsing_fd.c
void		readfd(t_scene *p, char **argv);
void		parsing(t_scene *p, char *line);
char		*get_numb(char *line);
//void		init_ambiant(t_scene *p, char *line);

//Array_2d.c
t_rgb		**create_2d_rgb(int cols, int rows);
t_vector	**create_2d_vector(int cols, int rows);
void		free_2d_rgb(t_rgb **rgb, int cols);
void		free_2d_vector(t_vector **vec, int cols);

/* ************************************************************************** */
#endif
