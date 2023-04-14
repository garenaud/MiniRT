/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 09:50:19 by grenaud-          #+#    #+#             */
/*   Updated: 2023/04/14 12:03:14 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	init_obj(t_scene *p, char *line, int index)
{
	if (line[0] == 's' && line[1] == 'p')
		push_sp(p, index);
	if (line[0] == 'p' && line[1] == 'l')
		push_pl(p, index);
	if (line[0] == 'c' && line[1] == 'y')
		push_cy(p, index);
}

t_plan	*create_plan()
{
	t_plan	*plan;

	plan = wrmalloc(sizeof(t_plan));
	if (plan == NULL)
		wrdestroy();
	return (plan);
}

t_sphere	*create_sp()
{
	t_sphere	*sphere;

	sphere = wrmalloc(sizeof(t_sphere));
	if (sphere == NULL)
		wrdestroy();
	return (sphere);
}

t_cyl	*create_cy()
{
	t_cyl	*cyl;

	cyl = wrmalloc(sizeof(t_cyl));
	if (cyl == NULL)
		wrdestroy();
	return (cyl);
}

void	create_array(t_scene *s)
{
	int			i;
	t_listobj	*start;

	start = s->obj;
	i = 0;

	while (s->obj)
	{
		if (s->obj->id == 1)
		{
			s->forme[i].ptr = create_plan(); // renvoi address plan
			s->forme[i].id = 1;
			init_vector(&((t_plan *)(s->forme[i].ptr))->C, s->obj->pos.vec[0], s->obj->pos.vec[1], s->obj->pos.vec[2]);
			init_vector(&((t_plan *)(s->forme[i].ptr))->n, s->obj->dir.vec[0], s->obj->dir.vec[1], s->obj->dir.vec[2]);
			init_plan(((t_plan *)(s->forme[i].ptr)), ((t_plan *)(s->forme[i].ptr))->C, unit(((t_plan *)(s->forme[i].ptr))->n));
			((t_plan *)(s->forme[i].ptr))->OC = sub(((t_plan *)(s->forme[i].ptr))->C, s->c.pos);
			((t_plan *)(s->forme[i].ptr))->OCn = dot(((t_plan *)(s->forme[i].ptr))->OC, ((t_plan *)(s->forme[i].ptr))->n);
			((t_plan *)(s->forme[i].ptr))->color.rgb[0] = s->obj->color.rgb[0];
			((t_plan *)(s->forme[i].ptr))->color.rgb[1] = s->obj->color.rgb[1];
			((t_plan *)(s->forme[i].ptr))->color.rgb[2] = s->obj->color.rgb[2];
			((t_plan *)(s->forme[i].ptr))->index = i;
		}
		if (s->obj->id == 2)
		{
			s->forme[i].ptr = create_sp();
			s->forme[i].id = 2;
			init_vector(&((t_sphere *)(s->forme[i].ptr))->C, s->obj->pos.vec[0], s->obj->pos.vec[1], s->obj->pos.vec[2]);
			init_sphere(((t_sphere *)(s->forme[i].ptr)), ((t_sphere *)(s->forme[i].ptr))->C, s->obj->r);
			((t_sphere *)(s->forme[i].ptr))->OC = sub(s->c.pos,((t_sphere *)(s->forme[i].ptr))->C);// a verifier
			((t_sphere *)(s->forme[i].ptr))->discr_c = norm_2(((t_sphere *)(s->forme[i].ptr))->OC) - ((t_sphere *)(s->forme[i].ptr))->r2;
			((t_sphere *)(s->forme[i].ptr))->color.rgb[0] = s->obj->color.rgb[0];
			((t_sphere *)(s->forme[i].ptr))->color.rgb[1] = s->obj->color.rgb[1];
			((t_sphere *)(s->forme[i].ptr))->color.rgb[2] = s->obj->color.rgb[2];
			((t_sphere *)(s->forme[i].ptr))->index = i;
		}
		if (s->obj->id == 3)
		{
			s->forme[i].ptr = create_cy();
			s->forme[i].id = 3;
			init_vector(&((t_cyl *)(s->forme[i].ptr))->C0, s->obj->pos.vec[0], s->obj->pos.vec[1], s->obj->pos.vec[2]);
			init_vector(&((t_cyl *)(s->forme[i].ptr))->dir, s->obj->dir.vec[0], s->obj->dir.vec[1], s->obj->dir.vec[2]);
			printv(&((t_cyl *)(s->forme[i].ptr))->C0);
			printv(&((t_cyl *)(s->forme[i].ptr))->dir);
			init_cylindre(((t_cyl *)(s->forme[i].ptr)), ((t_cyl *)(s->forme[i].ptr))->C0,
				((t_cyl *)(s->forme[i].ptr))->dir, sub(((t_cyl *)(s->forme[i].ptr))->C0, s->c.pos));
			printv(&((t_cyl *)(s->forme[i].ptr))->C0);
			printv(&((t_cyl *)(s->forme[i].ptr))->dir);// faux ligne suivante_
			init2_cylindre(((t_cyl *)(s->forme[i].ptr)),s->c.pos, s->obj->r, s->obj->h);//r h
				printf(GREEN);
			printv(&((t_cyl *)(s->forme[i].ptr))->C0);
			printv(&((t_cyl *)(s->forme[i].ptr))->dir);
			printf(ENDC);
			((t_cyl *)(s->forme[i].ptr))->color.rgb[0] = s->obj->color.rgb[0];
			((t_cyl *)(s->forme[i].ptr))->color.rgb[1] = s->obj->color.rgb[1];
			((t_cyl *)(s->forme[i].ptr))->color.rgb[2] = s->obj->color.rgb[2];
			((t_cyl *)(s->forme[i].ptr))->index = i;

		}
		s->obj = s->obj->next;
		i++;
	}
	s->obj = start;
}

void	print_array(t_scene *p, t_objet *array)
{
	int	i;

	i = 0;
	while (i <= size_stack_obj(p->obj))
	{
		if (array[i].id == 1)
		{
			printf(GREEN"\nplan N%d\n"ENDC, ((t_plan *)array[i].ptr)->index);
			printf("position:\t\t");
			printv(&((t_plan *)array[i].ptr)->C);
			printf("direction:\t\t");
			printv(&((t_plan *)array[i].ptr)->n);
			printf("vecteur cam->position:\t");
			printv(&((t_plan *)array[i].ptr)->OC);
			printf("couleur RGB:\t\t R[%d] G[%d] B[%d]\n", ((t_plan *)array[i].ptr)->color.rgb[0], ((t_plan *)array[i].ptr)->color.rgb[1], ((t_plan *)array[i].ptr)->color.rgb[2]);
		}
		if (array[i].id == 2)
		{
			printf(GREEN"\nsphere N%d\n"ENDC, ((t_sphere *)array[i].ptr)->index);
			printf("position:\t\t");
			printv(&((t_sphere *)array[i].ptr)->C);
			printf("vecteur cam->position:\t");
			printv(&((t_sphere *)array[i].ptr)->OC);
			printf("\nrayon:\t%f\n", ((t_sphere *)array[i].ptr)->r);
			printf("couleur RGB:\t\t R[%d] G[%d] B[%d]\n", ((t_sphere *)array[i].ptr)->color.rgb[0], ((t_sphere *)array[i].ptr)->color.rgb[1], ((t_sphere *)array[i].ptr)->color.rgb[2]);
		}
		if (array[i].id == 3)
		{
			printf(GREEN"\nCylindre N%d\n"ENDC, ((t_cyl *)array[i].ptr)->index);
			printf("position C0:\t\t");
			printv(&((t_cyl *)array[i].ptr)->C0);
			printf("position C1:\t\t");
			printv(&((t_cyl *)array[i].ptr)->C1);
			printf("direction:\t\t");
			printv(&((t_cyl *)array[i].ptr)->dir);
			printf("vecteur cam->position:\t");
			printv(&((t_cyl *)array[i].ptr)->OC);
			printf("couleur RGB:\t\t R[%d] G[%d] B[%d]\n", ((t_cyl *)array[i].ptr)->color.rgb[0], ((t_cyl *)array[i].ptr)->color.rgb[1], ((t_cyl *)array[i].ptr)->color.rgb[2]);
		}
		i++;
	}
}

void	parsing(t_scene *p, char **argv)
{
	int			fd;
	int			i;

    init_check(p, argv);
	fd = open(argv[1], O_RDONLY);
	i = 1;
	while (i++ <= p->check.fd_lines)
		read_fd(p, fd, i);
	check_struct(p);
	p->forme = wrmalloc(size_stack_obj(p->obj) * sizeof(t_objet));
	if (p->forme == NULL)
		wrdestroy();
	create_array(p);
	print_array(p, p->forme);
	close(fd);
}

void	read_fd(t_scene *p, int fd, int i)
{
	p->line = get_next_line(fd);
	if (is_empty(p->line) == 0 && p->line != NULL)
		p->line = clean_comm(p, p->line);
	if (is_empty(p->line) == 0 && p->line != NULL)
	{
		p->line = trim_line(p->line);
		if (p->line[0] == 'A')
			init_ambiant(p, i - 1);
		else if (p->line[0] == 'C')
			init_cam(p, i - 1);
		else if (p->line[0] == 'L')
			init_light(p, i - 1);
		else if (p->line[0] == 'p' && p->line[1] == 'l')
			init_obj(p, p->line, i - 1);
		else if (p->line[0] == 'c' && p->line[1] == 'y')
			init_obj(p, p->line, i - 1);
		else if (p->line[0] == 's' && p->line[1] == 'p')
			init_obj(p, p->line, i - 1);
	}
}

char	*get_numb(t_scene *p, int index)
{
	int				i;
	int				k;
	char			*num;

	i = 0;
	num = NULL;
	k = ft_strlen(p->line);
	while (p->line[i] != '\0')
	{
		while (ft_isdigit2(p->line[i]) == 0 && p->line[i] != '\0')
			i++;
		p->line = trim_numb(p->line, i);
		i = 0;
		while (ft_isdigit2(p->line[i]) == 1)
			i++;
		if (i > k)
			message("Your fd doesn't have enough information on line", index);
		if (i > 0)
			num = ft_strdup_num(p->line, 0, i);
		p->line = trim_numb(p->line, i);
		return (num);
		i++;
	}
	message(RED"Your fd doesn't have enough information on line"ENDC, index);
	return (num);
}

void	*trim_numb(char *line, int i)
{
	int		j;
	int		k;
	char	*new;

	k = 0;
	j = ft_strlen(line) - 1;
	if (j <= 0)
		return (NULL);
	new = wrmalloc(sizeof(char *) * ((j - i) + 2));
	if (!new)
		return (NULL);
	while (i <= j)
		new[k++] = line[i++];
	new[k] = '\0';
	line = new;
	return (line);
}
