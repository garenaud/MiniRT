/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 10:15:19 by jsollett          #+#    #+#             */
/*   Updated: 2023/05/03 15:57:50 by jsollett         ###   ########.fr       */
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
int	free_path(t_scene *p, int i, int j)
{
	double	min_dist;
	int		obj;
	t_vector	tmp, tmp1;

	t_vector	intersect;
	//t_vector	l_dir;
	if (p->closest->type == 1)
	{
		intersect = (((t_plan *)(p->forme[p->closest->index].ptr))->intersect0);
	}
	if (p->closest->type == 2)
	{
		intersect = (((t_sphere *)(p->forme[p->closest->index].ptr))->intersect0);
	}
	if (p->closest->type == 3 && ((t_cyl *)(p->forme[p->closest->index].ptr))->inside == 0)
	{// a verifier
		intersect = (((t_cyl *)(p->forme[p->closest->index].ptr))->intersect0);
	}
	if (p->closest->type == 3 && ((t_cyl *)(p->forme[p->closest->index].ptr))->inside == 1)
	{// a verifier
		intersect = (((t_cyl *)(p->forme[p->closest->index].ptr))->intersect1);
	}
	if (p->closest->type == 3 && ((t_cyl *)(p->forme[p->closest->index].ptr))->inside == 2)
	{// a verifier
		printf("Cyl !\n");
	}
	//printf(RED"type = %d\n"ENDC, p->closest->type);

	/*l->ray.dir = unit(sub(intersect, l->c.pos));
	l->ray.orig = p->l.pos;*/
	min_dist = 0;
	obj = 0;
	//create_ray(p, i, j);
	init_closest(p->l.cl);
	while (obj < p->n_obj && obj != p->l.cl->index)
	{
		if (p->forme[obj].id == 3)
			closest_cylindre1(p, &intersect, obj);
		if (p->forme[obj].id == 2)
			closest_sphere1(p, &intersect, obj);
		if (p->forme[obj].id == 1)
		{

			closest_plan1(p, &intersect, obj);
		}
		obj++;
	}
	if (i == 550 && j == 850)
	{
	//printf("j = %d, l.dir =  %lf,%lf,%lf\n", j,p->l.dir.vec[0], p->l.dir.vec[1],p->l.dir.vec[2]);
	tmp1 = sub(p->l.pos, p->l.li);
	//printf("j = %d, ratio l.dir/sub( , lposl.li) =  %lf,%lf,%lf\n", j,p->l.dir.vec[0]/tmp1.vec[0], p->l.dir.vec[1]/tmp1.vec[1],p->l.dir.vec[2]/tmp1.vec[2]);
	//printf("index (%d) = %d\t impact = %lf,%lf,%lf", j,p->l.cl->index ,p->l.li.vec[0], p->l.li.vec[1],p->l.li.vec[2]);
	tmp =cross(sub(p->l.li, p->l.pos), p->l.dir);
/*	if (egal(norm(tmp), 0, EPS))
		printf(GREEN"freepath OK\n"ENDC);
	else
		printf(RED"freepath KO\n"ENDC);*/
//	printf("index freepath = %d\n",p->l.cl->index );
//	printf("index type = %d\n",p->l.cl->type );
	}
	//printv(&tmp);
	return (p->l.cl->index);
}

