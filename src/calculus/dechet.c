/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dechet.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 09:52:06 by jsollett          #+#    #+#             */
/*   Updated: 2023/05/16 16:43:58 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// dans put cylindre1
if (/*i == 565 &&*/ j == 700)
		{
			//t_vector tmp2 = sub(p->l.pos,((t_cyl *)(p->forme[p->closest->index].ptr))->C0);
			//double test=norm(perpendicular(p->l.dir,((t_cyl *)(p->forme[p->closest->index].ptr))->ul ));
			/*printf(RED"%d\n",p->c.film[i][j].rgb[0]);
			printf(GREEN"%d\n",p->c.film[i][j].rgb[1]);
			printf(BLUE"%d\n",p->c.film[i][j].rgb[2]);*/
			//t_discr	*disc =((t_cyl *)(p->forme[p->closest->index].ptr))->discr;
			printf("(i,j)=(%d,%d)\t indide = %d\t diffusion = %lf, |normal| = (%lf, %lf, %lf)  |intersection | = (%lf, %lf, %lf)\n",i,j, inside, diffusion,
            normal.vec[0], normal.vec[1], normal.vec[2],
             intersection.vec[0], intersection.vec[1], intersection.vec[2]);
             printf("(i,j)=(%d,%d)\t indide = %d\t diffusion = %lf, |p->l.dir| = (%lf, %lf, %lf) \n",i,j, inside, diffusion,
            p->l.dir.vec[0], p->l.dir.vec[1], p->l.dir.vec[2]);
			printf("(i,j)=(%d,%d)\t indide = %d\t\n",i,j, inside);
		}

// dans fin shadow cylindre
/*		if (egal_v(p->l.cyl->intersect0, intersect, EPS))
		{
			//printf(PURP"impact lumiere = intersect 0 (vue cam)\n");
			//return (p->l.cyl->discr->tmin);// ajout fin 0905
		}
		if (egal_v(p->l.cyl->intersect1, intersect, EPS))
		{
			//printf(PURP"impact lumiere = intersect 1 (vue cam)\n");
			//return (p->l.cyl->discr->tmax);// ajout fin 0905
		}*/

dans ray ray_tracer_2
				if (i == 565 && j == 700)
				{
					printf("label: obj = %d\n", obj);
				}
minirt
//	printf(RED"ll - vpmiddle = %lf\n"ENDC, norm(sub(p->c.ll, p->c.vp_middle)));
minirt
for (int i = 0; i < VIEWPORT_WIDTH; i++)
	{
//	axe(p, i,700);
//	axe(p,565, i);
//	axe(p,i, 480);
  //  axe(p,200, i);
//	axe(p,i, 490);
//	axe(p,i, 423);
//	axe(p, 840, i);
//	axe(p, i, 950);
	}

dans cylput
/*					if (p->data.diffusion <0 ) // test on enleve diffusion negative
						p->data.diffusion *= -1; //IL faut tenir compte si lumiere interieure*/

/*		inside = ((t_cyl *)(p->forme[p->closest->index].ptr))->inside;
		if (inside == 0)
		{
			p->data.intersection = ((t_cyl *)(p->forme[p->closest->index].ptr))->intersect0;
			p->data.normal = perpendicular(((t_cyl *)(p->forme[p->closest->index].ptr))->w,((t_cyl *)(p->forme[p->closest->index].ptr))->ul);
		}
		else if (inside ==1)
		{
			p->data.intersection = ((t_cyl *)(p->forme[p->closest->index].ptr))->intersect1;
			p->data.normal = perpendicular(((t_cyl *)(p->forme[p->closest->index].ptr))->w11,((t_cyl *)(p->forme[p->closest->index].ptr))->ul);
		}*/

dans sphere put sphere
	//t_vector	intersection;
	//t_vector	normal;
	//double		diffusion;
	//int			fp;


dans shadow_cyl
/*	p->l.cyl->discr->a = norm_2(p->l.dir) - pow(dot(p->l.dir, p->l.cyl->ul), 2);
	p->l.cyl->discr->b = 2 * dot(p->l.cyl->w1, p->l.dir)
		- 2 * dot(p->l.dir, p->l.cyl->ul) * dot(p->l.cyl->w1, p->l.cyl->ul);
	p->l.cyl->discr->c = norm_2(p->l.cyl->w1) - pow(dot(p->l.cyl->w1,p->l.cyl->ul), 2) - Cyl->r * Cyl->r;
	p->l.cyl->discr->discr = discr(p->l.cyl->discr->a, p->l.cyl->discr->b, p->l.cyl->discr->c);*/
version fonctionnant
void	shadow_cyl(t_scene *p, t_cyl *Cyl)
{
	t_vector	intersect;

	intersect = *get_intersect(p);
/*	if (p->forme[p->closest->index].id == 1)
		intersect = ((t_plan *)(p->forme[p->closest->index].ptr))->intersect0;
	if (p->forme[p->closest->index].id == 2)
		intersect = ((t_sphere *)(p->forme[p->closest->index].ptr))->intersect0;
	if (p->forme[p->closest->index].id == 3 && Cyl->inside == 0)
		intersect = ((t_cyl *)(p->forme[p->closest->index].ptr))->intersect0;
	if (p->forme[p->closest->index].id == 3 && Cyl->inside == 1)
		intersect = ((t_cyl *)(p->forme[p->closest->index].ptr))->intersect1;*/
	if (Cyl->inside == 0 || Cyl->inside == 1)
	{
		init_vector(&p->l.dir, 0,0,0);
		p->l.dir = unit(sub(intersect, p->l.pos));
	}
	init_shadow_cyl(p, Cyl);
/*	p->l.cyl->C0 = Cyl->C0;
	p->l.cyl->C1 = add(Cyl->C0, scalar_prod(Cyl->dir, Cyl->h / norm(Cyl->dir)));
	p->l.cyl->OC = Cyl->OC;//0405
	p->l.cyl->vl = sub(Cyl->C1, Cyl->C0);
	p->l.cyl->ul = unit(p->l.cyl->vl);
	p->l.cyl->w1 = sub(p->l.pos, Cyl->C0);
	p->l.cyl->r = Cyl->r;
	p->l.cyl->h = Cyl->h;
*/
	// get_coeff_cyl
	get_cyl_disc2(p, Cyl);
/*	p->l.cyl->discr->a = norm_2(p->l.dir) - pow(dot(p->l.dir, p->l.cyl->ul), 2);
	p->l.cyl->discr->b = 2 * dot(p->l.cyl->w1, p->l.dir)
		- 2 * dot(p->l.dir, p->l.cyl->ul) * dot(p->l.cyl->w1, p->l.cyl->ul);
	p->l.cyl->discr->c = norm_2(p->l.cyl->w1) - pow(dot(p->l.cyl->w1,p->l.cyl->ul), 2) - Cyl->r * Cyl->r;
	p->l.cyl->discr->discr = discr(p->l.cyl->discr->a, p->l.cyl->discr->b, p->l.cyl->discr->c);*/
	// compute_intersecT_cyl
	if (p->l.cyl->discr->discr >= 0)
	{
		quadratic_solution2(p->l.cyl->discr);
		p->l.cyl->intersect0 = add(p->l.pos, scalar_prod(p->l.dir, p->l.cyl->discr->tmin));
		p->l.cyl->intersect1 = add(p->l.pos, scalar_prod(p->l.dir, p->l.cyl->discr->tmax));
		p->l.cyl->w = sub(p->l.cyl->intersect0, Cyl->C0);
		p->l.cyl->v = sub(p->l.cyl->intersect0, Cyl->C1);
		p->l.cyl->w11 = sub(p->l.cyl->intersect1, Cyl->C0);
		p->l.cyl->v11 = sub(p->l.cyl->intersect1, Cyl->C1);
	}
}

dans freepath
/*	if (p->closest->type == 3 && ((t_cyl *)(p->forme[p->closest->index].ptr))->inside == 2)
	{// a verifier
		printf("Cyl !\n");
	}*/
