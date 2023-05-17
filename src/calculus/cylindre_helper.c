/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylindre_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:09:14 by jsollett          #+#    #+#             */
/*   Updated: 2023/05/17 16:41:01 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	compute_intersect_cyl(t_discr *delta, t_ray ray, t_cyl *Cyl)
{
	Cyl->intersect0 = add(ray.orig, scalar_prod(ray.dir, delta->tmin));
	Cyl->intersect1 = add(ray.orig, scalar_prod(ray.dir, delta->tmax));
	Cyl->w = sub(Cyl->intersect0, Cyl->C0);
	Cyl->v = sub(Cyl->intersect0, Cyl->C1);
	Cyl->w11 = sub(Cyl->intersect1, Cyl->C0);
	Cyl->v11 = sub(Cyl->intersect1, Cyl->C1);
}

void	select_side_cyl(t_scene *p)
{
	int	inside;

	inside = ((t_cyl *)(p->forme[p->closest->index].ptr))->inside;
	if (inside == 0)
	{
		p->data.intersection = ((t_cyl *)
				(p->forme[p->closest->index].ptr))->intersect0;
		p->data.normal = perpendicular(((t_cyl *)
					(p->forme[p->closest->index].ptr))->w, ((t_cyl *)
					(p->forme[p->closest->index].ptr))->ul);
	}
	else if (inside == 1)
	{
		p->data.intersection = ((t_cyl *)
				(p->forme[p->closest->index].ptr))->intersect1;
		p->data.normal = perpendicular(((t_cyl *)
					(p->forme[p->closest->index].ptr))->w11, ((t_cyl *)
					(p->forme[p->closest->index].ptr))->ul);
	}
}
