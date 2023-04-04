/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:04:14 by grenaud-          #+#    #+#             */
/*   Updated: 2023/04/04 11:48:53 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	free_struct(t_scene *p)
{
	printf("p->a.lum = %f\n", p->a.lum);
	free(&p->a.lum);
 	free(&p->a.color.rgb[0]);
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
	free(&p->l.color); 
	//delete_obj(&p->obj);
}

void	init_check(t_scene *p, char **argv)
{
	int		fd;

	fd = open(argv[1], O_RDONLY);
	check_fd(fd, argv);
	p->check.fd_lines = ft_count_lines(fd);
	p->check.comm = 0;
	p->a.check_a = 0;
	p->l.check_l = 0;
	p->c.check_c = 0;
	close(fd);
}

int		main(int argc, char **argv)
{
	t_scene	p;
	(void) argc;

	init_check(&p, argv);
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
	(void) argv;
	int		fd;
	//int		len;
	char	*line;
//	char	*test;
//	int i = 0;
	int j = 0;

	fd = open(argv[1], O_RDONLY);
	//i = ft_count_lines(fd);
	//printf("i = %d\n", i);
//	printf("test = %s\n", test);
	while (j < 5)
	{
		line = get_next_line(fd);
		printf("line = [%s]\n", line);
		if (!line)
			printf("line est vide\n");
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
}
 */