/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:26:06 by jsollett          #+#    #+#             */
/*   Updated: 2023/05/18 11:26:31 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

double	light_sphere_hit(t_scene *p, t_sphere *Sph)
{
	double	r_hit;

	r_hit = norm(sub(p->l.li, Sph->c));
	if (egal(r_hit, Sph->r, EPS))
	{
		return (r_hit);
	}
	else
		return (-1);
}

void	light_intersect_sph(t_scene *p)
{
	p->l.li = add(p->l.pos, scalar_prod(p->l.dir, p->l.discr->tmin));
}

void	closest_sphere1(t_scene *p, t_vector *intersect, int obj)
{
	p->l.cl->min_dist = 0;
	shadow_sphere(p, (t_sphere *)p->forme[obj].ptr);
	if (p->l.discr->discr >= 0)
	{
		quadratic_solution2(p->l.discr);
		light_intersect_sph(p);
		if (light_sphere_hit(p, (t_sphere *)p->forme[obj].ptr) != -1)
			p->l.cl->min_dist = norm(sub(p->l.pos, p->l.li));
		if (p->l.cl->min_dist > 0 && p->l.cl->min_dist < p->l.cl->dmin)
			update_light_closest_sph(p, intersect, obj);
	}
}

void	update_light_closest_sph(t_scene *p, t_vector *intersect, int obj)
{
	p->l.cl->index = obj;
	p->l.cl->tmin = p->delta->tmin;
	p->l.cl->dmin = p->l.cl->min_dist;
	p->l.cl->type = p->forme[obj].id;
	p->l.cl->delta = norm(sub(p->l.li, *intersect));
}

int	light_side(t_vector *cam, t_vector *light, t_vector *i, t_vector *norm)
{
	t_vector	a;
	t_vector	b;

	a = sub(*cam, *i);
	b = sub(*light, *i);
	if ((dot(a, *norm) * dot(b, *norm)) > 0)
		return (1);
	else
		return (0);
}
