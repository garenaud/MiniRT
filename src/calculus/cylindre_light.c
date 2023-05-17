/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylindre_light.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:59:30 by jsollett          #+#    #+#             */
/*   Updated: 2023/05/17 16:37:32 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	closest_cylindre1(t_scene *p, t_vector *intersect, int obj)
{
	double	tmp;

	p->l.cl->min_dist = 0;
	{
		shadow_cyl(p, (t_cyl *)p->forme[obj].ptr);
		if (p->l.cyl->discr->discr >= 0)
		{
			quadratic_solution2(p->l.cyl->discr);
			tmp = cylindre_hit(p->l.cyl, p->l.cyl->discr, EPS);
			if (tmp >= 0 && p->l.cyl->inside != 2)
			{
				p->l.li = add(p->l.pos, scalar_prod(p->l.dir, tmp));
				p->l.cl->min_dist = norm(sub(p->l.pos, p->l.li));
				if (p->l.cl->min_dist > 0 && p->l.cl->min_dist < p->l.cl->dmin)
					update_light_closest_cyl(p, intersect, obj);
			}
		}
	}
}

void	update_light_closest_cyl(t_scene *p, t_vector *intersect, int obj)
{
	p->l.cl->index = obj;
	p->l.cl->tmin = p->delta->tmin;
	p->l.cl->dmin = p->l.cl->min_dist;
	p->l.cl->type = p->forme[obj].id;
	p->l.cl->delta = norm(sub(p->l.li, *intersect));
}
