/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:26:45 by jsollett          #+#    #+#             */
/*   Updated: 2023/04/21 15:48:52 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	compute_intersect_plan(t_ray ray, t_plan *P, int debug)
{// a tester
 // printv(&P->intersect0);
   // printf("\n*\n");
/*	 printf(PURP);*/
  //   printv(&P->n);
   //  printv(&ray.dir);
 //  int debug = 0;
	P->ndotray = dot(P->n, ray.dir);// l1.n

	//printf(PURP"compute plan ndotray = %10.19lf\n"ENDC, P->ndotray);
	if (not_egal(P->ndotray, 0.0, EPS))// not egal avant
	{

		P->tmin = P->OCn / P->ndotray;

		if (P->tmin >= 0)//
		{
		//	printf("\n*\n");
			P->intersect0 = add(ray.orig, scalar_prod(ray.dir, P->tmin));
		//	printv(&P->intersect0);
			if (debug)
			{
	//		printf(GREEN"plan_Hit(%d): ptmin = %lf\t",P->label, P->tmin);
	//		printv(&P->OC);
	//		printf(RED"Pocn = %lf\t", P->OCn);
            printf(RED); printf("obj = 1");
			printv(&P->intersect0);
            printf(ENDC);
			}
		}
	}// ajout 1904
/*	else
	{// attn pas intersection (dir T n)
		P->tmin = POS_INF;
		P->index = POS_INF;
	}
*/	//...
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

if (p->closest->type == 1)
{
	p_tmin = ((t_plan *)(p->forme[p->closest->index].ptr))->tmin;
    //p_tmin = p->closest->dmin;
	intersection = ((t_plan *)((p->forme[p->closest->index].ptr)))->intersect0;
	arg1 = ((t_plan *)(p->forme[p->closest->index].ptr))->C;// doute dessus
	normal = ((t_plan *)(p->forme[p->closest->index].ptr))->n;
}
/*	if (p->closest->tmin != -1 && p->closest->type == 1 && dot(p->c.dir,sub(((t_plan *)
		(p->forme[p->closest->index].ptr))->intersect0, ((t_plan *)(p->forme[p->closest->index].ptr))->C)) > 0
		&& ((t_plan *)(p->forme[p->closest->index].ptr))->tmin >0)*/
	if (p->closest->tmin != -1 && p->closest->type == 1 && egal(dot(normal, sub(intersection, arg1)), 0, EPS) == 1 && p_tmin > 0)
	{
		p->c.film[i][j] = ((t_plan *)(p->forme[p->closest->index].ptr))->color;
	}
}
