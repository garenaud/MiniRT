/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:03:44 by grenaud-          #+#    #+#             */
/*   Updated: 2023/04/11 13:27:12 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

int	destroy_window(t_scene *p)
{
	printf(BOLDRED"You closed the window and ended miniRT\n"ENDC);
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
	p->mlx_init.window = mlx_new_window(p->mlx_init.mlx, CANVAS_X,
			CANVAS_Y, p->mlx_init.title);
/* 	mlx_key_hook(p->mlx_init.window, deal_key, &p);
	mlx_hook(p->mlx_init.window, 17, 1L << 0, destroy_window, &p);
	mlx_hook(p->mlx_init.window, 17, 1L << 17, destroy_window, &p);
	mlx_loop(p->mlx_init.mlx); */
}

void	free_and_exit(t_scene *p)
{
	mlx_clear_window(p->mlx_init.mlx, p->mlx_init.window);
	mlx_destroy_window(p->mlx_init.mlx, p->mlx_init.window);
	wrdestroy();
	exit(0);
}
