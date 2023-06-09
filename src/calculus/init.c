/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:10:12 by jsollett          #+#    #+#             */
/*   Updated: 2023/05/18 11:01:22 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	init_vector(t_vector *v, double v0, double v1, double v2)
{
	v->vec[0] = v0;
	v->vec[1] = v1;
	v->vec[2] = v2;
}

void	init_ray(t_ray *ray, t_vector ori, t_vector dir)
{
	ray->orig = ori;
	ray->dir = dir;
}

void	init_sphere(t_sphere *sphere, t_vector center, double r)
{
	init_vector(&sphere->c, center.vec[0], center.vec[1], center.vec[2]);
	sphere->r = r;
	sphere->r2 = r * r;
}

void	init_plan(t_plan *plan, t_vector OC, t_vector n)
{
	init_vector(&plan->c, OC.vec[0], OC.vec[1], OC.vec[2]);
	init_vector(&plan->n, n.vec[0], n.vec[1], n.vec[2]);
}

void	init_cylindre(t_cyl *cyl, t_vector C, t_vector dir, t_vector OC)
{
	init_vector(&cyl->c0, C.vec[0], C.vec[1], C.vec[2]);
	init_vector(&cyl->dir, dir.vec[0], dir.vec[1], dir.vec[2]);
	init_vector(&cyl->oc, OC.vec[0], OC.vec[1], OC.vec[2]);
}
