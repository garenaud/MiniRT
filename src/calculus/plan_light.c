/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 11:47:51 by jsollett          #+#    #+#             */
/*   Updated: 2023/05/18 11:04:49 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	light_intersect_pl(t_scene *p)
{
	if (not_egal(p->l.ndotray_pl, 0.0, EPS))
	{
		p->l.tmin = p->l.ocn / p->l.ndotray_pl;
		if (p->l.tmin >= 0)
			p->l.li = add(p->l.pos, scalar_prod(p->l.dir, p->l.tmin));
	}
}

void	closest_plan1(t_scene *p, t_vector *intersect, int obj)
{
	p->l.cl->min_dist = 0;
	shadow_plan(p, (t_plan *)p->forme[obj].ptr);
	light_intersect_pl(p);
	if (light_plan_hit(p) != -1)
	{
		p->l.cl->min_dist = norm(sub(p->l.pos, p->l.li));
		if (p->l.tmin >= 1 && p->l.cl->min_dist > 0
			&& p->l.cl->min_dist < p->l.cl->dmin)
			update_light_closest_plan(p, intersect, obj);
	}
}

double	light_plan_hit(t_scene *p)
{
	if (not_egal(p->l.ndotray_pl, 0.0, EPS) && not_egal(p->l.ocn, 0.0, EPS))
	{
		return (p->l.tmin);
	}
	return (-1);
}

void	update_light_closest_plan(t_scene *p, t_vector *intersect, int obj)
{
	p->l.cl->index = obj;
	p->l.cl->tmin = p->l.tmin;
	p->l.cl->dmin = p->l.cl->min_dist;
	p->l.cl->type = p->forme[obj].id;
	p->l.cl->delta = norm(sub(p->l.li, *intersect));
}
