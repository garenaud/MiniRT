/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:26:45 by jsollett          #+#    #+#             */
/*   Updated: 2023/05/12 15:06:35 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	compute_intersect_plan(t_ray ray, t_plan *P)
{// a tester

 //  int debug = 0;
	P->ndotray = dot(P->n, ray.dir);// l1.n
	if (not_egal(P->ndotray, 0.0, EPS))// not egal avant
	{
		P->tmin = P->OCn / P->ndotray;
		if (P->tmin >= 0)//
		{
			P->intersect0 = add(ray.orig, scalar_prod(ray.dir, P->tmin));
		}
/*		else if (debug)
		{// a verifier si utile
			init_vector(&P->intersect0, POS_INF, POS_INF, POS_INF);
		}*/
	}
}

double	plan_hit(t_plan *P,  double eps, int debug )
{// a tester faux, ne rentre pas
//	if (dot(P->intersect0, dir) >= 0)
//		return(P->tmin);
	if (not_egal(P->ndotray, 0.0, eps) && not_egal(P->OCn, 0.0, eps))
	{

		if (debug)
	//		printf("plan_Hit: ---ptmin = %lf\n", P->tmin);
		return (P->tmin);
	}
	return (-1);
}

//double plan_hit1(t_plan *p)
double plan_hit1(t_plan *p, t_scene *s)
{
	double	r_hit;
	static int	count =0;
/*    if (p->intersect0.vec[0] == POS_INF)
	{
		printf("ptmin negatif ->");
		printv(&p->intersect0);
		return (-1);
	}*/
	r_hit = norm(sub(p->intersect0, s->c.pos));// avant p->C
	if (egal(dot(sub(p->intersect0, p->C), p->n), 0.0, EPS))
	{
		count++;
		//printf("count = %d\n", count);
		return (r_hit);

	}
	else
		return (-1);
}
void	put_plan(t_scene *p, int obj, int i, int j)
{
	double min_dist;
	if (obj != -1)
	{
	 //   compute_intersect_plan(p->ray, (t_plan *)p->forme[obj].ptr);
		min_dist = plan_hit((t_plan *)p->forme[obj].ptr, EPS, DEBUG);
		if (min_dist >= 0)
		{
			p->c.film[i][j] = ((t_plan *)(p->forme[p->closest->index].ptr))->color;
		}

	}
}

void	put_plan1(t_scene *p, int i, int j)
{
	double		p_tmin;
	t_vector	intersection;
	t_vector	arg1;
	t_vector	normal;
	t_vector    *amb;
	double		diffusion;
	int			fp;


if (p->closest->type == 1)
{
	p_tmin = ((t_plan *)(p->forme[p->closest->index].ptr))->tmin;
	intersection = ((t_plan *)((p->forme[p->closest->index].ptr)))->intersect0;
	arg1 = ((t_plan *)(p->forme[p->closest->index].ptr))->C;// doute dessus
	normal = ((t_plan *)(p->forme[p->closest->index].ptr))->n;

	diffusion = 0;
	if (p->closest->tmin != -1 && p->closest->type == 1 && egal(dot(normal, sub(intersection, arg1)), 0, EPS) == 1 && p_tmin > 0)
	{
		amb = ambiant1(p);
		fp = free_path(p);
		//if (!((free_path(p, i,j) != -1 && free_path(p,i,j) != p->closest->index) && (not_egal(p->l.cl->delta,0, EPS))))
		if ((fp == -1 || fp == p->closest->index) && (egal(p->l.cl->delta,0, EPS)))
		{
			if (light_side(&p->c.pos, &p->l.pos, &intersection, &normal) == 1)
			{
				diffusion = fabs(p->l.lum * dot(normal, reverse(p->l.dir))/(norm(normal)*norm(p->l.dir)));
			}
		}
		p->c.film[i][j].rgb[0] = (amb->vec[0] + diffusion)*(((t_plan *)(p->forme[p->closest->index].ptr))->color.rgb[0]);
		p->c.film[i][j].rgb[1] = (amb->vec[1] + diffusion)*(((t_plan *)(p->forme[p->closest->index].ptr))->color.rgb[1]);
		p->c.film[i][j].rgb[2] = (amb->vec[2] + diffusion)*(((t_plan *)(p->forme[p->closest->index].ptr))->color.rgb[2]);
		if (p->c.film[i][j].rgb[0] > 255)
			p->c.film[i][j].rgb[0] = 255;
		if (p->c.film[i][j].rgb[1] > 255)
			p->c.film[i][j].rgb[1] = 255;
		if (p->c.film[i][j].rgb[2] > 255)
			p->c.film[i][j].rgb[2] = 255;
		free (amb);
	}
	}
}
