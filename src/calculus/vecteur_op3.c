/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vecteur_op3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 09:38:39 by jsollett          #+#    #+#             */
/*   Updated: 2023/04/12 15:01:38 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

t_vector	projection(t_vector from, t_vector to)
{
	return (scalar_prod(to, dot(from, to) / dot(to, to)));
}

t_vector	perpendicular(t_vector from, t_vector to)
{
	t_vector	tmp;

	tmp = projection(from, to);
	return (sub(from, tmp));
}

double	distance(t_vector point, t_vector segment1, t_vector segment2)
{
	t_vector	v;
	t_vector	w;
	double		b;

	v = sub(segment2, segment1);
	w = sub(point, segment1);
	if (dot(w, v) <= 0 && norm(projection(w, v)) > norm(v))
	{
		return (norm(sub(point, segment1)));
	}
	if (dot(v, v) <= dot(w, v))
	{
		return (norm(sub(point, segment2)));
	}
	b = dot(w, v) / dot(v, v);
	return (norm(sub(point, add(segment1, scalar_prod(v, b)))));
}
