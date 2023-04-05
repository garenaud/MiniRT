/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_obj_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 18:32:48 by grenaud-          #+#    #+#             */
/*   Updated: 2023/04/05 16:30:22 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	push_cy(t_scene *p, char *line, int index)
{
	char		*id;
	t_listobj	*tmp;

	id = "cy";
	tmp = init_listobj(p);
	if (!tmp)
		return ;
	tmp->id = ft_strdup(id);
	tmp->pos.vec[0] = ascii_to_double(get_numb(line, index), 0, index);
	tmp->pos.vec[1] = ascii_to_double(get_numb(line, index), 0, index);
	tmp->pos.vec[2] = ascii_to_double(get_numb(line, index), 0, index);
	tmp->dir.vec[0] = ascii_to_double(get_numb(line, index), 2, index);
	tmp->dir.vec[1] = ascii_to_double(get_numb(line, index), 2, index);
	tmp->dir.vec[2] = ascii_to_double(get_numb(line, index), 2, index);
	tmp->diam = ascii_to_double(get_numb(line, index), 0, index);
	tmp->h = ascii_to_double(get_numb(line, index), 0, index);
	tmp->color.rgb[0] = ft_atoi_check(get_numb(line, index), 1, index);
	tmp->color.rgb[1] = ft_atoi_check(get_numb(line, index), 1, index);
	tmp->color.rgb[2] = ft_atoi_check(get_numb(line, index), 1, index);
	tmp->next = NULL;
	add_to_list(&p->obj, tmp);
}

void	push_sp(t_scene *p, char *line, int index)
{
	char		*id;
	t_listobj	*tmp;

	id = "sp";
	tmp = init_listobj(p);
	if (!tmp)
		return ;
	tmp->id = ft_strdup(id);
	tmp->pos.vec[0] = ascii_to_double(get_numb(line, index), 0, index);
	tmp->pos.vec[1] = ascii_to_double(get_numb(line, index), 0, index);
	tmp->pos.vec[2] = ascii_to_double(get_numb(line, index), 0, index);
	tmp->diam = ascii_to_double(get_numb(line, index), 0, index);
	tmp->color.rgb[0] = ft_atoi_check(get_numb(line, index), 1, index);
	tmp->color.rgb[1] = ft_atoi_check(get_numb(line, index), 1, index);
	tmp->color.rgb[2] = ft_atoi_check(get_numb(line, index), 1, index);
	tmp->next = NULL;
	add_to_list(&p->obj, tmp);
}

void	push_pl(t_scene *p, char *line, int index)
{
	char		*id;
	t_listobj	*tmp;

	id = "pl";
	tmp = init_listobj(p);
	if (!tmp)
		return ;
	tmp->id = ft_strdup(id);
	tmp->pos.vec[0] = ascii_to_double(get_numb(line, index), 0, index);
	tmp->pos.vec[1] = ascii_to_double(get_numb(line, index), 0, index);
	tmp->pos.vec[2] = ascii_to_double(get_numb(line, index), 0, index);
	tmp->dir.vec[0] = ascii_to_double(get_numb(line, index), 2, index);
	tmp->dir.vec[1] = ascii_to_double(get_numb(line, index), 2, index);
	tmp->dir.vec[2] = ascii_to_double(get_numb(line, index), 2, index);
	tmp->color.rgb[0] = ft_atoi_check(get_numb(line, index), 1, index);
	tmp->color.rgb[1] = ft_atoi_check(get_numb(line, index), 1, index);
	tmp->color.rgb[2] = ft_atoi_check(get_numb(line, index), 1, index);
	tmp->next = NULL;
	add_to_list(&p->obj, tmp);
}
