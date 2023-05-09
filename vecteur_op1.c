/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vecteur_op1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:27:57 by jsollett          #+#    #+#             */
/*   Updated: 2023/03/22 11:27:58 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "miniRT.h"

t_vector	reverse(t_vector v)
{
	t_vector	res;

	res.vec[0] = -v.vec[0];
	res.vec[1] = -v.vec[1];
	res.vec[2] = -v.vec[2];
	return (res);
}

t_vector	add(t_vector v1, t_vector v2)
{
	t_vector	res;

	res.vec[0] = v1.vec[0] + v2.vec[0];
	res.vec[1] = v1.vec[1] + v2.vec[1];
	res.vec[2] = v1.vec[2] + v2.vec[2];
	return (res);
}

t_vector	sub(t_vector v1, t_vector v2)
{
	t_vector	res;

	res.vec[0] = v1.vec[0] - v2.vec[0];
	res.vec[1] = v1.vec[1] - v2.vec[1];
	res.vec[2] = v1.vec[2] - v2.vec[2];
	return (res);
}

t_vector	scalar_prod(t_vector v, double t)
{
	t_vector	res;

	res.vec[0] = t * v.vec[0];
	res.vec[1] = t * v.vec[1];
	res.vec[2] = t * v.vec[2];
	return (res);
}
