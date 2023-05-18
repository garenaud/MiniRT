/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:03:05 by jsollett          #+#    #+#             */
/*   Updated: 2023/05/18 10:58:07 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	init2_cylindre(t_cyl *Cyl, t_vector cam, double r, double h)
{
	t_vector	tmp;

	Cyl->r = r;
	Cyl->h = h;
	tmp = add(Cyl->c0, scalar_prod(Cyl->dir, Cyl->h / norm(Cyl->dir)));
	init_vector(&Cyl->c1, tmp.vec[0], tmp.vec[1], tmp.vec[2]);
	tmp = sub(Cyl->c1, Cyl->c0);
	init_vector(&Cyl->vl, tmp.vec[0], tmp.vec[1], tmp.vec[2]);
	tmp = unit(Cyl->vl);
	init_vector(&Cyl->ul, tmp.vec[0], tmp.vec[1], tmp.vec[2]);
	tmp = sub(cam, Cyl->c0);
	init_vector(&Cyl->w1, tmp.vec[0], tmp.vec[1], tmp.vec[2]);
}

void	init_closest(t_closest *close)
{
	close->index = -1;
	close->type = -1;
	close->tmin = POS_INF;
	close->dmin = POS_INF;
	close->delta = POS_INF;
	close->min_dist = 0;
	close->obj = 0;
}

void	background(t_rgb **rgb, t_color color, int i, int j)
{
	rgb[i][j].rgb[0] = color.r;
	rgb[i][j].rgb[1] = color.g;
	rgb[i][j].rgb[2] = color.b;
}
