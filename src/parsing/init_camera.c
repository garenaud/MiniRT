/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 13:58:08 by jsollett          #+#    #+#             */
/*   Updated: 2023/05/18 10:25:18 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	init_camera(t_scene *p)
{
	init_vector(&p->c.vup, 0, 1, 0);
	if (egal(norm(sub(p->c.vup, p->c.dir)), 0, EPS))
		init_vector(&p->c.vup, 0, 0, -1);
	if (egal(norm(sub(reverse(p->c.vup), p->c.dir)), 0, EPS))
		init_vector(&p->c.vup, 0, 0, 1);
	p->c.vp_middle = add(p->c.pos, p->c.dir);
	p->c.w1 = unit(sub(p->c.pos, p->c.vp_middle));
	p->c.u = unit(cross(p->c.w1, p->c.vup));
	p->c.v = unit(cross(p->c.u, p->c.w1));
	p->c.hor = 2 * tan(p->c.fov * PI / 360.0);
	p->c.ver = p->c.hor;
	p->c.ll = sub(sub(p->c.vp_middle, scalar_prod(p->c.u, p->c.hor / 2)),
			scalar_prod(p->c.v, p->c.ver / 2));
	init_film(p, p->bg);
}

void	create_ray(t_scene *p, int i, int j)
{
	t_vector	aa;
	t_vector	bb;

	aa = scalar_prod(p->c.u, p->c.hor * (double)(i) / (VIEWPORT_WIDTH - 1));
	bb = scalar_prod(p->c.v, p->c.ver * (double)(j) / (VIEWPORT_HEIGHT - 1));
	init_ray(&p->ray, p->c.pos, sub(add(p->c.ll, add(aa, bb)), p->c.pos));
}

void	init_film(t_scene *p, t_color back)
{
	int	i;
	int	j;

	p->c.film = create_2d_rgb(VIEWPORT_WIDTH, VIEWPORT_HEIGHT);
	j = VIEWPORT_HEIGHT - 1;
	while (j >= 0)
	{
		i = 0;
		while (i < VIEWPORT_WIDTH)
		{
			background(p->c.film, back, i, j);
			++i;
		}
		j--;
	}
}

int	rgb_to_int(t_rgb rgb)
{
	return (rgb.rgb[0] << 16 | rgb.rgb[1] << 8 | rgb.rgb[2]);
}
