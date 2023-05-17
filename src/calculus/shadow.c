/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:10:25 by jsollett          #+#    #+#             */
/*   Updated: 2023/05/17 13:37:44 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	shadow_plan(t_scene *p, t_plan *Pl)
{
	t_vector	intersect;

	intersect = *get_intersect(p);
	p->l.OCn = dot(sub(Pl->C, p->l.pos), Pl->n);
	p->l.dir = unit(sub(intersect, p->l.pos));
	p->l.ndotray_pl = dot(Pl->n, p->l.dir);
	p->l.n = Pl->n;
	p->l.OC = Pl->OC;
}

int	shadow_sphere(t_scene *p, t_sphere *Sph)
{
	t_vector	oc;
	t_vector	intersect;

	intersect = *get_intersect(p);
	oc = sub(p->l.pos, Sph->C);
	p->l.dir = unit(sub(intersect, p->l.pos));
	p->l.discr->a = dot(p->l.dir, p->l.dir);
	p->l.discr->b = 2 * dot(p->l.dir, oc);
	p->l.discr->c = norm_2(oc) - Sph->r2;
	p->l.discr->discr = discr(p->l.discr->a, p->l.discr->b, p->l.discr->c);
	if (p->l.discr->discr >= 0)
		return (1);
	else
		return (0);
}

void	get_cyl_disc2(t_scene *p, t_cyl *Cyl)
{
	p->l.cyl->discr->a = norm_2(p->l.dir) - pow(dot(p->l.dir, p->l.cyl->ul), 2);
	p->l.cyl->discr->b = 2 * dot(p->l.cyl->w1, p->l.dir)
		- 2 * dot(p->l.dir, p->l.cyl->ul) * dot(p->l.cyl->w1, p->l.cyl->ul);
	p->l.cyl->discr->c = norm_2(p->l.cyl->w1) - pow(dot(p->l.cyl->w1,
				p->l.cyl->ul), 2) - Cyl->r * Cyl->r;
	p->l.cyl->discr->discr = discr(p->l.cyl->discr->a,
			p->l.cyl->discr->b, p->l.cyl->discr->c);
}

void	init_shadow_cyl(t_scene *p, t_cyl *Cyl)
{
	p->l.cyl->C0 = Cyl->C0;
	p->l.cyl->C1 = add(Cyl->C0, scalar_prod(Cyl->dir, Cyl->h / norm(Cyl->dir)));
	p->l.cyl->OC = Cyl->OC;
	p->l.cyl->vl = sub(Cyl->C1, Cyl->C0);
	p->l.cyl->ul = unit(p->l.cyl->vl);
	p->l.cyl->w1 = sub(p->l.pos, Cyl->C0);
	p->l.cyl->r = Cyl->r;
	p->l.cyl->h = Cyl->h;
}

void	shadow_cyl(t_scene *p, t_cyl *Cyl)
{
	t_vector	intersect;

	intersect = *get_intersect(p);
	if (Cyl->inside == 0 || Cyl->inside == 1)
	{
		init_vector(&p->l.dir, 0, 0, 0);
		p->l.dir = unit(sub(intersect, p->l.pos));
	}
	init_shadow_cyl(p, Cyl);
	get_cyl_disc2(p, Cyl);
	if (p->l.cyl->discr->discr >= 0)
	{
		quadratic_solution2(p->l.cyl->discr);
		p->l.cyl->intersect0 = add(p->l.pos,
				scalar_prod(p->l.dir, p->l.cyl->discr->tmin));
		p->l.cyl->intersect1 = add(p->l.pos,
				scalar_prod(p->l.dir, p->l.cyl->discr->tmax));
		p->l.cyl->w = sub(p->l.cyl->intersect0, Cyl->C0);
		p->l.cyl->v = sub(p->l.cyl->intersect0, Cyl->C1);
		p->l.cyl->w11 = sub(p->l.cyl->intersect1, Cyl->C0);
		p->l.cyl->v11 = sub(p->l.cyl->intersect1, Cyl->C1);
	}
}
