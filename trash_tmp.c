
void	print_array(t_scene *p, t_objet *array)
{
	int	i;

	i = 0;
	while (i <= size_stack_obj(p->obj))
	{
		if (array[i].id == 1)
		{
			printf(GREEN"\nplan N%d\n"ENDC, ((t_plan *)array[i].ptr)->index);
			printf("position:\t\t");
			printv(&((t_plan *)array[i].ptr)->C);
			printf("direction:\t\t");
			printv(&((t_plan *)array[i].ptr)->n);
			printf("vecteur cam->position:\t");
			printv(&((t_plan *)array[i].ptr)->OC);
			printf("couleur RGB:\t\t R[%d] G[%d] B[%d]\n", ((t_plan *)array[i].ptr)->color.rgb[0], ((t_plan *)array[i].ptr)->color.rgb[1], ((t_plan *)array[i].ptr)->color.rgb[2]);
		}
		if (array[i].id == 2)
		{
			printf(GREEN"\nsphere N%d\n"ENDC, ((t_sphere *)array[i].ptr)->index);
			printf("position:\t\t");
			printv(&((t_sphere *)array[i].ptr)->C);
			printf("vecteur cam->position:\t");
			printv(&((t_sphere *)array[i].ptr)->OC);
			printf("\nrayon:\t%f\n", ((t_sphere *)array[i].ptr)->r);
			printf("couleur RGB:\t\t R[%d] G[%d] B[%d]\n", ((t_sphere *)array[i].ptr)->color.rgb[0], ((t_sphere *)array[i].ptr)->color.rgb[1], ((t_sphere *)array[i].ptr)->color.rgb[2]);
		}
		if (array[i].id == 3)
		{
			printf(GREEN"\nCylindre N%d\n"ENDC, ((t_cyl *)array[i].ptr)->index);
			printf("position C0:\t\t");
			printv(&((t_cyl *)array[i].ptr)->C0);
			printf("position C1:\t\t");
			printv(&((t_cyl *)array[i].ptr)->C1);
			printf("direction:\t\t");
			printv(&((t_cyl *)array[i].ptr)->dir);
			printf("vecteur cam->position:\t");
			printv(&((t_cyl *)array[i].ptr)->OC);
			printf("couleur RGB:\t\t R[%d] G[%d] B[%d]\n", ((t_cyl *)array[i].ptr)->color.rgb[0], ((t_cyl *)array[i].ptr)->color.rgb[1], ((t_cyl *)array[i].ptr)->color.rgb[2]);
		}
		i++;
	}
}


void	printll_obj(t_listobj *obj)
{
	int	i;

	i = 1;
	printf(RED"\n-------------------------------------------------------"ENDC);
	printf(RED"\nstart obj list\n\n"ENDC);
	if (!obj)
		printf(RED"\nla liste n'existe pas!!!\n"ENDC);
	while (obj)
	{
		if (obj->id == 3)
		{
			printf(GREEN"objet N%d \nid = %d\n"ENDC, obj->index, (obj->id));
			printf(GREEN"coordonne f \t[x %f]\t[y %f]\t[z %f]\n"ENDC, (obj->pos.vec[0]), (obj->pos.vec[1]), (obj->pos.vec[2]));
			printf(GREEN"vect 3d \t[x %f]\t[y %f]\t[z %f]\n"ENDC, (obj->dir.vec[0]), (obj->dir.vec[1]), (obj->dir.vec[2]));
			printf(GREEN"diametre \t[%f] \nhauteur \t[%f]\n"ENDC, (obj->r), (obj->h));
			printf(GREEN"color \t\t[R %d]\t\t[G %d]\t\t[B %d]\n\n"ENDC, (obj->color.rgb[0]), (obj->color.rgb[1]), (obj->color.rgb[2]));
		}
		if (obj->id == 2)
		{
			printf(PURP"objet N%d \nid = %d\n"ENDC, obj->index, (obj->id));
			printf(PURP"coordonne \t[x %f]\t[y %f]\t[z %f]\n"ENDC, (obj->pos.vec[0]), (obj->pos.vec[1]), (obj->pos.vec[2]));
			printf(PURP"diametre \t[%f]\n"ENDC, (obj->r));
			printf(PURP"color \t\t[R %d]\t\t[G %d]\t\t[B %d]\n\n"ENDC, (obj->color.rgb[0]), (obj->color.rgb[1]), (obj->color.rgb[2]));
		}
		if (obj->id == 1)
		{
			printf(BLUE"objet N%d \nid = %d\n"ENDC, obj->index, (obj->id));
			printf(BLUE"coordonne f \t[x %f]\t[y %f]\t[z %f]\n"ENDC, (obj->pos.vec[0]), (obj->pos.vec[1]), (obj->pos.vec[2]));
			printf(BLUE"vect 3d \t[x %f]\t[y %f]\t[z %f]\n"ENDC, (obj->dir.vec[0]), (obj->dir.vec[1]), (obj->dir.vec[2]));
			printf(BLUE"color \t\t[R %d]\t\t[G %d]\t\t[B %d]\n\n"ENDC, (obj->color.rgb[0]), (obj->color.rgb[1]), (obj->color.rgb[2]));
		}
		i++;
		obj = obj->next;
	}
	printf(RED"-------------------------------------------------------\n\n"ENDC);
}
