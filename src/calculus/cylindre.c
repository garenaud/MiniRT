/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylindre.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 09:39:21 by jsollett          #+#    #+#             */
/*   Updated: 2023/05/05 15:11:03 by jsollett         ###   ########.fr       */
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

void	compute_intersect_cyl(t_discr *delta, t_ray ray, t_cyl *Cyl)
{
	Cyl->intersect0 = add(ray.orig, scalar_prod(ray.dir, delta->tmin));
	Cyl->intersect1 = add(ray.orig, scalar_prod(ray.dir, delta->tmax));
	Cyl->w = sub(Cyl->intersect0, Cyl->C0);
	Cyl->v = sub(Cyl->intersect0, Cyl->C1);
	Cyl->w11 = sub(Cyl->intersect1, Cyl->C0);
	Cyl->v11 = sub(Cyl->intersect1, Cyl->C1);
}

double	intersect_axe(t_cyl *Cyl, int param)
{//a tester
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
//	intersect0 lie a  tmin
//	intersect1 lie a  tmax

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
{// ajout if
	t_vector	*amb;

	if (p->closest->type == 3 && p->closest->tmin != 1)
	{
		amb = ambiant1(p);
		if ((free_path(p,i,j) == -1 || free_path(p,i,j) == p->closest->index) && (egal(p->l.cl->delta,0, EPS)))
			*amb = scalar_prod(*amb, 2);
		//p->c.film[i][j] = ((t_cyl *)(p->forme[p->closest->index].ptr))->color;
		p->c.film[i][j].rgb[0] = amb->vec[0]*(((t_cyl *)(p->forme[p->closest->index].ptr))->color.rgb[0]);
		p->c.film[i][j].rgb[1] = amb->vec[1]*(((t_cyl *)(p->forme[p->closest->index].ptr))->color.rgb[1]);
		p->c.film[i][j].rgb[2] = amb->vec[2]*(((t_cyl *)(p->forme[p->closest->index].ptr))->color.rgb[2]);
		free(amb);
	}
}

void	put_cylindre1(t_scene *p, int i, int j)
{// ajout if
	t_vector	*amb;
	int			inside;

	if (p->closest->type == 3 && p->closest->tmin != 1)
	{
		inside = ((t_cyl *)(p->forme[p->closest->index].ptr))->inside;
		if (i == 840)
			printf(RED"i = %d, j = %d, inside = %d\n", i, j, inside);
		amb = ambiant1(p);
		if ( (free_path(p,i,j) == -1 || free_path(p,i,j) == p->closest->index) && (egal(p->l.cl->delta,0, EPS)))
			*amb = scalar_prod(*amb, 2);
		//p->c.film[i][j] = ((t_cyl *)(p->forme[p->closest->index].ptr))->color;
		p->c.film[i][j].rgb[0] = amb->vec[0]*(((t_cyl *)(p->forme[p->closest->index].ptr))->color.rgb[0]);
		p->c.film[i][j].rgb[1] = amb->vec[1]*(((t_cyl *)(p->forme[p->closest->index].ptr))->color.rgb[1]);
		p->c.film[i][j].rgb[2] = amb->vec[2]*(((t_cyl *)(p->forme[p->closest->index].ptr))->color.rgb[2]);
		free(amb);
	}
}
