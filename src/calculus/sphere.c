/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:26:06 by jsollett          #+#    #+#             */
/*   Updated: 2023/05/16 13:55:52 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	get_coeff_sph(t_discr *d, t_ray *ray, t_sphere *Sph)
{
	d->a = dot(ray->dir, ray->dir);
	d->b = 2 * dot(ray->dir, Sph->OC);
	d->c = Sph->discr_c;
	d->discr = discr(d->a, d->b, d->c);
}

void	compute_intersect_sph(t_discr *delta, t_ray ray, t_sphere *Sph)
{
	Sph->intersect0 = add(ray.orig, scalar_prod(ray.dir, delta->tmin));
}

double	sphere_hit(t_sphere *Sph, t_discr *delta, double eps)
{
	(void)delta;
	double	r_hit;

	r_hit = norm(sub(Sph->intersect0, Sph->C));
	if (egal(r_hit, Sph->r, eps))
	{
		return (r_hit);
	}
	else
		return (-1);
}

void	put_sphere(t_scene *p, int i, int j)
{
	p->data.diffusion = 0;
	if (p->closest->tmin != -1 && p->closest->type == 2)
	{
		p->data.intersection = ((t_sphere *)(p->forme[p->closest->index].ptr))->intersect0;
		p->data.normal = sub(p->data.intersection, ((t_sphere *)(p->forme[p->closest->index].ptr))->C);
		p->data.amb = *ambiant1(p);
		p->data.fp = free_path(p);
		if ((p->data.fp == -1 ||  p->data.fp == p->closest->index ) && (egal(p->l.cl->delta,0, EPS))
			&& light_side(&p->c.pos, &p->l.pos, &p->data.intersection, &p->data.normal) == 1)
				p->data.diffusion = p->l.lum * dot(p->data.normal, reverse(p->l.dir))/(norm(p->data.normal)*norm(p->l.dir));
		print_sph_film(p,i,j);
		saturation_pixel(p, i, j);
	}
}

void	print_sph_film(t_scene *p, int i, int j)
{
	p->c.film[i][j].rgb[0] = (p->data.amb.vec[0] + p->data.diffusion)*
		(((t_sphere *)(p->forme[p->closest->index].ptr))->color.rgb[0]);
	p->c.film[i][j].rgb[1] = (p->data.amb.vec[1] + p->data.diffusion)*
		(((t_sphere *)(p->forme[p->closest->index].ptr))->color.rgb[1]);
	p->c.film[i][j].rgb[2] = (p->data.amb.vec[2] + p->data.diffusion)*
		(((t_sphere *)(p->forme[p->closest->index].ptr))->color.rgb[2]);
}
