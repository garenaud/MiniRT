/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listobj_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 21:29:20 by grenaud-          #+#    #+#             */
/*   Updated: 2023/05/16 12:02:22 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

t_listobj	*init_listobj(void)
{
	t_listobj	*new;

	new = (t_listobj *)wrmalloc(sizeof(t_listobj));
	if (!new)
		return (NULL);
	new->index = 0;
	new->id = 0;
	new->pos.vec[0] = 0;
	new->pos.vec[1] = 0;
	new->pos.vec[2] = 0;
	new->r = 0;
	new->h = 0;
	new->color.rgb[0] = 0;
	new->color.rgb[1] = 0;
	new->color.rgb[2] = 0;
	new->next = NULL;
	return (new);
}

t_listobj	*getobj(t_listobj *top, int index)
{
	t_listobj	*tmp;

	tmp = (t_listobj *)wrmalloc(sizeof(t_listobj));
	if (!tmp)
		exit (-1);
	if (index > size_stack_obj(top))
		return (NULL);
	else
	{
		while (index != top->index)
			top = top->next;
		tmp->index = top->index;
		tmp->id = top->id;
		tmp->pos.vec[0] = top->pos.vec[0];
		tmp->pos.vec[1] = top->pos.vec[1];
		tmp->pos.vec[2] = top->pos.vec[2];
		tmp->r = top->r;
		tmp->h = top->h;
		tmp->color.rgb[0] = top->color.rgb[0];
		tmp->color.rgb[1] = top->color.rgb[1];
		tmp->color.rgb[2] = top->color.rgb[2];
		tmp->next = NULL;
		return (tmp);
	}
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

int	size_stack_obj(t_listobj *top)
{
	int	size;

	size = 0;
	while (top != NULL)
	{
		size++;
		top = top->next;
	}
	return (size);
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
		if (tmp)
			wrfree(tmp);
	}
}
