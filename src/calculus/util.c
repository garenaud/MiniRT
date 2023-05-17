/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:46:05 by jsollett          #+#    #+#             */
/*   Updated: 2023/05/16 10:58:04 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

int	egal(double lhs, double rhs, double tolerance)
{
	if ((lhs > rhs - tolerance) && (lhs < rhs + tolerance))
		return (1);
	else
		return (0);
}

int	not_egal(double lhs, double rhs, double tolerance)
{
	if (egal(lhs, rhs, tolerance) == 1)
		return (0);
	else
		return (1);
}

int	egal_v(t_vector lhs, t_vector rhs, double tolerance)
{
	if (egal(lhs.vec[0], rhs.vec[0], tolerance) == 1
		&& egal(lhs.vec[1], rhs.vec[1], tolerance) == 1
		&& egal(lhs.vec[2], rhs.vec[2], tolerance) == 1)
		return (1);
	else
		return (0);
}
