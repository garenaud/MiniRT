/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 11:47:51 by jsollett          #+#    #+#             */
/*   Updated: 2023/05/04 14:41:20 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	light_intersect_pl(t_scene *p)
{// a tester
	int 	debug = 1;

//	p->ndotray = dot(p->n, p->l.dir);

	if (not_egal(p->l.ndotray_pl, 0.0, EPS))
	{
		 p->l.tmin = p->l.OCn / p->l.ndotray_pl;
		if ( p->l.tmin >= 0)//
		{
			p->l.li = add(p->l.pos, scalar_prod(p->l.dir,  p->l.tmin));
			if (egal(norm(sub(p->l.li, ((t_plan *)(p->forme[p->closest->index].ptr))->intersect0)), 0, EPS))
			{
				//printf(GREEN"OK\t l.tmin = %lf\n"ENDC,  p->l.tmin);
			}
			else
			{
			//	printf(RED"KO\t %lf \t l.tmin = %lf\n"ENDC,norm(cross(sub(p->l.li, p->l.OC), p->l.n)) ,  p->l.tmin);
			//	printv(&p->l.li);
			//	printv((&((t_plan *)(p->forme[p->closest->index].ptr))->intersect0));
			}
		}
		else if (debug)
		{
		//printf("check cas ptmin <0\n"PURP);
		//init_vector(&p->l.li, POS_INF, POS_INF, POS_INF);//fait foirer la partie sur sphere
		}
	}
}

void	closest_plan1(t_scene *p, t_vector *intersect, int obj)
{
	double	min_dist;
	int debug;

	min_dist = 0;
	debug = 0;
	shadow_plan(p, (t_plan *)p->forme[obj].ptr);
	light_intersect_pl(p);
	if (light_plan_hit(p) != -1)
	{// entre toujours ??
		min_dist = norm(sub(p->l.pos, p->l.li ));
		//if (((t_plan *)p->forme[obj].ptr)->tmin >=1 && min_dist > 0 && min_dist < p->closest->dmin)
		if (p->l.tmin >= 1 && min_dist > 0 && min_dist < p->l.cl->dmin)
		{// closest
			p->l.cl->index = obj;
			//p->closest->tmin = (((t_plan *)p->forme[obj].ptr)->tmin);
			p->l.cl->tmin = p->l.tmin;
			p->l.cl->dmin = min_dist;
			p->l.cl->type = p->forme[obj].id;
			p->l.cl->delta = norm(sub(p->l.li, *intersect));

		}
	}
/*    else
	printf(GREEN"not hit plan \t"ENDC);*/
}

double	light_plan_hit(t_scene *p)
{

	if (not_egal(p->l.ndotray_pl, 0.0, EPS) && not_egal(p->l.OCn, 0.0, EPS))
	{
		return (p->l.tmin);
	}
	return (-1);
}
