/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:03:44 by grenaud-          #+#    #+#             */
/*   Updated: 2023/05/09 16:51:39 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

int	destroy_window(t_scene *p)
{
	printf(RED"You closed the window and ended miniRT\n"ENDC);
	free_and_exit(p);
	exit (0);
}

int	deal_key(int key_code, t_scene *p)
{
	escape(key_code, p);
	return (0);
}

int	escape(int key_code, t_scene *p)
{
	if (key_code == ESC)
		free_and_exit(p);
	return (0);
}

void	init_mlx(t_scene *p, char **argv)
{
	p->mlx_init.title = ft_strjoin("miniRT - ", argv[1]);
	p->mlx_init.mlx = mlx_init();
	// ajout 17/04
	if (p->mlx_init.mlx == NULL)
	{
		exit (0);
	}
	// fin ajout
	p->mlx_init.window = mlx_new_window(p->mlx_init.mlx, VIEWPORT_WIDTH,
			VIEWPORT_HEIGHT, p->mlx_init.title);
	// ajout 17/04
	if (p->mlx_init.window == NULL)
	{
		// free(p->mlx_new_window);
		exit (0);
	}
	// ? mlx_new_image...
	p->mlx_init.img.mlx_img = mlx_new_image(p->mlx_init.mlx, VIEWPORT_WIDTH, VIEWPORT_HEIGHT);
	p->mlx_init.img.addr = mlx_get_data_addr(p->mlx_init.img.mlx_img,
		&p->mlx_init.img.bpp, &p->mlx_init.img.line_len, &p->mlx_init.img.endian);
	// fin ajout

	 /* mlx_key_hook(p->mlx_init.window, deal_key, &p);
	mlx_hook(p->mlx_init.window, 17, 1L << 0, destroy_window, &p);
	mlx_hook(p->mlx_init.window, 17, 1L << 17, destroy_window, &p);
	mlx_loop(p->mlx_init.mlx); */
}

void	free_and_exit(t_scene *p)
{
	(void)	p;
	//mlx_clear_window(p->mlx_init.mlx, p->mlx_init.window);
	//mlx_destroy_window(p->mlx_init.mlx, p->mlx_init.window);
	wrdestroy();
	exit(0);
}
