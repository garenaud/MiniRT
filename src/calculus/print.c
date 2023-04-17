/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:14:59 by jsollett          #+#    #+#             */
/*   Updated: 2023/04/17 14:40:18 by jsollett         ###   ########.fr       */
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
