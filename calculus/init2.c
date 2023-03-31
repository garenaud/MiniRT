/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:03:05 by jsollett          #+#    #+#             */
/*   Updated: 2023/03/30 16:03:16 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	init2_cylindre(t_cyl *Cyl, t_vector cam, double r, double h)
{
	t_vector	tmp;

	Cyl->r = r;
	Cyl->h = h;
//	tmp = add(Cyl->C0, scalar_prod(unit(Cyl->dir), Cyl->h));
	tmp = add(Cyl->C0, scalar_prod(Cyl->dir, Cyl->h / norm(Cyl->dir)));//correction ?
	init_vector(&Cyl->C1, tmp.vec[0], tmp.vec[1], tmp.vec[2]);
	tmp = sub(Cyl->C1, Cyl->C0);
	init_vector(&Cyl->vl, tmp.vec[0], tmp.vec[1], tmp.vec[2]);
	tmp = unit(Cyl->vl);
	init_vector(&Cyl->ul, tmp.vec[0], tmp.vec[1], tmp.vec[2]);
	tmp = sub(cam, Cyl->C0);
	init_vector(&Cyl->w1, tmp.vec[0], tmp.vec[1], tmp.vec[2]);
}
