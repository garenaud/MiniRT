/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vecteur_op2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:27:51 by jsollett          #+#    #+#             */
/*   Updated: 2023/04/12 15:01:30 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

double	dot(t_vector v1, t_vector v2)
{
	double	r;

	r = v1.vec[0] * v2.vec[0] + v1.vec[1] * v2.vec[1] + v1.vec[2] * v2.vec[2];
	return (r);
}

double	norm_2(t_vector v)
{
	return (v.vec[0] * v.vec[0] + v.vec[1] * v.vec[1] + v.vec[2] * v.vec[2]);
}

double	norm(t_vector v)
{
	return (sqrt(norm_2(v)));
}

t_vector	cross(t_vector v1, t_vector v2)
{
	t_vector	res;

	res.vec[0] = v1.vec[1] * v2.vec[2] - v1.vec[2] * v2.vec[1];
	res.vec[1] = v1.vec[2] * v2.vec[0] - v1.vec[0] * v2.vec[2];
	res.vec[2] = v1.vec[0] * v2.vec[1] - v1.vec[1] * v2.vec[0];
	return (res);
}

t_vector	unit(t_vector v)
{
	return (scalar_prod(v, 1 / norm(v)));
}
