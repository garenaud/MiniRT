/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:10:25 by jsollett          #+#    #+#             */
/*   Updated: 2023/05/12 15:08:57 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"
// exemple
void	shadow_plan(t_scene *p, t_plan *Pl)
{
	t_vector	intersect;

	if (p->forme[p->closest->index].id == 1)
		intersect = ((t_plan *)(p->forme[p->closest->index].ptr))->intersect0;
	if (p->forme[p->closest->index].id == 2)
		intersect = ((t_sphere *)(p->forme[p->closest->index].ptr))->intersect0;
	if (p->forme[p->closest->index].id == 3 && ((t_cyl *)(p->forme[p->closest->index].ptr))->inside == 0)
		intersect = ((t_cyl *)(p->forme[p->closest->index].ptr))->intersect0;
	if (p->forme[p->closest->index].id == 3 && ((t_cyl *)(p->forme[p->closest->index].ptr))->inside == 1)
		intersect = ((t_cyl *)(p->forme[p->closest->index].ptr))->intersect1;
	p->l.OCn = dot(sub(Pl->C, p->l.pos), Pl->n);
	p->l.dir = unit(sub(intersect, p->l.pos));
	p->l.ndotray_pl = dot(Pl->n, p->l.dir);
	p->l.n = Pl->n;
	p->l.OC = Pl->OC;
}

int	shadow_sphere(t_scene *p, t_sphere *Sph)
{
	t_vector	OC;
	t_vector	intersect;

	if (p->forme[p->closest->index].id == 2)
		intersect = ((t_sphere *)(p->forme[p->closest->index].ptr))->intersect0;
	if (p->forme[p->closest->index].id == 1)
		intersect = ((t_plan *)(p->forme[p->closest->index].ptr))->intersect0;
	if (p->forme[p->closest->index].id == 3 && ((t_cyl *)(p->forme[p->closest->index].ptr))->inside == 0)
		intersect = ((t_cyl *)(p->forme[p->closest->index].ptr))->intersect0;
	if (p->forme[p->closest->index].id == 3 && ((t_cyl *)(p->forme[p->closest->index].ptr))->inside == 1)
		intersect = ((t_cyl *)(p->forme[p->closest->index].ptr))->intersect1;
	OC = sub(p->l.pos, Sph->C);
	p->l.dir = unit(sub(intersect, p->l.pos));
	p->l.discr->a = dot(p->l.dir, p->l.dir);//
	p->l.discr->b = 2 * dot(p->l.dir, OC);
	p->l.discr->c = norm_2(OC) - Sph->r2;
	p->l.discr->discr = discr(p->l.discr->a, p->l.discr->b, p->l.discr->c);
	if (p->l.discr->discr >= 0)
		return (1);
	else
		return (0);
}

void	shadow_cyl(t_scene *p, t_cyl *Cyl)// modif signature plus inside ,avant void
{
	t_vector	intersect;
	//int			inside;
	//printf(PURP"inside (shadow cyl) = %d\n",Cyl->inside);
	//inside = ((t_cyl *)(p->forme[p->closest->index].ptr))->inside;
	if (p->forme[p->closest->index].id == 1)
		intersect = ((t_plan *)(p->forme[p->closest->index].ptr))->intersect0;
	if (p->forme[p->closest->index].id == 2)
		intersect = ((t_sphere *)(p->forme[p->closest->index].ptr))->intersect0;
	// ajout test inside 0905, faut il le faire ailleur ???
	if (p->forme[p->closest->index].id == 3 && Cyl->inside == 0)
		intersect = ((t_cyl *)(p->forme[p->closest->index].ptr))->intersect0;
	if (p->forme[p->closest->index].id == 3 && Cyl->inside == 1)
		intersect = ((t_cyl *)(p->forme[p->closest->index].ptr))->intersect1;
	// fin ajout 0905
	p->l.dir = unit(sub(intersect, p->l.pos));
	p->l.light.orig = p->l.pos;//0405
	p->l.light.dir = p->l.dir;//0405
/*	printf(GREEN"closest cylindre1 light:orig \t dir \n");
	 printv(&p->l.light.orig);
	  printv(&p->l.light.dir);*/
	p->l.cyl->C0 = Cyl->C0;
	p->l.cyl->C1 = add(Cyl->C0, scalar_prod(Cyl->dir, Cyl->h / norm(Cyl->dir)));
	//p->l.cyl->OC = sub(p->l.pos, Cyl->C0);
	p->l.cyl->OC = Cyl->OC;//0405
	p->l.cyl->vl = sub(Cyl->C1, Cyl->C0);
	p->l.cyl->ul = unit(p->l.cyl->vl);
	p->l.cyl->w1 = sub(p->l.pos, Cyl->C0);
	p->l.cyl->r = Cyl->r;
	p->l.cyl->h = Cyl->h;

	// get_coeff_cyl
	p->l.cyl->discr->a = norm_2(p->l.dir) - pow(dot(p->l.dir, p->l.cyl->ul), 2);
	p->l.cyl->discr->b = 2 * dot(p->l.cyl->w1, p->l.dir)
		- 2 * dot(p->l.dir, p->l.cyl->ul) * dot(p->l.cyl->w1, p->l.cyl->ul);
	p->l.cyl->discr->c = norm_2(p->l.cyl->w1) - pow(dot(p->l.cyl->w1,p->l.cyl->ul), 2) - Cyl->r * Cyl->r;
	p->l.cyl->discr->discr = discr(p->l.cyl->discr->a, p->l.cyl->discr->b, p->l.cyl->discr->c);
	// compute_intersecT_cyl
	if (p->l.cyl->discr->discr >= 0)
	{// vue de la lumiere, ne tient pas compte dim. cylindre
		quadratic_solution2(p->l.cyl->discr);
		p->l.cyl->intersect0 = add(p->l.pos, scalar_prod(p->l.dir, p->l.cyl->discr->tmin));
		p->l.cyl->intersect1 = add(p->l.pos, scalar_prod(p->l.dir, p->l.cyl->discr->tmax));
		p->l.cyl->w = sub(p->l.cyl->intersect0, Cyl->C0);
		p->l.cyl->v = sub(p->l.cyl->intersect0, Cyl->C1);
		p->l.cyl->w11 = sub(p->l.cyl->intersect1, Cyl->C0);
		p->l.cyl->v11 = sub(p->l.cyl->intersect1, Cyl->C1);
		if (egal_v(p->l.cyl->intersect0, intersect, EPS))
		{
			//printf(PURP"impact lumiere = intersect 0 (vue cam)\n");
			//return (p->l.cyl->discr->tmin);// ajout fin 0905
		}
		if (egal_v(p->l.cyl->intersect1, intersect, EPS))
		{
			//printf(PURP"impact lumiere = intersect 1 (vue cam)\n");
			//return (p->l.cyl->discr->tmax);// ajout fin 0905
		}
	}
}
