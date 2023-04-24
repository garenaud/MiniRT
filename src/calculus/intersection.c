/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 10:10:29 by jsollett          #+#    #+#             */
/*   Updated: 2023/04/24 15:19:40 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	closest_cylindre(t_scene *p, int obj)
{
	double	min_dist;

	min_dist = 0;
	get_coeff_cyl(p->delta, &p->ray, (t_cyl *)p->forme[obj].ptr);
	if (p->delta->discr >= 0)
	{
		quadratic_solution2(p->delta);
		compute_intersect_cyl(p->delta, p->ray, (t_cyl *)p->forme[obj].ptr);
		min_dist = cylindre_hit((t_cyl *)p->forme[obj].ptr, p->delta, EPS);
		if (min_dist >= 0 && min_dist < p->closest->tmin)
		{// a verifier
			p->closest->index = obj;
			p->closest->tmin = p->delta->tmin;
			p->closest->dmin = min_dist;
			p->closest->type = p->forme[obj].id;
		}
	}
}

void	closest_sphere(t_scene *p, int obj)
{
	double	min_dist;

	min_dist = 0;
	get_coeff_sph(p->delta, &p->ray, (t_sphere *)p->forme[obj].ptr);
	if (p->delta->discr >= 0)
	{
		quadratic_solution2(p->delta);
		compute_intersect_sph(p->delta, p->ray, (t_sphere *)p->forme[obj].ptr);
		if (sphere_hit((t_sphere *)p->forme[obj].ptr, p->delta, EPS) != -1)
		{
			min_dist = norm(sub(p->c.pos,
						((t_sphere *)p->forme[obj].ptr)->intersect0));
		}
		if (/*((t_sphere *)p->forme[obj].ptr)->tmin >=1 &&*/ min_dist > 0 && min_dist < p->closest->dmin)
		{
			p->closest->index = obj;
			p->closest->tmin = p->delta->tmin;
			p->closest->dmin = min_dist;
			p->closest->type = p->forme[obj].id;
		}
	}
}

void	closest_plan(t_scene *p, int obj, int i, int j)
{
	double	min_dist;
	int debug;

	min_dist = 0;
	debug = 0;
/*	if (j % 240 == 0 && i % 40 == 0)
		debug = 1;
	else
		debug = 0;*/
	compute_intersect_plan(p->ray, (t_plan *)p->forme[obj].ptr, debug);
	if (plan_hit1((t_plan *)p->forme[obj].ptr, p) != -1)
	{

		if (debug)
		printf("\tcalcul min\t");
		min_dist = norm(sub(p->c.pos, ((t_plan *)p->forme[obj].ptr)->intersect0));
		if (((t_plan *)p->forme[obj].ptr)->tmin >=1 && min_dist > 0 && min_dist < p->closest->dmin)
		{
			p->closest->index = obj;
			p->closest->tmin = (((t_plan *)p->forme[obj].ptr)->tmin);
			p->closest->dmin = min_dist;
			p->closest->type = p->forme[obj].id;
		}
		if ((j % 240) == 0 && (i % 40) == 0)
		{
			printf("(i,j) = (%d,%d)\t",i,j);
			printf(RED"obj = %d, mdist = %10.10lf, p->closest->dmin = %10.10lf \t"ENDC, obj, min_dist, p->closest->dmin);
			printv(&((t_plan *)p->forme[obj].ptr)->intersect0);
		 // printv(&p->ray.dir);
		}
	}
}
