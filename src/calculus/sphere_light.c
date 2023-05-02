/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:26:06 by jsollett          #+#    #+#             */
/*   Updated: 2023/05/02 16:01:18 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

int	shadow_sphere(t_scene *p, t_sphere *Sph, int obj)
{// a tester -> modification light
	(void)obj;
	t_vector	OC;
	//t_discr		d;
	t_vector	intersect;
//	t_vector	C;

	if (p->forme[p->closest->index].id == 2)
		intersect = ((t_sphere *)(p->forme[p->closest->index].ptr))->intersect0;
	if (p->forme[p->closest->index].id == 1)
		intersect = ((t_plan *)(p->forme[p->closest->index].ptr))->intersect0;
	//C = ((t_sphere *)(p->forme[p->closest->index].ptr))->C;
	OC = sub(p->l.pos, Sph->C);// si j'intervertit ici ?? 0105
	//OC = sub(Sph->C, p->l.pos);// intervertit ici ?? 0105 cela casse le code ?
	p->l.dir = unit(sub(intersect, p->l.pos));

	p->l.discr->a = dot(p->l.dir, p->l.dir);//
	p->l.discr->b = 2 * dot(p->l.dir, OC);
	p->l.discr->c = norm_2(OC) - Sph->r2;
	p->l.discr->discr = discr(p->l.discr->a, p->l.discr->b, p->l.discr->c);
	if (p->l.discr->discr >= 0)
		return (1);
	else
		return (0);
}

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
	shadow_sphere(p, (t_sphere *)p->forme[obj].ptr, obj);
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


void	shadow_plan(t_scene *p, t_plan *Pl)
{
	t_vector	intersect;
/*	double	OCn;*/
	if (p->forme[p->closest->index].id == 1)
		intersect = ((t_plan *)(p->forme[p->closest->index].ptr))->intersect0;
	if (p->forme[p->closest->index].id == 2)
		intersect = ((t_sphere *)(p->forme[p->closest->index].ptr))->intersect0;
	p->l.OCn = dot(sub(Pl->C, p->l.pos), Pl->n);
	p->l.dir = unit(sub(intersect, p->l.pos));
	p->l.ndotray_pl = dot(Pl->n, p->l.dir);
	p->l.n = Pl->n;
	p->l.OC = Pl->OC;
	/*if (not_egal(ndotraylight, 0.0, EPS))
	{
		if (OCn / ndotraylight >= 0)
			return (1);
		else
			return (0);
	}
	else
		return (0);*/
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
