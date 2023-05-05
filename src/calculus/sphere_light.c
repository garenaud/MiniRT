/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:26:06 by jsollett          #+#    #+#             */
/*   Updated: 2023/05/03 11:59:01 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

double	light_sphere_hit(t_scene *p,t_sphere *Sph)
{

	double	r_hit;

	r_hit = norm(sub(p->l.li, Sph->C));
	if (egal(r_hit, Sph->r, EPS))
	{
		return (r_hit);
	}
	else
		return (-1);
}

void	light_intersect_sph(t_scene *p)
{// pb
	p->l.li = add(p->l.pos, scalar_prod(p->l.dir, p->l.discr->tmin));
//	printv(&Sph->intersect0);
}

void	closest_sphere1(t_scene *p, t_vector *intersect, int obj)
{
	double	min_dist;

	min_dist = 0;
	shadow_sphere(p, (t_sphere *)p->forme[obj].ptr);
//	get_coeff_sph(p->delta, &p->ray, (t_sphere *)p->forme[obj].ptr);
	if (p->l.discr->discr >= 0)
	{
		quadratic_solution2(p->l.discr);
		light_intersect_sph(p);
		//compute_intersect_sph(p->delta, p->ray, (t_sphere *)p->forme[obj].ptr);
		if (light_sphere_hit(p, (t_sphere *)p->forme[obj].ptr) != -1)
			min_dist = norm(sub(p->l.pos, p->l.li));
		if ( min_dist > 0 && min_dist < p->l.cl->dmin)
		{
			p->l.cl->index = obj;
			p->l.cl->tmin = p->delta->tmin;
			p->l.cl->dmin = min_dist;
			p->l.cl->type = p->forme[obj].id;
			p->l.cl->delta = norm(sub(p->l.li, *intersect));
		}
	}
}

int		light_side(t_vector *cam, t_vector *light, t_vector *intersect, t_vector *norm)
{
	t_vector	a;
	t_vector	b;

	a = sub(*cam, *intersect);
	b = sub(*light, *intersect);
	if ((dot(a, *norm) * dot(b, *norm)) > 0)
		return (1);
	else
		return (0);
}
