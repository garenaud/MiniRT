/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:04:14 by grenaud-          #+#    #+#             */
/*   Updated: 2023/04/14 14:49:47 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	init_check(t_scene *p, char **argv)
{
	int		fd;

	fd = open(argv[1], O_RDONLY);
	check_fd(fd, argv);
	p->check.fd_lines = ft_count_lines(fd);
/*	p->check.comm = 0;
	p->a.check_a = 0;
	p->l.check_l = 0;
	p->c.check_c = 0;*/
    //p->pl.index = 0;
	p->l.color.rgb[0] = 255;
	p->l.color.rgb[1] = 255;
	p->l.color.rgb[2] = 255;
    p->obj = NULL;
	close(fd);
}

void	mlx_key(t_scene *p)
{
	mlx_key_hook(p->mlx_init.window, deal_key, &p);
	mlx_hook(p->mlx_init.window, 17, 1L << 0, destroy_window, &p);
	mlx_hook(p->mlx_init.window, 17, 1L << 17, destroy_window, &p);
	mlx_loop(p->mlx_init.mlx);
}

t_objet	*transfer(t_scene *s)
{
	int		size;
	t_objet	*objet;
	t_plan	*plan;
	int		i;

	i = 0;
	size = size_stack_obj(s->obj);
	objet = (t_objet *)wrmalloc(size * sizeof(t_objet));
	plan = (t_plan *)wrmalloc(size * sizeof(t_plan));
	while (s->obj)
	{
		if (s->obj->id == 1)
		{
			objet[i].id = 1;
			objet[i].ptr = &plan[i];
			init_vector(&plan[i].C, s->obj->pos.vec[0], s->obj->pos.vec[1], s->obj->pos.vec[2]);
			init_vector(&plan[i].n, s->obj->dir.vec[0], s->obj->dir.vec[1], s->obj->dir.vec[2]);
			init_plan(&plan[i], plan[i].C, unit(plan[i].n));
			plan[i].OC = sub(plan[i].C, s->c.pos);//cam pos de la camera...
				//p->OC = sub(p0, cam); // a tester
				//p->OCn = dot(p->OC, p->n); // a tester
			plan[i].OCn = dot(plan[i].OC, plan[i].n);
			plan[i].index = i;
		}
		if (s->obj->id == 2)
		{
		}
		if (s->obj->id == 3)
		{
		}
		s->obj = s->obj->next;
	}
	return (objet);
}

int		main(int argc, char **argv)
{
	t_scene	*p;
	(void) argc;
    p = wrmalloc(sizeof(t_scene));
	int			debug = 1;

	p = &(t_scene){0};

	parsing(p, argv);

	if (debug)
	{
		printf(GREEN"\n\np->a.lum = %f, p->a.color.rgb[0] = %d, p->a.color.rgb[1] = %d, p->a.color.rgb[2] = %d\n"ENDC, p->a.lum, p->a.color.rgb[0], p->a.color.rgb[1], p->a.color.rgb[2]);
		printf(BLUE"\np->c.vec[0] = %f, p->c.vec[1] = %f, p->c.vec[2] = %f, p->c.dir.vec[0] = %f, p->c.dir.vec[1] = %f, p->c.dir.vec[2] = %f, p->c.fov = %f \n"ENDC, p->c.pos.vec[0], p->c.pos.vec[1], p->c.pos.vec[2], p->c.dir.vec[0], p->c.dir.vec[1], p->c.dir.vec[2], p->c.fov);
        printf("\nvup\t\t");printv(&p->c.vup);
        printf("\nvp_middle\t");printv(&p->c.vp_middle);
        printf("\nvup\t\t");printv(&p->c.vup);
        printf("\nU\t\t");printv(&p->c.u);
        printf("\nV\t\t");printv(&p->c.v);
        printf("\nhor = %f ver = %f", p->c.hor, p->c.ver);
		printf(YEL"\np->l.pos.vec[0] = %f, p->l.pos.vec[1] = %f, p->l.pos.vec[2] = %f, p->l.lum = %f, p->l.color.rgb[0] = %d, p->l.color.rgb[1] = %d, p->l.color.rgb[2] = %d \n"ENDC, p->l.pos.vec[0], p->l.pos.vec[1], p->l.pos.vec[2], p->l.lum, p->l.color.rgb[0], p->l.color.rgb[1], p->l.color.rgb[2]);
		printll_obj(p->obj);
	}
    printll_obj(p->obj);
	init_mlx(p, argv);
	//mlx_key(&p);
 	mlx_key_hook(p->mlx_init.window, deal_key, p);
	mlx_hook(p->mlx_init.window, 17, 1L << 0, destroy_window, p);
	mlx_hook(p->mlx_init.window, 17, 1L << 17, destroy_window, p);
	mlx_loop(p->mlx_init.mlx);

	wrdestroy();
	return (0);
}
