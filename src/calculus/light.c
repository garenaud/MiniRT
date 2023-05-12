/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 10:15:19 by jsollett          #+#    #+#             */
/*   Updated: 2023/05/12 14:59:47 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

t_vector	*ambiant1(t_scene *p)
{// fonctionnerai mais trop lent ??? FAUX
	t_vector	*res;
	t_rgb		amb;

	//res = wrmalloc(sizeof(t_vector));
	res = malloc(sizeof(t_vector));// plus rapide
	if (res == NULL)
		exit(1);
	amb = p->a.color;
	init_vector(res, amb.rgb[0], amb.rgb[1], amb.rgb[2]);
	*res = scalar_prod(*res, p->a.lum / 255.0);
	return (res);

}

t_vector	ambiant2(t_scene *p)
{// fonctionnerai mais trop lent ??? FAUX
	t_vector	res;
	t_rgb		amb;

	//res = wrmalloc(sizeof(t_vector));
	amb = p->a.color;
	init_vector(&res, amb.rgb[0], amb.rgb[1], amb.rgb[2]);
	res = scalar_prod(res, p->a.lum / 255.0);
	return (res);

}
void	ambiant(t_scene *p)
{
	t_vector	ai;
	t_rgb		amb;

	amb = p->a.color;
	init_vector(&ai, amb.rgb[0]*p->a.lum/255.0, amb.rgb[1]*p->a.lum/255.0, amb.rgb[2]*p->a.lum/255.0);
	if (p->closest->type == 1)
	{
		((t_plan *)(p->forme[p->closest->index].ptr))->color.rgb[0] *= ai.vec[0];
		((t_plan *)(p->forme[p->closest->index].ptr))->color.rgb[1] *= ai.vec[1];
		((t_plan *)(p->forme[p->closest->index].ptr))->color.rgb[2] *= ai.vec[2];
	}
	if (p->closest->type == 2)
	{

	}
	if (p->closest->type == 3)
	{

	}
}

// doit detecter si le faisceau de lumiere peut atteindre l'intersection
int	free_path(t_scene *p)
{
	double	min_dist;
	int		obj;

	t_vector	intersect;
	if (p->closest->type == 1)
		intersect = (((t_plan *)(p->forme[p->closest->index].ptr))->intersect0);
	if (p->closest->type == 2)
		intersect = (((t_sphere *)(p->forme[p->closest->index].ptr))->intersect0);
	if (p->closest->type == 3 && ((t_cyl *)(p->forme[p->closest->index].ptr))->inside == 0)
		intersect = (((t_cyl *)(p->forme[p->closest->index].ptr))->intersect0);
	if (p->closest->type == 3 && ((t_cyl *)(p->forme[p->closest->index].ptr))->inside == 1)
		intersect = (((t_cyl *)(p->forme[p->closest->index].ptr))->intersect1);
	if (p->closest->type == 3 && ((t_cyl *)(p->forme[p->closest->index].ptr))->inside == 2)
	{// a verifier
		printf("Cyl !\n");
	}
	min_dist = 0;
	obj = 0;
	init_closest(p->l.cl);
	while (obj < p->n_obj && obj != p->l.cl->index)
	{
		if (p->forme[obj].id == 3)
			closest_cylindre1(p, &intersect, obj);
		if (p->forme[obj].id == 2)
			closest_sphere1(p, &intersect, obj);
		if (p->forme[obj].id == 1)
			closest_plan1(p, &intersect, obj);
		obj++;
	}
	return (p->l.cl->index);
}

