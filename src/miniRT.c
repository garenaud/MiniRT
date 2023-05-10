/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:04:14 by grenaud-          #+#    #+#             */
/*   Updated: 2023/05/09 17:02:40 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

int	key_hook(int keycode, t_scene *vars)
{
	(void) vars;
	printf("Hello from key_hook! keycode is %d\n", keycode);
	return (0);
}

void	init_check(t_scene *p, char **argv)
{
	int		fd;

	fd = open(argv[1], O_RDONLY);
	check_fd(fd, argv);
	p->check.fd_lines = ft_count_lines(fd);
/*	p->check.comm = 0;
	p->a.check_a = 0;
	p->l.check_l = 0;
	p->c.check_c = 0;*/
	//p->pl.index = 0;
	p->l.color.rgb[0] = 255;
	p->l.color.rgb[1] = 255;
	p->l.color.rgb[2] = 255;
	// setting background color
	p->bg.r = 0;
	p->bg.g = 0;
	p->bg.b = 0;
	p->obj = NULL;
	close(fd);
}
void	axe(t_scene *p, int i, int j)
{
		p->c.film[i][j].rgb[0] = 255;
		p->c.film[i][j].rgb[1] = 0;
		p->c.film[i][j].rgb[2] = 255;
}

void	mlx_key(t_scene *p)
{
	mlx_key_hook(p->mlx_init.window, deal_key, &p);
	mlx_hook(p->mlx_init.window, 02, 1L << 0, destroy_window, &p);
	mlx_hook(p->mlx_init.window, 17, 1L << 17, destroy_window, &p);
	mlx_loop(p->mlx_init.mlx);
}

/*
void	ray_tracer_0(t_scene *p, int obj)
{
	int		i;
	int		j;
	double min_dist;
	 //

	j = VIEWPORT_HEIGHT - 1;
	while (j >= 0)
	{
		i = 0;
		while (i < VIEWPORT_WIDTH)
		{// sphere
			create_ray(p, i, j);
			if (p->forme[obj].id == 2)
			{
				get_coeff_sph(p->delta, &p->ray, (t_sphere *)p->forme[obj].ptr);
				if (p->delta->discr >= 0)
				{
					quadratic_solution2(p->delta);
					compute_intersect_sph(p->delta, p->ray, (t_sphere *)p->forme[obj].ptr);
					if (sphere_hit((t_sphere *)p->forme[obj].ptr, p->delta,EPS) != -1)// modif 1804
					{// intersect0 sur la sphere
						min_dist = norm(sub(p->c.pos, ((t_sphere *)p->forme[obj].ptr)->intersect0));
					}
					if (min_dist >= 0 && min_dist < p->closest->dmin)
					{
					//	p->closest->index = p->forme[obj].id;
						p->closest->index = obj;
						p->closest->tmin = p->delta->tmin;
						p->closest->dmin = min_dist;
						p->closest->type = p->forme[obj].id;
					}
					put_sphere(p, obj, i, j);// faux a modifier
				//	put_sphere1(p, i, j);
				}
				//	printf("SPHERE\n");
			}
			++i;
		}
		--j;
	}
}
*/
//	printf(GREEN"distance minimum of %d is \t%f\n"ENDC,obj, min_dist);
// dans if min_dist > 0..
// erreur ici logique ? ou structure
//	printf(GREEN"distance update of %d\t"ENDC, obj);
//	p->closest->index = p->forme[obj].id;
//	printf(RED"update min distance is for %d \t %f\n"ENDC, p->closest->index, p->closest->dmin);
// put_sphere logique error
// modif 1804 (sphere_hit)

//void	ray_tracer_1(t_scene *p)
void	ray_tracer_2(t_scene *p)
{

	int		i;
	int		j;
	double	min_dist;
	int		obj;

	obj = 0;

	j = VIEWPORT_HEIGHT - 1;
	get_duration();
	while (j >= 0)
	{
		i = 0;
		while (i < VIEWPORT_WIDTH)
		{
			min_dist = 0;
			obj = 0;
			create_ray(p, i, j);
			init_closest(p->closest);// pb ici

			while (obj < p->n_obj)
			{
				if (p->forme[obj].id == 3)
				{
					closest_cylindre(p, obj);
				}
				if (p->forme[obj].id == 2)
				{
					closest_sphere(p, obj);
				}
				if (p->forme[obj].id == 1)
				{
					closest_plan(p, obj, i, j);
				}
				obj++;
			}

			//put_sphere(p, p->closest->index, i, j);// faux a modifier
			if (i == 200 && j == 650)
			{
				//printf("label\n");
			}
			put_cylindre1(p, i, j);
			//put_sphere1(p, i, j);
			put_sphere2(p,i,j);
			put_plan1(p, i, j);
			++i;
		}
		--j;
		screen_info_processing(p);
	}
	printf(BLUE"\nDuration   :   %.2fs\n"ENDC, get_duration());
}



int		main(int argc, char **argv)
{
	t_scene	*p;

	(void) argc;
	p = wrmalloc(sizeof(t_scene));
	p = &(t_scene){0};
	p->delta = create_discriminant();
	p->l.discr = create_discriminant();
	p->l.cyl = create_cy();
	p->l.cyl->discr = create_discriminant();
	p->closest = create_closest();
	p->l.cl = create_closest();



	//int			debug = 0;




	init_check(p, argv);
	parsing(p, argv);

	//print_parsing(p, debug);
//	printf(RED"ll - vpmiddle = %lf\n"ENDC, norm(sub(p->c.ll, p->c.vp_middle)));
//	ray_tracer_0(p, 0);
	//ray_tracer_1(p);
	ray_tracer_2(p);




	init_mlx(p, argv);
	//mlx_key(&p);
 	mlx_key_hook(p->mlx_init.window, deal_key, p);
	for (int i = 0; i < VIEWPORT_WIDTH; i++)
	{
//	axe(p, i, 460);
//	axe(p,450, i);
//	axe(p,i, 480);
  //  axe(p,200, i);
//	axe(p,i, 650);
//	axe(p,i, 423);
//	axe(p, 840, i);
//	axe(p, i, 950);
	}
	render(p);
	mlx_key(p);
	//mlx_key_hook(p->mlx_init.window, key_hook, &p);
	wrdestroy();
	return (0);
}
