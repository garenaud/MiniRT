/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 10:10:29 by jsollett          #+#    #+#             */
/*   Updated: 2023/04/21 16:02:22 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	closest_sphere(t_scene *p, int obj)
{
	double	min_dist;

	min_dist = 0;
	get_coeff_sph(p->delta, &p->ray, (t_sphere *)p->forme[obj].ptr);
	if (p->delta->discr >= 0)
	{
		quadratic_solution2(p->delta);
		compute_intersect_sph(p->delta, p->ray, (t_sphere *)p->forme[obj].ptr);
		if (sphere_hit((t_sphere *)p->forme[obj].ptr, p->delta, EPS) != -1)
		{
			min_dist = norm(sub(p->c.pos,
						((t_sphere *)p->forme[obj].ptr)->intersect0));
		}
		if (min_dist > 0 && min_dist < p->closest->dmin)
		{
			p->closest->index = obj;
			p->closest->tmin = p->delta->tmin;
			p->closest->dmin = min_dist;
			p->closest->type = p->forme[obj].id;
		}
	}
}

void	closest_plan(t_scene *p, int obj, int i, int j)
{
	double	min_dist;
//	static int count = 0;
//  printf("(i,j) = (%d,%d)\n",i,j);
	min_dist = 0;
    int debug;
    if (j % 240 == 0 && i % 40 == 0)
        debug = 1;
    else
        debug = 0;
	//printv(&p->ray.dir);
	compute_intersect_plan(p->ray, (t_plan *)p->forme[obj].ptr, debug);
	if (plan_hit1((t_plan *)p->forme[obj].ptr, p) != -1)
	{
//		count++;

		min_dist = norm(sub(p->c.pos, ((t_plan *)p->forme[obj].ptr)->intersect0));
		//printf("%d min_dist = %10.10lf \n", count, min_dist);
		//printf(RED"count %d dmin = %10.10lf \n", count, p->closest->dmin);
		if (min_dist > 0 && min_dist < p->closest->dmin)
		{
			p->closest->index = obj;
			p->closest->tmin = (((t_plan *)p->forme[obj].ptr)->tmin);
			p->closest->dmin = min_dist;
			p->closest->type = p->forme[obj].id;
		}
		if ((j % 240) == 0 && (i % 40) == 0)
		{
			printf("(i,j) = (%d,%d)\t",i,j);
			printf(RED"obj = %d, mdist = %10.10lf, p->closest->dmin = %10.10lf \t"ENDC, obj, min_dist, p->closest->dmin);
            printv(&((t_plan *)p->forme[obj].ptr)->intersect0);
         //   printv(&p->ray.dir);
		}
		//printf(GREEN"count %d dmin = %10.10lf \n"ENDC, count, p->closest->dmin);
	}
}
