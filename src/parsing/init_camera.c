/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 13:58:08 by jsollett          #+#    #+#             */
/*   Updated: 2023/04/14 15:20:44 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

//p->c.w1 = scalar_prod(sub(p->c.pos, p->c.vp_middle), 1 / norm(sub(p->c.pos, p->c.vp_middle)));
void	init_camera(t_scene *p)
{
	init_vector(&p->c.vup, 0, 1, 0);
	p->c.vp_middle = add(p->c.pos, p->c.dir);
	p->c.w1 = unit(sub(p->c.pos, p->c.vp_middle));
	p->c.u = cross(p->c.w1, p->c.vup);
	p->c.v = cross(p->c.u, p->c.w1);
	p->c.hor = 2 * tan(p->c.fov * PI / 360.0);
	p->c.ver = p->c.hor;
	p->c.ll = sub(sub(p->c.vp_middle, scalar_prod(p->c.u, p->c.hor/2)), scalar_prod(p->c.v, p->c.ver/2));
}

void	create_ray(t_scene *p, int i, int j)
{
	t_vector	aa;
	t_vector	bb;

	aa = scalar_prod(p->c.u, p->c.hor * (double)(i) / (VIEWPORT_WIDTH - 1));
	bb = scalar_prod(p->c.v, p->c.ver * (double)(j) / (VIEWPORT_HEIGHT - 1));
	init_ray(&p->ray, p->c.pos, sub(add(p->c.ll, add(aa, bb)), p->c.pos));
}
