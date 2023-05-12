/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:26:06 by jsollett          #+#    #+#             */
/*   Updated: 2023/05/12 15:02:07 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	get_coeff_sph(t_discr *d, t_ray *ray, t_sphere *Sph)
{// a tester
	d->a = dot(ray->dir, ray->dir);
	d->b = 2 * dot(ray->dir, Sph->OC);
	d->c = Sph->discr_c;
	d->discr = discr(d->a, d->b, d->c);
}

void	compute_intersect_sph(t_discr *delta, t_ray ray, t_sphere *Sph)
{// pb
	Sph->intersect0 = add(ray.orig, scalar_prod(ray.dir, delta->tmin));
//	printv(&Sph->intersect0);
}

double	sphere_hit(t_sphere *Sph, t_discr *delta, double eps)
{
	(void)delta;
	double	r_hit;

	r_hit = norm(sub(Sph->intersect0, Sph->C));
	if (egal(r_hit, Sph->r, eps))
	{
		return (r_hit);
	}
	else
		return (-1);
}

// a modifier, ici aussi a modifier 92, et voir la logique...
void	put_sphere(t_scene *p, int obj, int i, int j)
{
	double min_dist;

	if (p->forme[obj].id == 2)
	{
		get_coeff_sph(p->delta, &p->ray, (t_sphere *)p->forme[obj].ptr);
		quadratic_solution2(p->delta);
		compute_intersect_sph(p->delta, p->ray, (t_sphere *)p->forme[obj].ptr);
		min_dist = sphere_hit((t_sphere *)p->forme[obj].ptr, p->delta,EPS);
		if (min_dist >= 0)
		{
			p->c.film[i][j] = ((t_sphere *)(p->forme[obj].ptr))->color;
		}
	}
}
//printf(GREEN"avant put sphere %d\n"ENDC, p->closest->index);
void	put_sphere1(t_scene *p, int i, int j)
{
	t_vector	*amb;

	if (p->closest->tmin != -1 && p->closest->type == 2)
	{
		amb = ambiant1(p);
		//p->c.film[i][j] = ((t_sphere *)(p->forme[p->closest->index].ptr))->color;
		p->c.film[i][j].rgb[0] = amb->vec[0]*(((t_sphere *)(p->forme[p->closest->index].ptr))->color.rgb[0]);
		p->c.film[i][j].rgb[1] = amb->vec[1]*(((t_sphere *)(p->forme[p->closest->index].ptr))->color.rgb[1]);
		p->c.film[i][j].rgb[2] = amb->vec[2]*(((t_sphere *)(p->forme[p->closest->index].ptr))->color.rgb[2]);
	}
}

void	put_sphere2(t_scene *p, int i, int j)
{
	t_vector	*amb;
	t_vector	intersection;
	t_vector	normal;
	int			obj;
	double		diffusion;
	int			fp;

	obj = 0;
	diffusion = 0;
	if (p->closest->tmin != -1 && p->closest->type == 2)
	{
		intersection = ((t_sphere *)(p->forme[p->closest->index].ptr))->intersect0;
		normal = sub(intersection, ((t_sphere *)(p->forme[p->closest->index].ptr))->C);
		amb = ambiant1(p);
		//diffusion = p->l.lum * dot(normal, reverse(p->l.dir))/(norm_2(normal)*norm_2(p->l.dir));
		fp = free_path(p);
		if ((/*free_path(p,i,j)*/fp == -1 || /*free_path(p,i,j)*/ fp == p->closest->index ) && (egal(p->l.cl->delta,0, EPS)))
		{
			if (light_side(&p->c.pos, &p->l.pos, &intersection, &normal) == 1)
			{
				diffusion = p->l.lum * dot(normal, reverse(p->l.dir))/(norm(normal)*norm(p->l.dir));
/* 				if (j == 500 && i == 500)
				{
					printf(RED"diffusion at centre = %lf\n", diffusion);
					printv(&p->l.dir);
					printv(&normal);
				} *///*amb = scalar_prod(*amb, (1/*+p->l.lum*/));// 2<--> diffusion
			}
		}
		p->c.film[i][j].rgb[0] = (amb->vec[0]+ diffusion)*(((t_sphere *)(p->forme[p->closest->index].ptr))->color.rgb[0]);
		p->c.film[i][j].rgb[1] = (amb->vec[1]+ diffusion)*(((t_sphere *)(p->forme[p->closest->index].ptr))->color.rgb[1]);
		p->c.film[i][j].rgb[2] = (amb->vec[2]+ diffusion)*(((t_sphere *)(p->forme[p->closest->index].ptr))->color.rgb[2]);
		if (p->c.film[i][j].rgb[0] > 255)
			p->c.film[i][j].rgb[0] = 255;
		if (p->c.film[i][j].rgb[1] > 255)
			p->c.film[i][j].rgb[1] = 255;
		if (p->c.film[i][j].rgb[2] > 255)
			p->c.film[i][j].rgb[2] = 255;
		free(amb);
	}
}
