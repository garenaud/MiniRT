/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 17:18:06 by grenaud-          #+#    #+#             */
/*   Updated: 2023/05/16 12:12:58 by grenaud-         ###   ########.fr       */
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
# define ITALIC		"\033[3m"
# define DIM		"\033[2m"
# define WBGROUND	"\033[7m"
# define WRONG		"\033[9m"
# define BLUE		"\033[1;34m"

# define ESC		53
# define VIEWPORT_HEIGHT	1000
# define VIEWPORT_WIDTH		1000
# define MCC		255
# define POS_INF	1.0/0
# define PI			3.141592
# define EPS		0.001//0.00000001
# define DEBUG		0

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <math.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdbool.h>
# include <sys/time.h>

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include "../src/parsing/get_next_line.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

/* ************************************************************************** */
/* STRUCTS																	  */
/* ************************************************************************** */

typedef struct s_vector
{
	double	vec[3];
//	double	norm;
}			t_vector;
/*
typedef struct	s_vecteur
{
	double	arr[3];
	double	norm;
}			t_vecteur;
*/
typedef struct s_rgb
{
	int		rgb[3];
}			t_rgb;

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
	double	tr;
}			t_color;

// id = 1   plan
// id = 2   sphere
// id = 3   cylindre

typedef struct s_listobj
{
	int					index;
	int					id;
	t_vector			pos;
	t_vector			dir;
	double				r;
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

typedef struct	s_sphere
{
	int			index;
	t_rgb		color;
	t_vector	C;// centre
	t_vector	OC; // position camera vers centre C
	t_vector	intersect0;
	double		discr_c;
	double		OC_norm_2;
	double		r;
	double		r2;
}			t_sphere;

typedef struct	s_plan
{
	int			index;
	t_vector	C;
	t_vector	n;
	t_vector	OC; //ray to Po plan
	t_vector	intersect0;
	double		OCn;//(po-lo).n
	double		ndotray;
	double		tmin; //?
	t_rgb		color;
}			t_plan;

typedef struct	s_cyl
{
	t_rgb		color;
	int			index;
	t_discr		*discr;
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
	int			inside; // bool...
	//
	double		r;
	double		h;
}			t_cyl;
// new


typedef struct	s_objet
{
//	int			type;
	int			id;
	void		*ptr;
}			t_objet;

typedef struct	s_closest
{
	int			index;
	int			type;
	double		tmin;
	double		dmin;
	double		delta;

}			t_closest;

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
	t_vector	vup;
	t_vector	vp_middle;
	t_vector	w1;
	t_vector	u;
	t_vector	v;
	t_vector	ll;
	t_rgb		**film; // test
	double		fov;
	double		hor;
	double		ver;
}		t_camera;

typedef struct s_light
{
	int			check_l;
	t_vector	dir;
	t_vector	pos;
	t_vector	li;// light impact
	double		lum;
	t_ray		light; //0405
	t_rgb		color;
	t_closest	*cl;
	t_discr		*discr;
	// plan

	double  	ndotray_pl;
	double		OCn;
	t_vector    n;
	t_vector    OC;
	double      tmin;
	// cylindre
	t_cyl		*cyl;
}		t_light;

typedef struct s_check
{
	int		comm;
	int		fd_lines;
}		t_check;

// Necessaire...// ajout 17/04
typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_mlx
{
	void	*mlx;
	void	*window;
	t_img	img; // ajout 17/04
	char	*title;
}		t_mlx;

typedef struct s_scene
{
	char		*line;// parsing
	int			n_obj;// ou est il ?
	int			process;
	t_color		bg;
	t_ambiant	a;
	t_camera	c;
	t_light		l;
	t_ray		ray;
	t_objet		*forme;
	t_listobj	*obj;
	t_closest	*closest;
	t_check		check;
	t_mlx		mlx_init;
	t_discr		*delta;// AJOUT 1704
//	t_plan		pl;
}			t_scene;
/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */
//miniRT.c
void		mlx_key(t_scene *p);
void		init_check(t_scene *p, char **argv);

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
void		init_obj(t_scene *p, char *line, int index);
void		parsing(t_scene *p, char **argv);
void		read_fd(t_scene *p, int fd, int i);
char		*get_numb(t_scene *p, int index);
void		*trim_numb(char *line, int i);

/* ************************************************************************** */
//fd_data_init.c
void		init_ambiant(t_scene *p, int index);
void		init_cam(t_scene *p, int index);
void		init_light(t_scene *p, int index);

/* ************************************************************************** */
//fd_obj_init.c
void		push_cy(t_scene *p, int index);
void		push_sp(t_scene *p, int index);
void		push_pl(t_scene *p, int index);

/* ************************************************************************** */
//listobj_util.c
t_listobj	*init_listobj(void);
t_listobj	*getobj(t_listobj *top, int index);
void		add_to_list(t_listobj **head, t_listobj *new_element);
int			size_stack_obj(t_listobj *top);
void		printll_obj(t_listobj *obj);
void		delete_obj(t_listobj **top);

/* ************************************************************************** */
//check_line.c
char		*trim_line(char *line);
int			is_empty(char *line);
int			strlen_comm(t_scene *p, char *line);
char		*clean_comm(t_scene *p, char *line);
int			ft_count_lines(int fd);

/* ************************************************************************** */
//msg_error.c
void		message(char *msg, int index);
void		check_fd(int fd, char **argv);
void		check_struct(t_scene *p);
void		check_double(double value, int check, int index);
void		check_int(int value, int check, int index);

/* ************************************************************************** */
//utils.c
int			atoi_c(const char *str, int check, int index);

/* ************************************************************************** */
//windows.c
int			destroy_window(t_scene *p);
int			deal_key(int key_code, t_scene *p);
int			escape(int key_code, t_scene *p);
void		init_mlx(t_scene *p, char **argv);
void		free_and_exit(t_scene *p);

/* ************************************************************************** */
//draw.c
void		img_pix_put(t_mlx *d, int x, int y, t_rgb rgb);
void		render(t_scene *p);
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
void		print_parsing(t_scene *p, int debug);
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
int			egal_v(t_vector lhs, t_vector rhs, double tolerance);

/* ************************************************************************** */
// quadratic_solver.c
double		discr(double a, double b, double c);
void		test_quad_sol(t_discr *d);
void		quadratic_solution(t_discr *d, double a, double b, double c);
void		quadratic_solution2(t_discr *d);

/* ************************************************************************** */
// init_camera.c
void		init_camera(t_scene *p);
void		init_camera1(t_scene *p);
int			rgb_to_int(t_rgb rgb);
void		create_ray(t_scene *p, int i, int j);
void		init_film(t_scene *p, t_color back);

void		put_plan1(t_scene *p, int i, int j);
double		plan_hit(t_plan *P,  double eps, int debug );
double		plan_hit1(t_plan *p, t_scene *s);
void		put_plan(t_scene *p, int obj, int i, int j);
//void		closest_plan(t_scene *p, int obj, double eps, int debug);
void		compute_intersect_plan(t_ray ray, t_plan *P);
t_plan		*create_plan(void);
t_sphere	*create_sp(void);
t_cyl		*create_cy(void);
void		create_array(t_scene *s);
void		print_array(t_scene *p, t_objet *array);

t_discr		*create_discriminant(void);
t_closest	*create_closest(void);
//void		put_sphere(t_scene *p, int obj, int i, int j);
/* ************************************************************************** */
// sphere.c a controller
void		get_coeff_sph(t_discr *d, t_ray *ray, t_sphere *Sph);
void		compute_intersect_sph(t_discr *delta, t_ray ray, t_sphere *Sph);
double		sphere_hit(t_sphere *Sph, t_discr *delta, double eps);
void		put_sphere(t_scene *p, int obj, int i, int j);
void		put_sphere1(t_scene *p, int i, int j);
void		put_sphere2(t_scene *p, int i, int j);
/* ************************************************************************** */
// intersection.c a controller
void		closest_sphere(t_scene *p, int obj);
void		closest_plan(t_scene *p, int obj);
void		closest_cylindre(t_scene *p, int obj);
/* ************************************************************************** */
// cylindre.c a controller
void		get_coeff_cyl(t_discr *d, t_ray *ray, t_cyl *Cyl);
void		compute_intersect_cyl(t_discr *delta, t_ray ray, t_cyl *Cyl);
double		intersect_axe(t_cyl *Cyl, int param);
double		cylindre_hit(t_cyl *Cyl, t_discr *delta, double eps);
void		put_cylindre(t_scene *p, int i, int j);
/* ************************************************************************** */
// light.c a controller
void		ambiant(t_scene *p);
t_vector	*ambiant1(t_scene *p);
t_vector	ambiant2(t_scene *p);
int	        free_path(t_scene *p);

/* ************************************************************************** */
// spot.c a controller
void	ray_tracer_2(t_scene *p);

/* ************************************************************************** */
// spot.c a controller
int		shadow_sphere(t_scene *p, t_sphere *Sph);
void	shadow_plan(t_scene *p, t_plan *Pl);
void	light_intersect_sph(t_scene *p);
double	light_sphere_hit(t_scene *p,t_sphere *Sph);
void	closest_sphere1(t_scene *p, t_vector *intersect, int obj);
void	light_intersect_pl(t_scene *p);
void	closest_plan1(t_scene *p,t_vector *intersect, int obj);
double	light_plan_hit(t_scene *p);
int		light_side(t_vector *cam, t_vector *light, t_vector *intersect, t_vector *norm);
void	shadow_cyl(t_scene *p, t_cyl *Cyl);
//double	shadow_cyl(t_scene *p, t_cyl *Cyl);
void	closest_cylindre1(t_scene *p, t_vector *intersect, int obj);
void	put_cylindre1(t_scene *p, int i, int j);

/* ************************************************************************** */
// progressbar.c
void	console_info_processing(double perc);
void	screen_info_processing(t_scene *p);
void	reset_processing(t_scene *p);
double	get_duration(void);


int		key_hook(int keycode, t_scene *vars);
void	*trim_end(char *line);

void	plan_array(t_scene *s, int i);
void	sphere_array(t_scene *s, int i);
void	cyl_array(t_scene *s, int i);

#endif
