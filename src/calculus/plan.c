/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:26:45 by jsollett          #+#    #+#             */
/*   Updated: 2023/05/18 10:54:52 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	compute_intersect_plan(t_ray ray, t_plan *P)
{
	P->ndotray = dot(P->n, ray.dir);
	if (not_egal(P->ndotray, 0.0, EPS))
	{
		P->tmin = P->ocn / P->ndotray;
		if (P->tmin >= 0)
			P->intersect0 = add(ray.orig, scalar_prod(ray.dir, P->tmin));
	}
}

double	plan_hit1(t_plan *p, t_scene *s)
{
	double		r_hit;

	r_hit = norm(sub(p->intersect0, s->c.pos));
	if (egal(dot(sub(p->intersect0, p->c), p->n), 0.0, EPS))
	{
		return (r_hit);
	}
	else
		return (-1);
}

void	put_plan(t_scene *p, int i, int j)
{
	double		p_tmin;
	t_vector	arg1;

	if (p->closest->type == 1)
	{
		p_tmin = ((t_plan *)(p->forme[p->closest->index].ptr))->tmin;
		p->data.intersection = ((t_plan *)
				((p->forme[p->closest->index].ptr)))->intersect0;
		arg1 = ((t_plan *)(p->forme[p->closest->index].ptr))->c;
		p->data.normal = ((t_plan *)(p->forme[p->closest->index].ptr))->n;
		p->data.diffusion = 0;
		if (p->closest->tmin != -1 && p->closest->type == 1
			&& egal(dot(p->data.normal,
					sub(p->data.intersection, arg1)), 0, EPS)
			== 1 && p_tmin > 0)
		{
			init_vector(&p->data.amb, p->a.color.rgb[0],
				p->a.color.rgb[1], p->a.color.rgb[2]);
			p->data.amb = scalar_prod(p->data.amb, p->a.lum / 255);
			p->data.fp = free_path(p);
			test_diffusion(p);
			print_plan_film(p, i, j);
			saturation_pixel(p, i, j);
		}
	}
}

void	test_diffusion(t_scene *p)
{
	if ((p->data.fp == -1 || p->data.fp == p->closest->index)
		&& (egal(p->l.cl->delta, 0, EPS))
		&& light_side(&p->c.pos, &p->l.pos, &p->data.intersection,
			&p->data.normal) == 1)
			p->data.diffusion = fabs(p->l.lum * dot(p->data.normal,
					reverse(p->l.dir))
				/ (norm(p->data.normal) * norm(p->l.dir)));
}

void	print_plan_film(t_scene *p, int i, int j)
{
	p->c.film[i][j].rgb[0] = (p->data.amb.vec[0] + p->data.diffusion)
		* (((t_plan *)(p->forme[p->closest->index].ptr))->color.rgb[0]);
	p->c.film[i][j].rgb[1] = (p->data.amb.vec[1] + p->data.diffusion)
		* (((t_plan *)(p->forme[p->closest->index].ptr))->color.rgb[1]);
	p->c.film[i][j].rgb[2] = (p->data.amb.vec[2] + p->data.diffusion)
		* (((t_plan *)(p->forme[p->closest->index].ptr))->color.rgb[2]);
}
