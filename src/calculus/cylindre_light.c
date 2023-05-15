/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylindre_light.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:59:30 by jsollett          #+#    #+#             */
/*   Updated: 2023/05/15 14:52:01 by jsollett         ###   ########.fr       */
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
	//if (inside == 1 || inside == 0)
	{
		shadow_cyl(p, (t_cyl *)p->forme[obj].ptr);// ajout fin0905
		if (p->l.cyl->discr->discr >= 0)
		{
			quadratic_solution2(p->l.cyl->discr);
			tmp = cylindre_hit(p->l.cyl, p->l.cyl->discr, EPS);
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
}
