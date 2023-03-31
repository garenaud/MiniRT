/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:04:14 by grenaud-          #+#    #+#             */
/*   Updated: 2023/03/31 19:50:55 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	free_struct(t_scene *p)
{
	//free(&p->a.lum);
/* 	free(&p->a.color.rgb[0]);
	free(&p->a.color.rgb[1]);
	free(&p->a.color.rgb[2]);
	free(&p->c.pos.vec[0]);
	free(&p->c.pos.vec[1]);
	free(&p->c.pos.vec[2]);
	free(&p->c.dir.vec[0]);
	free(&p->c.dir.vec[1]);
	free(&p->c.dir.vec[2]);
	free(&p->c.fov);
	free(&p->l.pos.vec[0]);
	free(&p->l.pos.vec[1]);
	free(&p->l.pos.vec[2]);
	free(&p->l.color.rgb[0]);
	free(&p->l.color.rgb[1]);
	free(&p->l.color.rgb[2]);
	free(&p->l.lum);
	free(&p->l.color); */
	delete_obj(&p->obj);
}

int		main(int argc, char **argv)
{
	t_scene	p;
	(void) argc;

	parsing(&p, argv);
	printf(GREEN"\n\np->a.lum = %f, p->a.color.rgb[0] = %d, p->a.color.rgb[1] = %d, p->a.color.rgb[2] = %d\n"ENDC, p.a.lum, p.a.color.rgb[0], p.a.color.rgb[1], p.a.color.rgb[2]);
	printf(BLUE"\np->c.vec[0] = %f, p->c.vec[1] = %f, p->c.vec[2] = %f, p->c.dir.vec[0] = %f, p->c.dir.vec[1] = %f, p->c.dir.vec[2] = %f, p->c.fov = %f \n"ENDC, p.c.pos.vec[0], p.c.pos.vec[1], p.c.pos.vec[2], p.c.dir.vec[0], p.c.dir.vec[1], p.c.dir.vec[2], p.c.fov);
	printf(YEL"\np->l.pos.vec[0] = %f, p->l.pos.vec[1] = %f, p->l.pos.vec[2] = %f, p->l.lum = %f, p->l.color.rgb[0] = %d, p->l.color.rgb[1] = %d, p->l.color.rgb[2] = %d \n"ENDC, p.l.pos.vec[0], p.l.pos.vec[1], p.l.pos.vec[2], p.l.lum, p.l.color.rgb[0], p.l.color.rgb[1], p.l.color.rgb[2]);
	printll_obj(p.obj);
	printf("adresse de p->obj = %p size = %zu\n", p.obj, size_stack_obj(p.obj));
	printf("adresse de p->a.lum = %p\n", &p.c.pos);
	//free_struct(&p);
	//delete_obj(&p.obj);
	//free(&p.c.fov);
	return (0);
}

/* int		main(int argc, char **argv)
{
	//t_scene	p;
	(void) argc;
	int		fd;
	//int		len;
	char	*line;
	//char	*test;
	int i = 0;
	int j = 0;

	fd = open(argv[1], O_RDONLY);
	i = ft_count_lines(fd);
	printf("i = %d\n", i);
	while (fd)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		//printf("line au debut = [%s]\n", line);
		//line = trim_line(line);
		//len = strlen_comm(&p, line);
		//printf("line apres = [%s] et strlen = %zu longueur malloc = %d\n", line, ft_strlen(line), len);
		//line = clean_comm(&p, line);
		//printf("line apres clean comm = [%s]\n", line);
		//free(line);
		j++;
	}
	//free_struct(&p);
	//delete_obj(&p.obj);
	//free(&p.c.fov);
	return (0);
} */
