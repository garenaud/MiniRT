/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:26:45 by jsollett          #+#    #+#             */
/*   Updated: 2023/04/14 15:27:12 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	compute_intersect_plan(t_ray ray, t_plan *P, double eps, int debug)
{// a tester
	P->ndotray = dot(P->n, ray.dir);// l1.n
	if (not_egal(P->ndotray, 0, eps))// not egal avant
	{

		P->tmin = P->OCn / P->ndotray;
		if ( P->tmin >0)
		{
			P->intersect0 = add(ray.orig, scalar_prod(ray.dir, P->tmin));
			if (debug)
			{
	//			printf(GREEN"plan_Hit(%d): ptmin = %lf\t",P->label, P->tmin);
	//		printv(&P->OC);
	//		printf(RED"Pocn = %lf\t", P->OCn);
				printv(&P->intersect0);
			}
		}
	}
	//...
}

double	plan_hit(t_plan *P,  double eps, int debug )
{// a tester faux, ne rentre pas
//	if (dot(P->intersect0, dir) >= 0)
//		return(P->tmin);
	if (not_egal(P->ndotray, 0, eps) && not_egal(P->OCn, 0, eps))
	{

		if (debug)
	//		printf("plan_Hit: ---ptmin = %lf\n", P->tmin);
		return (P->tmin);
	}
	return (-1);
}
