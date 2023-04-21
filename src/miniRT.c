/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:04:14 by grenaud-          #+#    #+#             */
/*   Updated: 2023/04/21 15:09:56 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

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

void	mlx_key(t_scene *p)
{
	mlx_key_hook(p->mlx_init.window, deal_key, &p);
	mlx_hook(p->mlx_init.window, 17, 1L << 0, destroy_window, &p);
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

void	ray_tracer_1(t_scene *p)
{
	int		i;
	int		j;
	double	min_dist;
	int		obj;
	int     count;

	obj = 0;
	count = 0;
	j = VIEWPORT_HEIGHT - 1;
  //  j = 200;
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
				if (p->forme[obj].id == 2)
				{
					closest_sphere(p, obj);
				}
				if (p->forme[obj].id == 1)
				{count++;
					closest_plan(p, obj, i, j);
				}
				obj++;
			}

			//put_sphere(p, p->closest->index, i, j);// faux a modifier
			put_sphere1(p, i, j);
		//	printf(RED"index plan %d\n"ENDC, p->closest->index);
		//	put_plan(p, p->closest->index, i, j);
			put_plan1(p, i, j);
			++i;
		//	init_closest(p->closest);// pb ici
		}
		--j;
	}
  //  printf(RED"count = %d\n"ENDC, count);
}

int		main(int argc, char **argv)
{
	t_scene	*p;
	(void) argc;
	p = wrmalloc(sizeof(t_scene));
	p = &(t_scene){0};
	p->delta = create_discriminant();
	p->closest = create_closest();
//	init_closest(p->closest);

	int			debug = 0;




	init_check(p, argv);
	parsing(p, argv);

	print_parsing(p, debug);
//	printf(RED"nb objet = %d\n"ENDC, p->n_obj);
//	ray_tracer_0(p, 0);
	ray_tracer_1(p);




	init_mlx(p, argv);
	//mlx_key(&p);
 	mlx_key_hook(p->mlx_init.window, deal_key, p);
	render(p);
	mlx_hook(p->mlx_init.window, 17, 1L << 0, destroy_window, p);
	mlx_hook(p->mlx_init.window, 17, 1L << 17, destroy_window, p);
	mlx_loop(p->mlx_init.mlx);

	wrdestroy();
	return (0);
}
