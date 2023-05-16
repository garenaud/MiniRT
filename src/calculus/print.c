/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:14:59 by jsollett          #+#    #+#             */
/*   Updated: 2023/05/16 12:10:22 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	printv(t_vector *v)
{
	printf(" %f %f %f \n", v->vec[0], v->vec[1], v->vec[2]);
}

void	print(t_rgb **a, int col, int row)
{
	int	i;
	int	j;

	printf("P3\n");
	printf("%d", col);
	printf(" ");
	printf("%d", row);
	printf("\n255\n");
	j = row - 1;
	while (j >= 0)
	{
		i = 0;
		while (i < col)
		{
			printf("%d %d %d \n ", a[i][j].rgb[0],
				a[i][j].rgb[1], a[i][j].rgb[2]);
			++i;
		}
	--j;
	}
}

void	print_parsing(t_scene *p, int debug)
{
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

void	printll_obj(t_listobj *obj)
{
	int	i;

	i = 1;
	printf(RED"\n-------------------------------------------------------"ENDC);
	printf(RED"\nstart obj list\n\n"ENDC);
	if (!obj)
		printf(RED"\nla liste n'existe pas!!!\n"ENDC);
	while (obj)
	{
		if (obj->id == 3)
		{
			printf(GREEN"objet N%d \nid = %d\n"ENDC, obj->index, (obj->id));
			printf(GREEN"coordonne f \t[x %f]\t[y %f]\t[z %f]\n"ENDC, (obj->pos.vec[0]), (obj->pos.vec[1]), (obj->pos.vec[2]));
			printf(GREEN"vect 3d \t[x %f]\t[y %f]\t[z %f]\n"ENDC, (obj->dir.vec[0]), (obj->dir.vec[1]), (obj->dir.vec[2]));
			printf(GREEN"diametre \t[%f] \nhauteur \t[%f]\n"ENDC, (obj->r), (obj->h));
			printf(GREEN"color \t\t[R %d]\t\t[G %d]\t\t[B %d]\n\n"ENDC, (obj->color.rgb[0]), (obj->color.rgb[1]), (obj->color.rgb[2]));
		}
		if (obj->id == 2)
		{
			printf(PURP"objet N%d \nid = %d\n"ENDC, obj->index, (obj->id));
			printf(PURP"coordonne \t[x %f]\t[y %f]\t[z %f]\n"ENDC, (obj->pos.vec[0]), (obj->pos.vec[1]), (obj->pos.vec[2]));
			printf(PURP"diametre \t[%f]\n"ENDC, (obj->r));
			printf(PURP"color \t\t[R %d]\t\t[G %d]\t\t[B %d]\n\n"ENDC, (obj->color.rgb[0]), (obj->color.rgb[1]), (obj->color.rgb[2]));
		}
		if (obj->id == 1)
		{
			printf(BLUE"objet N%d \nid = %d\n"ENDC, obj->index, (obj->id));
			printf(BLUE"coordonne f \t[x %f]\t[y %f]\t[z %f]\n"ENDC, (obj->pos.vec[0]), (obj->pos.vec[1]), (obj->pos.vec[2]));
			printf(BLUE"vect 3d \t[x %f]\t[y %f]\t[z %f]\n"ENDC, (obj->dir.vec[0]), (obj->dir.vec[1]), (obj->dir.vec[2]));
			printf(BLUE"color \t\t[R %d]\t\t[G %d]\t\t[B %d]\n\n"ENDC, (obj->color.rgb[0]), (obj->color.rgb[1]), (obj->color.rgb[2]));
		}
		i++;
		obj = obj->next;
	}
	printf(RED"-------------------------------------------------------\n\n"ENDC);
}
