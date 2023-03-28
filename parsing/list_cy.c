/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 21:29:20 by grenaud-          #+#    #+#             */
/*   Updated: 2023/03/24 14:46:01 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_listobj	*init_listobj()
{
	t_listobj	*new;
	new = (t_listobj *)malloc(sizeof(t_listobj));
	if (!new)
		return (NULL);
	new->id = (char *)malloc(sizeof(char *) * (2 + 1));
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

void add_to_list(t_listobj **head, t_listobj *new_element) 
{
    t_listobj	*current;

	if (*head == NULL)
        *head = new_element;
    else {
        current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_element;
    }
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
	printf(BOLDRED"\nstart obj list\n"ENDC);
	if (!obj)
		printf(RED"\nla liste n'existe pas!!!\n"ENDC);
	while (obj)
	{
		if (obj->id[0] == 'c' && obj->id[1] == 'y')
		{
			printf(GREEN"\n\nid = %s\n"ENDC, (obj->id));
			printf(GREEN"coordonne f [x %f][y %f][z %f]\n"ENDC, (obj->pos.vec[0]), (obj->pos.vec[1]), (obj->pos.vec[2]));
			printf(GREEN"vect orientation 3d [x %f][y %f][z %f]\n"ENDC, (obj->dir.vec[0]), (obj->dir.vec[1]), (obj->dir.vec[2]));
			printf(GREEN"diametre [%f] hauteur [%f]\n"ENDC, (obj->diam), (obj->h));
			printf(GREEN"color [R %d][G %d][B %d]\n\n"ENDC, (obj->color.rgb[0]), (obj->color.rgb[1]), (obj->color.rgb[2]));
		}
		if (obj->id[0] == 's' && obj->id[1] == 'p')
		{
			printf(PURP"id = %s\n"ENDC, (obj->id));
			printf(PURP"coordonne [x %f][y %f][z %f]\n"ENDC, (obj->pos.vec[0]), (obj->pos.vec[1]), (obj->pos.vec[2]));
			printf(PURP"diametre [%f]\n"ENDC, (obj->diam));
			printf(PURP"color [R %d][G %d][B %d]\n\n"ENDC, (obj->color.rgb[0]), (obj->color.rgb[1]), (obj->color.rgb[2]));
		}
		if (obj->id[0] == 'p' && obj->id[1] == 'l')
		{
			printf(BLUE"id = %s\n"ENDC, (obj->id));
			printf(BLUE"coordonne f [x %f][y %f][z %f]\n"ENDC, (obj->pos.vec[0]), (obj->pos.vec[1]), (obj->pos.vec[2]));
			printf(BLUE"vect orientation 3d [x %f][y %f][z %f]\n"ENDC, (obj->dir.vec[0]), (obj->dir.vec[1]), (obj->dir.vec[2]));
			printf(BLUE"color [R %d][G %d][B %d]\n\n"ENDC, (obj->color.rgb[0]), (obj->color.rgb[1]), (obj->color.rgb[2]));
		}	
		obj = obj->next;
	}
	printf("-->[end]\n");
}
/* 
void	push(t_list **top, char *item)
{
	t_list	*tmp;

	tmp = malloc(sizeof(t_list));
	if (!tmp)
		return ;
	tmp->data = ft_strdup(item);
	tmp->next = *top;
	*top = tmp;
} */

void	push_cy(t_scene *p, char *line)
{
	char		*id;
	t_listobj	*tmp;

	id = "cy";
	tmp = init_listobj();
	if (!tmp)
		return ;
	tmp->id = ft_strdup(id);
	tmp->pos.vec[0] = ascii_to_double(get_numb(line));
	tmp->pos.vec[1] = ascii_to_double(get_numb(line));
	tmp->pos.vec[2] = ascii_to_double(get_numb(line));
	tmp->dir.vec[0] = ascii_to_double(get_numb(line));
	tmp->dir.vec[1] = ascii_to_double(get_numb(line));
	tmp->dir.vec[2] = ascii_to_double(get_numb(line));
	tmp->diam = ascii_to_double(get_numb(line));
	tmp->h = ascii_to_double(get_numb(line));
	tmp->color.rgb[0] = ft_atoi(get_numb(line));
	tmp->color.rgb[1] = ft_atoi(get_numb(line));
	tmp->color.rgb[2] = ft_atoi(get_numb(line));
	tmp->next = NULL;
	add_to_list(&p->obj, tmp);
/* 	tmp->next = *top;
	*top = tmp; */
	free(line);
}

void	push_sp(t_scene *p, char *line)
{
	char		*id;
	t_listobj	*tmp;

	id = "sp";
	tmp = init_listobj();
	if (!tmp)
		return ;
	tmp->id = ft_strdup(id);
	tmp->pos.vec[0] = ascii_to_double(get_numb(line));
	tmp->pos.vec[1] = ascii_to_double(get_numb(line));
	tmp->pos.vec[2] = ascii_to_double(get_numb(line));
	tmp->diam = ascii_to_double(get_numb(line));
	tmp->color.rgb[0] = ft_atoi(get_numb(line));
	tmp->color.rgb[1] = ft_atoi(get_numb(line));
	tmp->color.rgb[2] = ft_atoi(get_numb(line));
	tmp->next = NULL;
	add_to_list(&p->obj, tmp);
	free(line);
}

void	push_pl(t_scene *p, char *line)
{
	char	*id;
	t_listobj	*tmp;

	id = "pl";
	tmp = init_listobj();
	if (!tmp)
		return ;
	tmp->id = ft_strdup(id);
	tmp->pos.vec[0] = ascii_to_double(get_numb(line));
	tmp->pos.vec[1] = ascii_to_double(get_numb(line));
	tmp->pos.vec[2] = ascii_to_double(get_numb(line));
	tmp->dir.vec[0] = ascii_to_double(get_numb(line));
	tmp->dir.vec[1] = ascii_to_double(get_numb(line));
	tmp->dir.vec[2] = ascii_to_double(get_numb(line));
	tmp->color.rgb[0] = ft_atoi(get_numb(line));
	tmp->color.rgb[1] = ft_atoi(get_numb(line));
	tmp->color.rgb[2] = ft_atoi(get_numb(line));
	tmp->next = NULL;
	add_to_list(&p->obj, tmp);
	free(line);
}
