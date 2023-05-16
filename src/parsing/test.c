/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 10:23:16 by grenaud-          #+#    #+#             */
/*   Updated: 2023/05/16 14:11:12 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	create_array(t_scene *s)
{
	int			i;
	t_listobj	*start;

	start = s->obj;
	i = 0;
	while (s->obj)
	{
		if (s->obj->id == 1)
			plan_array(s, i);
		if (s->obj->id == 2)
			sphere_array(s, i);
		if (s->obj->id == 3)
			cyl_array(s, i);
		s->obj = s->obj->next;
		i++;
	}
	s->obj = start;
	s->n_obj = i;
}

void	plan_array(t_scene *s, int i)
{
	s->forme[i].ptr = create_plan();
	s->forme[i].id = 1;
	init_vector(&((t_plan *)(s->forme[i].ptr))->C, s->obj->pos.vec[0],
		s->obj->pos.vec[1], s->obj->pos.vec[2]);
	init_vector(&((t_plan *)(s->forme[i].ptr))->n, s->obj->dir.vec[0],
		s->obj->dir.vec[1], s->obj->dir.vec[2]);
	init_plan(((t_plan *)(s->forme[i].ptr)), ((t_plan *)(s->forme[i].ptr))->C,
		unit(((t_plan *)(s->forme[i].ptr))->n));
	((t_plan *)(s->forme[i].ptr))->OC = sub(((t_plan *)(s->forme[i].ptr))->C,
			s->c.pos);
	((t_plan *)(s->forme[i].ptr))->OCn = dot(((t_plan *)(s->forme[i].ptr))->OC,
			((t_plan *)(s->forme[i].ptr))->n);
	((t_plan *)(s->forme[i].ptr))->color.rgb[0] = s->obj->color.rgb[0];
	((t_plan *)(s->forme[i].ptr))->color.rgb[1] = s->obj->color.rgb[1];
	((t_plan *)(s->forme[i].ptr))->color.rgb[2] = s->obj->color.rgb[2];
	((t_plan *)(s->forme[i].ptr))->index = i;
}

void	sphere_array(t_scene *s, int i)
{
	s->forme[i].ptr = create_sp();
	s->forme[i].id = 2;
	init_vector(&((t_sphere *)(s->forme[i].ptr))->C, s->obj->pos.vec[0],
		s->obj->pos.vec[1], s->obj->pos.vec[2]);
	init_sphere(((t_sphere *)(s->forme[i].ptr)),
		((t_sphere *)(s->forme[i].ptr))->C, s->obj->r);
	((t_sphere *)(s->forme[i].ptr))->OC = sub(s->c.pos,
			((t_sphere *)(s->forme[i].ptr))->C);
	((t_sphere *)(s->forme[i].ptr))->discr_c = norm_2(((t_sphere *)
				(s->forme[i].ptr))->OC) - ((t_sphere *)(s->forme[i].ptr))->r2;
	((t_sphere *)(s->forme[i].ptr))->color.rgb[0] = s->obj->color.rgb[0];
	((t_sphere *)(s->forme[i].ptr))->color.rgb[1] = s->obj->color.rgb[1];
	((t_sphere *)(s->forme[i].ptr))->color.rgb[2] = s->obj->color.rgb[2];
	((t_sphere *)(s->forme[i].ptr))->index = i;
}

void	cyl_array(t_scene *s, int i)
{
	s->forme[i].ptr = create_cy();
	s->forme[i].id = 3;
	init_vector(&((t_cyl *)(s->forme[i].ptr))->C0, s->obj->pos.vec[0],
		s->obj->pos.vec[1], s->obj->pos.vec[2]);
	init_vector(&((t_cyl *)(s->forme[i].ptr))->dir, s->obj->dir.vec[0],
		s->obj->dir.vec[1], s->obj->dir.vec[2]);
	init_cylindre(((t_cyl *)(s->forme[i].ptr)),
		((t_cyl *)(s->forme[i].ptr))->C0,
		((t_cyl *)(s->forme[i].ptr))->dir,
		sub(((t_cyl *)(s->forme[i].ptr))->C0, s->c.pos));
	init2_cylindre(((t_cyl *)(s->forme[i].ptr)),
		s->c.pos, s->obj->r, s->obj->h);
	((t_cyl *)(s->forme[i].ptr))->color.rgb[0] = s->obj->color.rgb[0];
	((t_cyl *)(s->forme[i].ptr))->color.rgb[1] = s->obj->color.rgb[1];
	((t_cyl *)(s->forme[i].ptr))->color.rgb[2] = s->obj->color.rgb[2];
	((t_cyl *)(s->forme[i].ptr))->index = i;
}
