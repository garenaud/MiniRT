/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 10:10:29 by jsollett          #+#    #+#             */
/*   Updated: 2023/05/16 09:55:13 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	closest_cylindre(t_scene *p, int obj)
{
	double	min_dist;
	double	tmp;
	t_vector	intersect;

	min_dist = 0;
	get_coeff_cyl(p->delta, &p->ray, (t_cyl *)p->forme[obj].ptr);
	if (p->delta->discr >= 0)
	{
		quadratic_solution2(p->delta);
		compute_intersect_cyl(p->delta, p->ray, (t_cyl *)p->forme[obj].ptr);
		tmp = cylindre_hit((t_cyl *)p->forme[obj].ptr, p->delta, EPS);
		if (tmp >= 0)
		{
			intersect = add(p->ray.orig, scalar_prod(p->ray.dir,tmp));
			min_dist = norm(sub(p->c.pos, intersect));
		}
		else
			return ;
		if (min_dist >= 0 && min_dist < p->closest->dmin)
		{
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
		if (min_dist > 0 && min_dist < p->closest->dmin)
		{
			p->closest->index = obj;
			p->closest->tmin = p->delta->tmin;
			p->closest->dmin = min_dist;
			p->closest->type = p->forme[obj].id;
		}
	}
}

void	closest_plan(t_scene *p, int obj)
{
	double	min_dist;

	min_dist = 0;
	compute_intersect_plan(p->ray, (t_plan *)p->forme[obj].ptr);
	if (plan_hit1((t_plan *)p->forme[obj].ptr, p) != -1)
	{
		min_dist = norm(sub(p->c.pos, ((t_plan *)p->forme[obj].ptr)->intersect0));
		if (((t_plan *)p->forme[obj].ptr)->tmin >=1 && min_dist > 0 && min_dist < p->closest->dmin)
		{
			p->closest->index = obj;
			p->closest->tmin = (((t_plan *)p->forme[obj].ptr)->tmin);
			p->closest->dmin = min_dist;
			p->closest->type = p->forme[obj].id;
		}
	}
}
