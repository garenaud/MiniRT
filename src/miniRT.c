/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:04:14 by grenaud-          #+#    #+#             */
/*   Updated: 2023/04/18 16:51:02 by jsollett         ###   ########.fr       */
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
/*
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
*/
void	put_sphere(t_scene *p, int obj, int i, int j)
{// a modifier, ici aussi a modifier 92, et voir la logique...
	double min_dist;

	if (p->forme[obj].id == 2) // sphere
	{// recalcul
		get_coeff_sph(p->delta, &p->ray, (t_sphere *)p->forme[obj].ptr);
		quadratic_solution2(p->delta);
		compute_intersect_sph(p->delta, p->ray, (t_sphere *)p->forme[obj].ptr);
		min_dist = sphere_hit((t_sphere *)p->forme[obj].ptr, p->delta,EPS);
		if (min_dist >= 0)
		{
			p->c.film[i][j] = ((t_sphere *)(p->forme[obj].ptr))->color;
		}
	}
}

void	put_sphere1(t_scene *p, int i, int j)
{
	//printf(GREEN"avant put sphere %d\n"ENDC, p->closest->index);
	if (p->closest->tmin != -1 && p->closest->type == 2)
	{
		p->c.film[i][j] = ((t_sphere *)(p->forme[p->closest->index].ptr))->color;
	}
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

void	ray_tracer_1(t_scene *p)
{// put_sphere logique error
	int		i;
	int		j;
	double min_dist;
	int		obj;

	obj = 0;
	j = VIEWPORT_HEIGHT - 1;
	while (j >= 0)
	{
		i = 0;
		while (i < VIEWPORT_WIDTH)
		{// sphere
			min_dist = 0;
            obj = 0;
			create_ray(p, i, j);
			while (obj < p->n_obj)
			{
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
						//	printf(GREEN"distance minimum of %d is \t%f\n"ENDC,obj, min_dist);
						}
						if (min_dist > 0 && min_dist < p->closest->dmin)
						{// erreur ici logique ? ou structure
						//	printf(GREEN"distance update of %d\t"ENDC, obj);
						//	p->closest->index = p->forme[obj].id;
							p->closest->index = obj;
							p->closest->tmin = p->delta->tmin;
							p->closest->dmin = min_dist;
							p->closest->type = p->forme[obj].id;
						//	printf(RED"update min distance is for %d \t %f\n"ENDC, p->closest->index, p->closest->dmin);

						}

					}
				}
				obj++;
			}

			//put_sphere(p, p->closest->index, i, j);// faux a modifier
			// printf("update min distance is for %d,%d %d \t %f\n"ENDC,i,j, p->closest->index, p->closest->dmin);
			put_sphere1(p, i, j);
			++i;
            init_closest(p->closest);// pb ici
		}
		--j;
	}
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
	printf(RED"nb objet = %d\n"ENDC, p->n_obj);
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
