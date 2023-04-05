/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listobj_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 21:29:20 by grenaud-          #+#    #+#             */
/*   Updated: 2023/04/05 11:47:24 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_listobj	*init_listobj(t_scene *p)
{
	t_listobj	*new;

	(void) p;
	new = (t_listobj *)wrmalloc(sizeof(t_listobj));
	if (!new)
		return (NULL);
	new->id = wrmalloc(sizeof(char *) * (2 + 1));
	new->id = "cy";
	new->pos.vec[0] = 0;
	new->pos.vec[1] = 0;
	new->pos.vec[2] = 0;
	new->diam = 0;
	new->h = 0;
	new->color.rgb[0] = 0;
	new->color.rgb[1] = 0;
	new->color.rgb[2] = 0;
	new->next = NULL;
	return (new);
}

void	add_to_list(t_listobj **head, t_listobj *new_element)
{
	t_listobj	*current;

	if (*head == NULL)
		*head = new_element;
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = new_element;
	}
	new_element->index = size_stack_obj(*head);
	new_element->next = NULL;
}

size_t	size_stack_obj(t_listobj *top)
{
	size_t	size;

	size = 0;
	while (top != NULL)
	{
		size++;
		top = top->next;
	}
	return (size);
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
		if (obj->id[0] == 'c' && obj->id[1] == 'y')
		{
			printf(GREEN"objet N%d \nid = %s\n"ENDC, obj->index, (obj->id));
			printf(GREEN"coordonne f \t[x %f]\t[y %f]\t[z %f]\n"ENDC, (obj->pos.vec[0]), (obj->pos.vec[1]), (obj->pos.vec[2]));
			printf(GREEN"vect 3d \t[x %f]\t[y %f]\t[z %f]\n"ENDC, (obj->dir.vec[0]), (obj->dir.vec[1]), (obj->dir.vec[2]));
			printf(GREEN"diametre \t[%f] \nhauteur \t[%f]\n"ENDC, (obj->diam), (obj->h));
			printf(GREEN"color \t\t[R %d]\t\t[G %d]\t\t[B %d]\n\n"ENDC, (obj->color.rgb[0]), (obj->color.rgb[1]), (obj->color.rgb[2]));
		}
		if (obj->id[0] == 's' && obj->id[1] == 'p')
		{
			printf(PURP"objet N%d \nid = %s\n"ENDC, obj->index, (obj->id));
			printf(PURP"coordonne \t[x %f]\t[y %f]\t[z %f]\n"ENDC, (obj->pos.vec[0]), (obj->pos.vec[1]), (obj->pos.vec[2]));
			printf(PURP"diametre \t[%f]\n"ENDC, (obj->diam));
			printf(PURP"color \t\t[R %d]\t\t[G %d]\t\t[B %d]\n\n"ENDC, (obj->color.rgb[0]), (obj->color.rgb[1]), (obj->color.rgb[2]));
		}
		if (obj->id[0] == 'p' && obj->id[1] == 'l')
		{
			printf(BLUE"objet N%d \nid = %s\n"ENDC, obj->index, (obj->id));
			printf(BLUE"coordonne f \t[x %f]\t[y %f]\t[z %f]\n"ENDC, (obj->pos.vec[0]), (obj->pos.vec[1]), (obj->pos.vec[2]));
			printf(BLUE"vect 3d \t[x %f]\t[y %f]\t[z %f]\n"ENDC, (obj->dir.vec[0]), (obj->dir.vec[1]), (obj->dir.vec[2]));
			printf(BLUE"color \t\t[R %d]\t\t[G %d]\t\t[B %d]\n\n"ENDC, (obj->color.rgb[0]), (obj->color.rgb[1]), (obj->color.rgb[2]));
		}
		i++;
		obj = obj->next;
	}
	printf(RED"-------------------------------------------------------\n\n"ENDC);
}

void	delete_obj(t_listobj **top)
{
	t_listobj	*tmp;

	if (*top == NULL)
		return ;
	while (*top != NULL)
	{
		tmp = *top;
		*top = (*top)->next;
		if (top)
			wrfree(top);
	}
}
