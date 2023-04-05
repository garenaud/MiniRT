/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 17:18:06 by grenaud-          #+#    #+#             */
/*   Updated: 2023/04/05 16:38:40 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define RED		"\033[1m\033[31m"
# define GREEN		"\033[1m\033[32m"
# define ORANGE		"\033[1m\033[33m"
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
# include <stddef.h>
# include <stdbool.h>

# include "libft/libft.h"
# include "mlx/mlx.h"
# include "parsing/get_next_line.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

/* ************************************************************************** */
/* STRUCTS																	  */
/* ************************************************************************** */

typedef struct s_vector
{
	double	vec[3];
	double	norm;
}			t_vector;

typedef struct s_rgb
{
	int		rgb[3];
}			t_rgb;

typedef struct s_listobj
{
	int					index;
	char				*id;
	t_vector			pos;
	t_vector			dir;
	double				diam;
	double				h;
	t_rgb				color;
	struct s_listobj	*next;
}			t_listobj;

typedef struct s_list
{
	char			*data;
	struct s_list	*next;
}		t_list;

typedef struct s_list_i
{
	int				data;
	struct s_list_i	*next;
}		t_list_i;

typedef struct s_ambiant
{
	int			check_a;
	double		lum;
	t_rgb		color;
}		t_ambiant;

typedef struct s_camera
{
	int			check_c;
	t_vector	pos;
	t_vector	dir;
	double		fov;
}		t_camera;

typedef struct s_light
{
	int			check_l;
	t_vector	pos;
	double		lum;
	t_rgb		color;
}		t_light;

typedef struct s_check
{
	int		comm;
	int		fd_lines;
}		t_check;

typedef struct s_scene
{
	t_ambiant	a;
	t_camera	c;
	t_light		l;
	t_listobj	*obj;
	t_check		check;
}			t_scene;
/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */
//ft_atod.c
int			sign_atod(char c);
double		int_part(char c, double result);
double		frac_part(char *str);
int			frac_len(char *str);
double		ascii_to_double(char *str, int check, int index);

/* ************************************************************************** */
//get_next_line.c
char		*ft_get_start(char *raw_line);
char		*ft_get_line(char *raw_line);
char		*ft_get_raw_line(int fd, char *raw_line);
char		*get_next_line(int fd);
/* ************************************************************************** */

//parsing_fd.c
void		init_ambiant(t_scene *p, char *line, int index);
void		init_cam(t_scene *p, char *line, int index);
void		init_light(t_scene *p, char *line, int index);
void		parsing(t_scene *p, char **argv);
char		*get_numb(char *line, int index);
//void		init_data(t_scene *p);
//void		init_ambiant(t_scene *p, char *line);
//list_cy.c
t_listobj	*init_listobj(t_scene *p);
int			size_stack_obj(t_listobj *top);
void		printll_obj(t_listobj *obj);
void		push_cy(t_scene *p, char *line, int index);
void		push_sp(t_scene *p, char *line, int index);
void		push_pl(t_scene *p, char *line, int index);
void		add_to_list(t_listobj **head, t_listobj *new_element);
void		delete_obj(t_listobj **top);

//check_line.c
int			is_empty(char *line);
int			strlen_comm(t_scene *p, char *line);
char		*clean_comm(t_scene *p, char *line);
char		*trim_line(char *line);
int			ft_count_lines(int fd);
void		init_check(t_scene *p, char **argv);
void		message(char *msg, int index);
void		check_fd(int fd, char **argv);
void		check_struct(t_scene *p);
void		read_fd(t_scene *p, int fd, int i);
t_listobj	*getobj(t_listobj *top, int index);
void		check_int(int value, int check, int index);
void		check_double(double value, int check, int index);
int			ft_atoi_check(const char *str, int check, int index);

//Array_2d.c
t_rgb		**create_2d_rgb(int cols, int rows);
t_vector	**create_2d_vector(int cols, int rows);
void		free_2d_rgb(t_rgb **rgb, int cols);
void		free_2d_vector(t_vector **vec, int cols);

/* ************************************************************************** */
#endif
