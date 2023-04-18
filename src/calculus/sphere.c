/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:26:06 by jsollett          #+#    #+#             */
/*   Updated: 2023/04/18 10:22:34 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	get_coeff_sph(t_discr *d, t_ray *ray, t_sphere *Sph)
{// a tester
	d->a = dot(ray->dir, ray->dir);
	d->b = 2 * dot(ray->dir, Sph->OC);
	d->c = Sph->discr_c;
	d->discr = discr(d->a, d->b, d->c);
}

void	compute_intersect_sph(t_discr *delta, t_ray ray, t_sphere *Sph)
{// pb
	Sph->intersect0 = add(ray.orig, scalar_prod(ray.dir, delta->tmin));
//	printv(&Sph->intersect0);
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
