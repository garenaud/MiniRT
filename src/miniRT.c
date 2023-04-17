/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:04:14 by grenaud-          #+#    #+#             */
/*   Updated: 2023/04/17 16:35:02 by jsollett         ###   ########.fr       */
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
	p->bg.r = 100;
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

t_objet	*transfer(t_scene *s)
{
	int		size;
	t_objet	*objet;
	t_plan	*plan;
	int		i;

	i = 0;
	size = size_stack_obj(s->obj);
	objet = (t_objet *)wrmalloc(size * sizeof(t_objet));
	plan = (t_plan *)wrmalloc(size * sizeof(t_plan));
	while (s->obj)
	{
		if (s->obj->id == 1)
		{
			objet[i].id = 1;
			objet[i].ptr = &plan[i];
			init_vector(&plan[i].C, s->obj->pos.vec[0], s->obj->pos.vec[1], s->obj->pos.vec[2]);
			init_vector(&plan[i].n, s->obj->dir.vec[0], s->obj->dir.vec[1], s->obj->dir.vec[2]);
			init_plan(&plan[i], plan[i].C, unit(plan[i].n));
			plan[i].OC = sub(plan[i].C, s->c.pos);//cam pos de la camera...
				//p->OC = sub(p0, cam); // a tester
				//p->OCn = dot(p->OC, p->n); // a tester
			plan[i].OCn = dot(plan[i].OC, plan[i].n);
			plan[i].index = i;
		}
		if (s->obj->id == 2)
		{
		}
		if (s->obj->id == 3)
		{
		}
		s->obj = s->obj->next;
	}
	return (objet);
}

void	put_sphere(t_scene *p, int obj, int i, int j)
{// a modifier
	double min_dist;

	if (p->forme[obj].id == 2) // sphere
	{// recalcul
		get_coeff_sph(p->delta, p->ray, *(t_sphere *)p->forme[obj].ptr);
		quadratic_solution2(p->delta);
		compute_intersect_sph(p->delta, p->ray, (t_sphere *)p->forme[obj].ptr);
		min_dist = sphere_hit((t_sphere *)p->forme[obj].ptr, p->delta,EPS);
		if (min_dist >= 0)
		{
			p->c.film[i][j] = ((t_sphere *)(p->forme[obj].ptr))->color;

			//rgb[i][j].rgb[0] = 125;
			//rgb[i][j].rgb[1] = 25;
			//rgb[i][j].rgb[2] = 125;
		}
	}
}

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
			if (p->forme[obj].id == 2)
			{
				get_coeff_sph(p->delta, p->ray, *(t_sphere *)p->forme[obj].ptr);
				if (p->delta->discr >= 0)
				{
					quadratic_solution2(p->delta);
					compute_intersect_sph(p->delta, p->ray, (t_sphere *)p->forme[obj].ptr);
					min_dist = sphere_hit((t_sphere *)p->forme[obj].ptr, p->delta,EPS);
					if (min_dist >= 0 && min_dist < p->closest->tmin)
					{
					//	p->closest->index = p->forme[obj].id;
						p->closest->index = obj;
						p->closest->tmin = sphere_hit((t_sphere *)p->forme[obj].ptr, p->delta, EPS);
						p->closest->type = p->forme[obj].id;
					}
				}
				//	printf("SPHERE\n");
			}
			++i;
		}
		--j;
	}
	put_sphere(p, obj, i, j);
}


int		main(int argc, char **argv)
{
	t_scene	*p;
	(void) argc;
	p = wrmalloc(sizeof(t_scene));
	p = &(t_scene){0};
	p->delta = create_discriminant();
	p->closest = create_closest();
	init_closest(p->closest);

	int			debug = 1;




	init_check(p, argv);
	parsing(p, argv);

	print_parsing(p, debug);
	ray_tracer_0(p, 0);




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
