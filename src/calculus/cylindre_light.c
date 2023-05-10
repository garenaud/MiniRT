/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylindre_light.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:59:30 by jsollett          #+#    #+#             */
/*   Updated: 2023/05/09 16:50:59 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"



void	closest_cylindre1(t_scene *p, t_vector *intersect, int obj)
{
	double	tmp;
	double	min_dist;
	int		inside;

	min_dist = 0;
	inside = ((t_cyl *)(p->forme[obj].ptr))->inside;
	/*tmp = */shadow_cyl(p, (t_cyl *)p->forme[obj].ptr);// ajout fin0905
//	get_coeff_cyl(p->l.cyl->discr, &p->l.light, (t_cyl *)p->forme[obj].ptr);//0405 foire
/*	printf(RED"closest cylindre1 light:orig \t dir \n");
		 printv(&p->l.light.orig);
	printv(&p->l.light.dir);*/
	if (p->l.cyl->discr->discr >= 0)
	{
		quadratic_solution2(p->l.cyl->discr);
	//	compute_intersect_cyl(p->l.cyl->discr, p->l.light, (t_cyl *)p->forme[obj].ptr);// 0405
		tmp = cylindre_hit(p->l.cyl, p->l.cyl->discr, EPS);

		//tmp = cylindre_hit((t_cyl *)p->forme[obj].ptr, p->l.cyl->discr, EPS);
		if (tmp >= 0 && p->l.cyl->inside != 2)// ajout 0405
		{
			p->l.li = add(p->l.pos, scalar_prod(p->l.dir, tmp));
			min_dist = norm(sub(p->l.pos, p->l.li));
			if ( min_dist > 0 && min_dist < p->l.cl->dmin)
			{
				p->l.cl->index = obj;
				p->l.cl->tmin = p->delta->tmin;
				p->l.cl->dmin = min_dist;
				p->l.cl->type = p->forme[obj].id;
				p->l.cl->delta = norm(sub(p->l.li, *intersect));
			}
		}
	}
}
