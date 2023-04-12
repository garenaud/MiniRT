/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 17:18:06 by grenaud-          #+#    #+#             */
/*   Updated: 2023/03/16 12:23:32 by grenaud-         ###   ########.fr       */
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
# define VIEWPORT_HEIGHT	128
# define VIEWPORT_WIDTH		128
# define MCC		255
# define POS_INF	1.0/0


# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <math.h>
# include <stdlib.h>

# include "libft/libft.h"
//# include "mlx/mlx.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

/* ************************************************************************** */
/* STRUCTS																	  */
/* ************************************************************************** */

typedef struct s_dico
{
	int				key;
	void			*value;
	struct s_dico	*next;
}	t_dico;

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

typedef struct	s_vecteur
{
	double	arr[3];
	double	norm;
}			t_vecteur;

typedef struct s_listobj
{// modification
	int					index;
	int					id;
	t_vector			pos;
	t_vector			dir;
	double				r;// plutot rayon
	double				h;
	t_rgb				color;
//	struct s_listobj	*next;
}			t_listobj;

// new
typedef struct	s_ray
{
	t_vector	orig;
	t_vector	dir;
}			t_ray;



typedef struct	s_cam
{
	t_vector	pos;
	t_vector	lookat;
}			t_cam;

typedef struct	s_sphere
{
	t_vector	C;
	t_vector	OC;
	t_vector	intersect0;
	double		discr_c;
	double		OC_norm_2;
	double		r;
	double		r2;
}			t_sphere;

typedef struct	s_plan
{
	int			label;
	t_vector	C;
	t_vector	n;
	t_vector	OC; //ray to Po plan
	t_vector	intersect0;
	double		OCn;//(po-lo).n
	double		ndotray;
	double		tmin; //?
}			t_plan;

typedef struct	s_cyl
{
	t_vector	C0;
	t_vector	C1;
	t_vector	dir;
	t_vector	OC;
	t_vector	vl;//c1-c0
	t_vector	ul;// |vl|
	t_vector	w1;//ray orig - c0
	// intersect et variable pour calcul inside outside
	t_vector	intersect0;
	t_vector	intersect1;
	t_vector	v;
	t_vector	w;
	t_vector	v11;
	t_vector	w11;
	double		tmp;
	int			inside; // bool...
	// 
	double		r;
	double		h;
}			t_cyl;
// new
typedef struct	s_discr
{
	double		t1;
	double		t2;
	double		tmin;
	double		tmax;
	double		discr;
	double		a;
	double		b;
	double		c;
}			t_discr;

typedef struct	s_objet
{
	int			type;
	void		*ptr;;
}			t_objet;

typedef struct	s_closest
{
	int			index;
	int			type;
	double		tmin;
	
}			t_closest;

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
//Array_2d.c
t_rgb		**create_2d_rgb(int cols, int rows);
t_vector	**create_2d_vector(int cols, int rows);
void		free_2d_rgb(t_rgb **rgb, int cols);
void		free_2d_vector(t_vector **vec, int cols);

/* ************************************************************************** */
//init.c
void		init_vector(t_vector *v, double v0, double v1, double v2);
void		init_ray(t_ray *ray,t_vector ori, t_vector dir);
void		init_sphere(t_sphere *sphere, t_vector center, double r);
void		init_plan(t_plan *plan, t_vector OC, t_vector n);
void		init_cylindre(t_cyl *cyl, t_vector C, t_vector dir, t_vector OC);

/* ************************************************************************** */
//init2.c

void		init2_cylindre(t_cyl *Cyl, t_vector cam, double r, double h);
void		init_closest(t_closest *close);
void		background(t_rgb **rgb, t_color color, int i, int j);
/* ************************************************************************** */
//print.c
void		printv(t_vector *v);
void		print(t_rgb **array, int col, int row);
/* ************************************************************************** */
//vecteur_op1.c
t_vector	reverse(t_vector v);
t_vector	add(t_vector v1, t_vector v2);
t_vector	sub(t_vector v1, t_vector v2);
t_vector	scalar_prod(t_vector v, double t);

/* ************************************************************************** */
//vecteur_op2.c
double		dot(t_vector v1, t_vector v2);
double		norm_2(t_vector v);
double		norm(t_vector v);
t_vector	cross(t_vector v1, t_vector v2);
t_vector	unit(t_vector v);

/* ************************************************************************** */
//vecteur_op3.c

t_vector	projection(t_vector from, t_vector to);
t_vector	perpendicular(t_vector from, t_vector to);
double		distance(t_vector point, t_vector segment1, t_vector segment2);

/* ************************************************************************** */
//util.c
int			egal(double lhs, double rhs, double tolerance);
int			not_egal(double lhs, double rhs, double tolerance);

/* ************************************************************************** */
// quadratic_solver.c
double		discr(double a, double b, double c);
void		test_quad_sol(t_discr *d);
void		quadratic_solution(t_discr *d, double a, double b, double c);
void		quadratic_solution2(t_discr *d);
#endif
