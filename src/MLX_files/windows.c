/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:03:44 by grenaud-          #+#    #+#             */
/*   Updated: 2023/05/17 15:51:55 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

int	destroy_window(void)
{
	printf(RED"You closed the window and ended miniRT\n"ENDC);
	free_and_exit();
	exit (0);
}

int	deal_key(int key_code)
{
	escape(key_code);
	return (0);
}

int	escape(int key_code)
{
	if (key_code == ESC)
		destroy_window();
	return (0);
}

void	init_mlx(t_scene *p, char **argv)
{
	p->mlx_init.title = ft_strjoin("miniRT - ", argv[1]);
	p->mlx_init.mlx = mlx_init();
	if (p->mlx_init.mlx == NULL)
		exit (0);
	p->mlx_init.window = mlx_new_window(p->mlx_init.mlx, VIEWPORT_WIDTH,
			VIEWPORT_HEIGHT, p->mlx_init.title);
	if (p->mlx_init.window == NULL)
		exit (0);
	p->mlx_init.img.mlx_img = mlx_new_image(p->mlx_init.mlx,
			VIEWPORT_WIDTH, VIEWPORT_HEIGHT);
	p->mlx_init.img.addr = mlx_get_data_addr(p->mlx_init.img.mlx_img,
			&p->mlx_init.img.bpp, &p->mlx_init.img.line_len,
			&p->mlx_init.img.endian);
}

void	free_and_exit(void)
{
	wrdestroy();
	exit(0);
}
