/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 10:15:19 by jsollett          #+#    #+#             */
/*   Updated: 2023/05/16 16:44:07 by jsollett         ###   ########.fr       */
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

void	saturation(t_scene *p)
{
	int		i;
	int		j;

	j = 0;
	while (j <= VIEWPORT_HEIGHT - 1)
	{
		i = 0;
		while (i < VIEWPORT_WIDTH)
		{
			if (p->c.film[i][j].rgb[0] > 255)
				p->c.film[i][j].rgb[0] = 255;
			if (p->c.film[i][j].rgb[1] > 255)
				p->c.film[i][j].rgb[1] = 255;
			if (p->c.film[i][j].rgb[2] > 255)
				p->c.film[i][j].rgb[2] = 255;
			i++;
		}
		j++;
	}
}

void	saturation_pixel(t_scene *p, int i, int j)
{
	if (p->c.film[i][j].rgb[0] > 255)
		p->c.film[i][j].rgb[0] = 255;
	if (p->c.film[i][j].rgb[1] > 255)
		p->c.film[i][j].rgb[1] = 255;
	if (p->c.film[i][j].rgb[2] > 255)
		p->c.film[i][j].rgb[2] = 255;
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

