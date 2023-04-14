#include "miniRT.h"
// faux plan.
/*
void	get_coeff_cyl(t_discr *d, t_ray ray, t_cyl Cyl)
{
	d->a = norm_2(ray.dir) - pow(dot(ray.dir, Cyl.ul), 2);
	d->b = 2 * dot(Cyl.w1, ray.dir) - 2 * dot(ray.dir, Cyl.ul) * dot(Cyl.w1, Cyl.ul);
	d->c = norm_2(Cyl.w1) - pow(dot(Cyl.w1,Cyl.ul),2) - Cyl.r*Cyl.r;
	d->discr = discr(d->a, d->b, d->c);
}
*/
void	get_coeff_sph(t_discr *d, t_ray ray, t_sphere Sph)
{// a tester
	d->a = dot(ray.dir, ray.dir);
	d->b = 2 * dot(ray.dir, Sph.OC);
	d->c = Sph.discr_c;
	d->discr = discr(d->a, d->b, d->c);
}

void	compute_intersect_sph(t_discr *delta, t_ray ray, t_sphere *Sph)
{
	Sph->intersect0 = add(ray.orig, scalar_prod(ray.dir, delta->tmin));
	printv(&Sph->intersect0);
}

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
/*
void	compute_intersect_cyl(t_discr *delta, t_ray ray , t_cyl *Cyl)
{
	Cyl->intersect0 = add(ray.orig,scalar_prod(ray.dir, delta->tmin));
	Cyl->intersect1 = add(ray.orig, scalar_prod(ray.dir, delta->tmax));
	// insertion des calculs apres intersection...
	Cyl->w = sub(Cyl->intersect0, Cyl->C0);
	Cyl->v = sub(Cyl->intersect0, Cyl->C1);
	Cyl->w11 = sub(Cyl->intersect1, Cyl->C0);
	Cyl->v11 = sub(Cyl->intersect1, Cyl->C1);
}

double	intersect_axe(t_cyl *Cyl, int param)
{
	t_vector	v_tmp;
	double		tmp;

	tmp = -1.0;
	if (param == 0)
	{
		v_tmp = sub(Cyl->intersect0, Cyl->C0);
		tmp = norm(perpendicular(v_tmp, Cyl->ul));
	}
	if (param == 1)
	{
		v_tmp = sub(Cyl->intersect1, Cyl->C0);
		tmp = norm(perpendicular(v_tmp, Cyl->ul));
	}
	return (tmp);
}
//	intersect0 lie a  tmin
//	intersect1 lie a  tmax


double	cylindre_hit(t_cyl *Cyl, t_discr *delta , double eps)
{// faux sur le return...
	if ((dot(Cyl->w, Cyl->vl) * dot(Cyl->v, Cyl->vl) <= 0))
	{
		if (egal(intersect_axe((Cyl), 0), Cyl->r, eps)) // test hauteur, avant tmp
		{
			Cyl->inside = 0;
			return (delta->tmin); // ici le tmin
		}
	}
	else
	{
		if ((dot(Cyl->w11, Cyl->vl) * dot(Cyl->v11, Cyl->vl)) <= 0)
		{
			if (egal(intersect_axe((Cyl),1), Cyl->r, eps))
			{
				Cyl->inside = 1;
				return (delta->tmax);
			}
		}
	}
	Cyl->inside = 2;
	return (-1);
}
*/
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
/*
int main(void)
{// version void
	int			debug = 1;
	int			show = 0;
//	int			inside = 2;

	int			obj_index;
	t_discr		*delta;
	t_closest	*close;

	t_color		back;
	back.r = 0;
	back.g = 0;
	back.b = 0;
	back.tr = 1;

	double uu,vv;
	double		min_dist;
	t_vector	cam, dir, vup,  vp_middle, w1;
	t_ray		ray;
//	t_vector	v_tmp;//
	init_vector(&cam, 0, 3, -1);
	init_vector(&dir, 0, 0, 1);
	init_vector(&vup, 0, 1, 0);// fonctionne pas i??

	t_plan		*p;
	t_plan		*p1;
	t_cyl		*Cyl, *Cyl0;
	t_sphere	*Sph0;
	void		*ptr[3];
	// test dynarr obj..
	t_objet		*objet;
	int			size = 2;

	objet = malloc(sizeof(t_objet)*size);
	if (objet == NULL)
		return (2);


	close = malloc(sizeof(t_closest));
	if (close == NULL)
		return (2);
	delta = malloc(sizeof(t_discr));
	if (delta == NULL)
		return (2);
	Cyl = malloc(sizeof(t_cyl));
	if (Cyl == NULL)
		return (2);
	ptr[0] = Cyl;
	Cyl0 = malloc(sizeof(t_cyl));
	if (Cyl0 == NULL)
		return (2);
	ptr[1] = Cyl0;


	p = malloc(sizeof(t_plan));
	if (p == NULL)
		return (2);


	Sph0 = malloc(sizeof(t_sphere));
	if (Sph0 == NULL)
		return (2);
	p1 = malloc(sizeof(t_plan));
	if (p1 == NULL)
		return (2);

	ptr[2] = p;
//	reinsertion dans objet...
	objet[0].ptr = p;
	objet[0].type = 1;
//	objet[1].ptr = p1;
//	objet[1].type = 1;
	objet[1].ptr = Sph0;
	objet[1].type = 2;

//	objet[0].ptr = Cyl;
//	objet[0].type = 3;
//	objet[1].ptr = Cyl0;
//	objet[1].type = 3;

//	test sphere
	t_vector	S_c;
	init_vector(&S_c, 0, +3, 1);
	init_sphere(Sph0, S_c, 1); // centre et rayon
	Sph0->OC = sub(cam, Sph0->C);
	Sph0->discr_c = norm_2(Sph0->OC) - Sph0->r2;


//	//TEST PLAN ptr
	t_vector p0, n0;
	init_vector(&p0, 0,2,0);
	init_vector(&n0, 1,0,1);

	init_plan(p,p0,unit(n0));
	p->OC = sub(p0, cam); // a tester
//	p->OC = sub(cam, p0);
	p->OCn = dot(p->OC, p->n); // a tester
	p->label = 0;
//  fin init PLAN
	t_vector p01, n01;
	init_vector(&p01, 0, 2,0);
	init_vector(&n01, 0,1,0);
	init_plan(p1,p01, n01);
	p1->OC = sub(p01, cam); // a tester
	p1->OCn = dot(p1->OC, p1->n); // a tester
	p1->label = 1;
//  fin init PLAN



//  TEST CYLINDRE
	t_vector c0,c1,  c_dir, c_dir1;
	init_vector(&c0, 0, 0, 10);
	init_vector(&c_dir, 0, 2, 4);
	init_vector(&c1, 0,0 ,6);
	init_vector(&c_dir1, 0, 2, 4);

	init_cylindre(Cyl, c0, c_dir, (sub(c0, cam))); //
	init2_cylindre(Cyl, cam, 3, 3);
//  valeur objet[1] de faux
	init_cylindre(Cyl0, c1, c_dir1, (sub(c1, cam))); //
	init2_cylindre(Cyl0, cam, 1, 10);

//  Fin init CYLINDRE, semble ok
	vp_middle= add(cam, dir);
	w1 = scalar_prod(sub(cam, vp_middle), 1/norm(sub(cam, vp_middle))) ;

	t_vector U,V;
	U = cross(w1, vup);
	V = cross(U, w1);

	double hor, ver;
	hor = 4.0;
	ver = 4.0;

	//	printf(ENDC"lower left vp =\n");
	t_vector ll = sub(sub(vp_middle, scalar_prod(U, hor/2)), scalar_prod(V, ver/2));;

	// test calcul ray
	t_rgb	**rgb;
	double t1, t2, tp;
	//double	tmp;
	t1 = 0;
	t2 = 0;
	tp = 0;
//	double	tmin, tmax;
	int		cols = VIEWPORT_WIDTH;
	int		rows = VIEWPORT_HEIGHT;
	rgb = create_2d_rgb(cols, rows);
	t_vector aa,bb;
//	int i;
//	int	j;
	double eps = 0.01;

	for (int j = VIEWPORT_HEIGHT - 1; j >= 0; --j)
		for (int i = 0; i < VIEWPORT_WIDTH; ++i)
			background(rgb, back, i, j);
//	double OC;
//	obj_index = 0;
	for (int j = VIEWPORT_HEIGHT - 1; j >= 0; --j)
//	j = 78;
	{//
		for (int i = 0; i < VIEWPORT_WIDTH; ++i)
//		i = 50;
		{
			uu = (double)(i)/(VIEWPORT_WIDTH -1);
			vv = (double)(j)/(VIEWPORT_HEIGHT - 1);
			rgb[i][j].rgb[0]= 0;
			rgb[i][j].rgb[1]= 0;
			rgb[i][j].rgb[2]= 0;
			// ray generator , avant 2
			aa = (scalar_prod(U, hor*uu));
			bb = (scalar_prod(V, ver*vv));
			init_ray(&ray,cam, sub(add(ll, add(aa, bb)), cam));
			init_closest(close);
			//
			obj_index = 0;
			version qui fonctionnait
	 		while (obj_index < 2)
			{// recherche minimum distanc
				get_coeff_cyl(delta, ray, *(t_cyl *)ptr[obj_index]);
				if (delta->discr >= 0)
				{
					quadratic_solution2(delta);
					compute_intersect_cyl(delta, ray, (t_cyl *)ptr[obj_index]);
					// test
					min_dist = cylindre_hit((t_cyl *)ptr[obj_index], delta, eps);
					if (min_dist >= 0 && min_dist < close->tmin)
					{
						close->index = obj_index;
						close->tmin = cylindre_hit((t_cyl *)ptr[obj_index], delta, eps);
						close->type = 3; // cylindre
					//	printf(RED"CLOSE %d\t%lf\n"ENDC, close->index, close->tmin);
					}
				}
				obj_index++;
			}
			// version avec objet..Semble fonctionner.
			while (obj_index < size)
			{// recherche minimum distanc
				if (objet[obj_index].type == 3)
				{
					get_coeff_cyl(delta, ray, *(t_cyl *)objet[obj_index].ptr);
					if (delta->discr >= 0)
					{
						quadratic_solution2(delta);
						compute_intersect_cyl(delta, ray, (t_cyl *)objet[obj_index].ptr);
						min_dist = cylindre_hit((t_cyl *)objet[obj_index].ptr, delta, eps);
						if (min_dist >= 0 && min_dist < close->tmin)
						{
							close->index = obj_index;
							close->tmin = cylindre_hit((t_cyl *)objet[obj_index].ptr, delta, eps);
							close->type = objet[obj_index].type; // cylindre
						}
					}
				}
				if (objet[obj_index].type == 2)
				{// semble fonctionner
					get_coeff_sph(delta, ray, *(t_sphere *)objet[obj_index].ptr);
					if (delta->discr >= 0)
					{
						quadratic_solution2(delta);
						compute_intersect_sph(delta, ray, (t_sphere *)objet[obj_index].ptr);
						min_dist = sphere_hit((t_sphere *)objet[obj_index].ptr, delta,eps);
						if (min_dist >= 0 && min_dist < close->tmin)
						{
							close->index = obj_index;
							close->tmin = sphere_hit((t_sphere *)objet[obj_index].ptr, delta, eps);
							close->type = objet[obj_index].type;
						}
					}
				//	printf("SPHERE\n");
				}
				if (objet[obj_index].type == 1)
				{// a verifier
					compute_intersect_plan(ray, (t_plan *)objet[obj_index].ptr, eps, debug);
					min_dist = plan_hit((t_plan *)objet[obj_index].ptr, eps, debug);
					if (min_dist >= 0 && min_dist < close->tmin)
					{
						close->index = obj_index;
						close->tmin = plan_hit((t_plan *)objet[obj_index].ptr, eps, debug);
						close->type = objet[obj_index].type;
					}
				//	printf("PLAN\n");
				}
				obj_index++;
			}








			// recalcul;
			// a verifier;
			// seg falut
			if (close->index != -1)
			{
				if (objet[close->index].type == 3)
				{// fonctionne
					get_coeff_cyl(delta, ray, *(t_cyl *)ptr[close->index]);
					quadratic_solution2(delta);
					compute_intersect_cyl(delta, ray, (t_cyl *)ptr[close->index]);
					if ((dot((*(t_cyl *)ptr[close->index]).w, (*(t_cyl *)ptr[close->index]).vl) * dot((*(t_cyl *)ptr[close->index]).v, (*(t_cyl *)ptr[close->index]).vl)) <= 0)
					{
						if ( egal(intersect_axe(((t_cyl *)ptr[close->index]), 0), (*(t_cyl *)ptr[close->index]).r, eps)) // test hauteur, avant tmp
						{
						rgb[i][j].rgb[0] = 255;
						}
					}
					else
					{
						if ((dot((*(t_cyl *)ptr[close->index]).w11, (*(t_cyl *)ptr[close->index]).vl) * dot((*(t_cyl *)ptr[close->index]).v11, (*(t_cyl *)ptr[close->index]).vl)) <= 0)
						{
							if (egal(intersect_axe(((t_cyl *)ptr[close->index]),1), (*(t_cyl *)ptr[close->index]).r, eps))
							{
								rgb[i][j].rgb[1] = 255;
							}
						}
					}
				}// fin si cylindre
				if (objet[close->index].type == 2) // sphere
				{// recalcul
					get_coeff_sph(delta, ray, *(t_sphere *)objet[close->index].ptr);
					quadratic_solution2(delta);
					compute_intersect_sph(delta, ray, (t_sphere *)objet[close->index].ptr);
					min_dist = sphere_hit((t_sphere *)objet[close->index].ptr, delta,eps);
					if (min_dist >= 0)
					{
						rgb[i][j].rgb[0] = 125;
						rgb[i][j].rgb[1] = 25;
						rgb[i][j].rgb[2] = 125;
					}
				}
				if (objet[close->index].type == 1)
				{
					t_vector	inters = ((t_plan *)objet[close->index].ptr)->intersect0;
					if ((((long int)(10*inters.vec[2]))%2 == 0 && labs((long int)((10*(inters.vec[0])))) % 2 == 0)
						||(((long int)(10*inters.vec[2]))%2 == 1 && labs((long int)((10*(inters.vec[0])))) % 2 == 1))
					{

						rgb[i][j].rgb[0]= 0;
						rgb[i][j].rgb[1]= 255;
						rgb[i][j].rgb[2]= 0;
					}
					else
					{
						rgb[i][j].rgb[0]= 0;
						rgb[i][j].rgb[1]= 255;
						rgb[i][j].rgb[2]= 255;
					}
					// debug imprime les coorsonnees
					// printf("plan");
				}
			}
		}
	}// fin cylindre intersection

	if (debug == 0 && show == 0)
		print(rgb, VIEWPORT_WIDTH, VIEWPORT_HEIGHT);
	free_2d_rgb(rgb,cols);
	for (int i=0; i < 3; i++)
		free(ptr[i]);
	return (0);
}
*/
