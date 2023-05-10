/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:46:07 by jsollett          #+#    #+#             */
/*   Updated: 2023/05/09 13:35:28 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"
// adapte de fractol, ET de AURELEIN BRABANT...

// A VERIFIER, senble ok, mod l25 ajout de viewportheight-y a la place de y
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

// A VERIFIER, semble ok compile, inversion y et j
void	render(t_scene *p)
{
	int		i;
	int		j;
//	int		color;
	t_rgb	pixel;

	//j = VIEWPORT_HEIGHT - 1;
	j = 0;
	while (j <= VIEWPORT_HEIGHT - 1)
	//while (j >= 0)
	{
		i = 0;
		while (i < VIEWPORT_WIDTH)
		{// a modifier
			//pixel = *p->c.film[j * VIEWPORT_WIDTH + i];
			pixel = p->c.film[i][VIEWPORT_HEIGHT - 1 - j];
			img_pix_put(&p->mlx_init, i, j, pixel);//i++
			//img_pix_put(d, i++, j, *(d->f.color + color));
            i++;
		}
		j++;
		//screen_info_processing(p);
		//j--;
	}
	mlx_put_image_to_window(p->mlx_init.mlx, p->mlx_init.window, p->mlx_init.img.mlx_img,
		0, 0);
}
