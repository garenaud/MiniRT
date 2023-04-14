/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_obj_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 18:32:48 by grenaud-          #+#    #+#             */
/*   Updated: 2023/04/14 12:01:59 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	push_cy(t_scene *p, int index)
{
	t_listobj	*tmp;

	tmp = init_listobj();
	if (!tmp)
		return ;
	tmp->id = 3;
	tmp->pos.vec[0] = ascii_to_double(get_numb(p, index), 0, index);
	tmp->pos.vec[1] = ascii_to_double(get_numb(p, index), 0, index);
	tmp->pos.vec[2] = ascii_to_double(get_numb(p, index), 0, index);
	tmp->dir.vec[0] = ascii_to_double(get_numb(p, index), 2, index);
	tmp->dir.vec[1] = ascii_to_double(get_numb(p, index), 2, index);
	tmp->dir.vec[2] = ascii_to_double(get_numb(p, index), 2, index);
	tmp->r = ascii_to_double(get_numb(p, index), 0, index);
	tmp->h = ascii_to_double(get_numb(p, index), 0, index);
	tmp->color.rgb[0] = atoi_c(get_numb(p, index), 1, index);
	tmp->color.rgb[1] = atoi_c(get_numb(p, index), 1, index);
	tmp->color.rgb[2] = atoi_c(get_numb(p, index), 1, index);
	tmp->next = NULL;
	add_to_list(&p->obj, tmp);
}

void	push_sp(t_scene *p, int index)
{
	t_listobj	*tmp;

	tmp = init_listobj();
	if (!tmp)
		return ;
	tmp->id = 2;
	tmp->pos.vec[0] = ascii_to_double(get_numb(p, index), 0, index);
	tmp->pos.vec[1] = ascii_to_double(get_numb(p, index), 0, index);
	tmp->pos.vec[2] = ascii_to_double(get_numb(p, index), 0, index);
	tmp->r = ascii_to_double(get_numb(p, index), 0, index);
	tmp->color.rgb[0] = atoi_c(get_numb(p, index), 1, index);
	tmp->color.rgb[1] = atoi_c(get_numb(p, index), 1, index);
	tmp->color.rgb[2] = atoi_c(get_numb(p, index), 1, index);
	tmp->next = NULL;
	add_to_list(&p->obj, tmp);
}

void	push_pl(t_scene *p, int index)
{
	t_listobj	*tmp;

	tmp = init_listobj();
	if (!tmp)
		return ;
	tmp->id = 1;
	tmp->pos.vec[0] = ascii_to_double(get_numb(p, index), 0, index);
	tmp->pos.vec[1] = ascii_to_double(get_numb(p, index), 0, index);
	tmp->pos.vec[2] = ascii_to_double(get_numb(p, index), 0, index);
	tmp->dir.vec[0] = ascii_to_double(get_numb(p, index), 2, index);
	tmp->dir.vec[1] = ascii_to_double(get_numb(p, index), 2, index);
	tmp->dir.vec[2] = ascii_to_double(get_numb(p, index), 2, index);
	tmp->color.rgb[0] = atoi_c(get_numb(p, index), 1, index);
	tmp->color.rgb[1] = atoi_c(get_numb(p, index), 1, index);
	tmp->color.rgb[2] = atoi_c(get_numb(p, index), 1, index);
	tmp->next = NULL;
	add_to_list(&p->obj, tmp);
}
