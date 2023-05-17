/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 10:15:19 by jsollett          #+#    #+#             */
/*   Updated: 2023/05/17 14:06:10 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

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

t_vector	*get_intersect_fp(t_scene *p)
{
	if (p->closest->type == 1)
		return (&(((t_plan *)(p->forme[p->closest->index].ptr))->intersect0));
	if (p->closest->type == 2)
		return (&(((t_sphere *)(p->forme[p->closest->index].ptr))->intersect0));
	if (p->closest->type == 3 && ((t_cyl *)
			(p->forme[p->closest->index].ptr))->inside == 0)
		return (&(((t_cyl *)(p->forme[p->closest->index].ptr))->intersect0));
	if (p->closest->type == 3 && ((t_cyl *)
			(p->forme[p->closest->index].ptr))->inside == 1)
		return (&(((t_cyl *)(p->forme[p->closest->index].ptr))->intersect1));
	return (NULL);
}

int	free_path(t_scene *p)
{
	t_vector	intersect;

	intersect = *get_intersect_fp(p);
	init_closest(p->l.cl);
	while (p->l.cl->obj < p->n_obj && p->l.cl->obj != p->l.cl->index)
	{
		if (p->forme[p->l.cl->obj].id == 3)
			closest_cylindre1(p, &intersect, p->l.cl->obj);
		if (p->forme[p->l.cl->obj].id == 2)
			closest_sphere1(p, &intersect, p->l.cl->obj);
		if (p->forme[p->l.cl->obj].id == 1)
			closest_plan1(p, &intersect, p->l.cl->obj);
		p->l.cl->obj++;
	}
	return (p->l.cl->index);
}
