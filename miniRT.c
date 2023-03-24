/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:04:14 by grenaud-          #+#    #+#             */
/*   Updated: 2023/03/23 20:55:23 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int		main(int argc, char **argv)
{
	t_scene	p;
	(void) argc;
	
	parsing(&p, argv);
	printf(GREEN"\n\np->a.lum = %f, p->a.color.rgb[0] = %d, p->a.color.rgb[1] = %d, p->a.color.rgb[2] = %d\n"ENDC, p.a.lum, p.a.color.rgb[0], p.a.color.rgb[1], p.a.color.rgb[2]);
	printf(BLUE"\n\np->c.vec[0] = %f, p->c.vec[1] = %f, p->c.vec[2] = %f, p->c.dir.vec[0] = %f, p->c.dir.vec[1] = %f, p->c.dir.vec[2] = %f, p->c.fov = %f, \n"ENDC, p.c.pos.vec[0], p.c.pos.vec[1], p.c.pos.vec[2], p.c.dir.vec[0], p.c.dir.vec[1], p.c.dir.vec[2], p.c.fov);
	printf(YEL"\n\np->l.pos.vec[0] = %f, p->l.pos.vec[1] = %f, p->l.pos.vec[2] = %f, p->l.lum = %f, p->l.color.rgb[0] = %d, p->l.color.rgb[1] = %d, p->l.color.rgb[2] = %d \n"ENDC, p.l.pos.vec[0], p.l.pos.vec[1], p.l.pos.vec[2], p.l.lum, p.l.color.rgb[0], p.l.color.rgb[1], p.l.color.rgb[2]);

	//printf("lumiere = %f, R = %d, G = %d, B = %d", p->a.lum, p->a.color.rgb[0], p->a.color.rgb[1], p->a.color.rgb[2]);
	return (0);
}
