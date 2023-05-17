/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylindre.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 09:39:21 by jsollett          #+#    #+#             */
/*   Updated: 2023/05/17 14:17:49 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	get_coeff_cyl(t_discr *d, t_ray *ray, t_cyl *Cyl)
{
	d->a = norm_2(ray->dir) - pow(dot(ray->dir, Cyl->ul), 2);
	d->b = 2 * dot(Cyl->w1, ray->dir)
		- 2 * dot(ray->dir, Cyl->ul) * dot(Cyl->w1, Cyl->ul);
	d->c = norm_2(Cyl->w1) - pow(dot(Cyl->w1, Cyl->ul), 2) - Cyl->r * Cyl->r;
	d->discr = discr(d->a, d->b, d->c);
}

double	intersect_axe(t_cyl *Cyl, int param)
{
	t_vector	v_tmp;
	double		tmp;

	tmp = -1.0;
	if (param == 0)
	{
		v_tmp = sub(Cyl->intersect0, Cyl->C0);
		tmp = norm(perpendicular(v_tmp, Cyl->ul));
	}
	if (param == 1)
	{
		v_tmp = sub(Cyl->intersect1, Cyl->C0);
		tmp = norm(perpendicular(v_tmp, Cyl->ul));
	}
	return (tmp);
}

double	cylindre_hit(t_cyl *Cyl, t_discr *delta, double eps)
{
	if ((dot(Cyl->w, Cyl->vl) * dot(Cyl->v, Cyl->vl) <= 0))
	{
		if (egal(intersect_axe((Cyl), 0), Cyl->r, eps))
		{
			Cyl->inside = 0;
			return (delta->tmin);
		}
	}
	else
	{
		if ((dot(Cyl->w11, Cyl->vl) * dot(Cyl->v11, Cyl->vl)) <= 0)
		{
			if (egal(intersect_axe((Cyl), 1), Cyl->r, eps))
			{
				Cyl->inside = 1;
				return (delta->tmax);
			}
		}
	}
	Cyl->inside = 2;
	return (-1);
}

void	put_cylindre(t_scene *p, int i, int j)
{
	p->data.diffusion = 0;
	if (p->closest->type == 3 && p->closest->tmin != 1)
	{
		select_side_cyl(p);
		init_vector(&p->data.amb, p->a.color.rgb[0],
			p->a.color.rgb[1], p->a.color.rgb[2]);
		p->data.amb = scalar_prod(p->data.amb, p->a.lum / 255);
		p->data.fp = free_path(p);
		if ((p->data.fp == -1 || p->data.fp == p->closest->index)
			&& (egal(p->l.cl->delta, 0, EPS))
			&& light_side(&p->c.pos, &p->l.pos, &p->data.intersection,
				&p->data.normal) == 1)
					p->data.diffusion = fabs((p->l.lum * dot(p->data.normal,
							reverse(p->l.dir))
						/ (norm(p->data.normal) * norm(p->l.dir))));
		print_cyl_film(p, i, j);
		saturation_pixel(p, i, j);
	}
}

void	print_cyl_film(t_scene *p, int i, int j)
{
	p->c.film[i][j].rgb[0] = (p->data.amb.vec[0] + p->data.diffusion)
		* (((t_cyl *)(p->forme[p->closest->index].ptr))->color.rgb[0]);
	p->c.film[i][j].rgb[1] = (p->data.amb.vec[1] + p->data.diffusion)
		* (((t_cyl *)(p->forme[p->closest->index].ptr))->color.rgb[1]);
	p->c.film[i][j].rgb[2] = (p->data.amb.vec[2] + p->data.diffusion)
		* (((t_cyl *)(p->forme[p->closest->index].ptr))->color.rgb[2]);
}
