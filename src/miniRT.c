/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:04:14 by grenaud-          #+#    #+#             */
/*   Updated: 2023/05/17 10:52:42 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	init_check(t_scene *p, char **argv)
{
	int		fd;

	fd = open(argv[1], O_RDONLY);
	check_fd(fd, argv);
	p->check.fd_lines = ft_count_lines(fd);
	p->l.color.rgb[0] = 255;
	p->l.color.rgb[1] = 255;
	p->l.color.rgb[2] = 255;
	p->bg.r = 0;
	p->bg.g = 0;
	p->bg.b = 0;
	p->obj = NULL;
	p->delta = create_discriminant();
	p->l.discr = create_discriminant();
	p->l.cyl = create_cy();
	p->l.cyl->discr = create_discriminant();
	p->closest = create_closest();
	p->l.cl = create_closest();
	close(fd);
}

void	axe(t_scene *p, int i, int j)
{
		p->c.film[i][j].rgb[0] = 255;
		p->c.film[i][j].rgb[1] = 0;
		p->c.film[i][j].rgb[2] = 255;
}

void	mlx_key(t_scene *p)
{
	mlx_key_hook(p->mlx_init.window, deal_key, &p);
	mlx_hook(p->mlx_init.window, 17, 1L << 0, destroy_window, &p);
	mlx_hook(p->mlx_init.window, 17, 1L << 17, destroy_window, &p);
	mlx_loop(p->mlx_init.mlx);
}

void	ray_tracer(t_scene *p)
{
	int		i;
	int		j;

	j = VIEWPORT_HEIGHT - 1;
	get_duration();
	while (j >= 0)
	{
		i = 0;
		while (i < VIEWPORT_WIDTH)
		{
			fire_ray(p, i, j);
			++i;
		}
		--j;
		screen_info_processing(p);
	}
	printf(BLUE"\nDuration   :   %.2fs\n"ENDC, get_duration());
}

void	fire_ray(t_scene *p, int i, int j)
{
	init_closest(p->closest);
	create_ray(p, i, j);
	while (p->closest->obj < p->n_obj)
	{
		if (p->forme[p->closest->obj].id == 3)
			closest_cylindre(p, p->closest->obj);
		if (p->forme[p->closest->obj].id == 2)
			closest_sphere(p, p->closest->obj);
		if (p->forme[p->closest->obj].id == 1)
			closest_plan(p, p->closest->obj);
		p->closest->obj++;
	}
	put_cylindre(p, i, j);
	put_sphere(p, i, j);
	put_plan(p, i, j);
}

int		main(int argc, char **argv)
{
	t_scene	*p;

	(void) argc;
	p = wrmalloc(sizeof(t_scene));
	p = &(t_scene){0};

	init_check(p, argv);
	parsing(p, argv);
	ray_tracer(p);
	init_mlx(p, argv);
	mlx_key_hook(p->mlx_init.window, deal_key, p);

	render(p);
	mlx_key(p);
	wrdestroy();
	return (0);
}
