/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:46:07 by jsollett          #+#    #+#             */
/*   Updated: 2023/05/18 09:39:58 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	axe(t_scene *p, int i, int j)
{
		p->c.film[i][j].rgb[0] = 255;
		p->c.film[i][j].rgb[1] = 0;
		p->c.film[i][j].rgb[2] = 255;
}

void	img_pix_put(t_mlx *d, int x, int y, t_rgb rgb)
{
	char	*pixel;
	int		i;
	int		color;

	color = rgb_to_int(rgb);
	i = d->img.bpp - 8;
	pixel = d->img.addr + ((y) * d->img.line_len + x * (d->img.bpp / 8));
	while (i >= 0)
	{
		if (d->img.endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (d->img.bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

void	render(t_scene *p)
{
	int		i;
	int		j;
	t_rgb	pixel;

	j = 0;
	while (j <= VIEWPORT_HEIGHT - 1)
	{
		i = 0;
		while (i < VIEWPORT_WIDTH)
		{
			pixel = p->c.film[i][VIEWPORT_HEIGHT - 1 - j];
			img_pix_put(&p->mlx_init, i, j, pixel);
			i++;
		}
		j++;
	}
	mlx_put_image_to_window(p->mlx_init.mlx, p->mlx_init.window,
		p->mlx_init.img.mlx_img, 0, 0);
}
