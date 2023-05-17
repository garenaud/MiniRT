/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 13:36:10 by jsollett          #+#    #+#             */
/*   Updated: 2023/05/17 13:40:50 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

t_vector	*get_intersect(t_scene *p)
{
	if (p->forme[p->closest->index].id == 1)
		return (&((t_plan *)(p->forme[p->closest->index].ptr))->intersect0);
	if (p->forme[p->closest->index].id == 2)
		return (&((t_sphere *)(p->forme[p->closest->index].ptr))->intersect0);
	if (p->forme[p->closest->index].id == 3
		&& ((t_cyl *)(p->forme[p->closest->index].ptr))->inside == 0)
		return (&((t_cyl *)(p->forme[p->closest->index].ptr))->intersect0);
	if (p->forme[p->closest->index].id == 3
		&& ((t_cyl *)(p->forme[p->closest->index].ptr))->inside == 1)
		return (&((t_cyl *)(p->forme[p->closest->index].ptr))->intersect1);
	return (NULL);
}
