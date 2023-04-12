/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:46:05 by jsollett          #+#    #+#             */
/*   Updated: 2023/04/12 15:01:14 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

int	egal(double lhs, double rhs, double tolerance)
{
	if ((lhs > rhs - tolerance) && (lhs < rhs + tolerance))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

int	not_egal(double lhs, double rhs, double tolerance)
{
	if (egal(lhs, rhs, tolerance) == 1)
		return (0);
	else
		return (1);
}
