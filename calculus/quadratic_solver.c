/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadratic_solver.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:24:49 by jsollett          #+#    #+#             */
/*   Updated: 2023/03/30 14:25:10 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../miniRT.h"

double	discr(double a, double b, double c)
{
	return (b * b - 4 * a * c);
}

void	test_quad_sol(t_discr *d)
{
	if (d->t2 < d->t1 && d->t2 >= 0)
	{
		d->tmin = d->t2;
		d->tmax = d->t1;
	}
	if (d->t2 < 0 && d->t1 >= 0)
	{
		d->tmin = d->t1;
		d->tmax = d->t2;
	}
	if (d->t1 < 0 && d->t2 < 0)
	{
		d->tmin = 0;
		d->tmax = 0;
	}
}

void	quadratic_solution(t_discr *d, double a, double b, double c)
{
	d->discr = discr(a, b, c);
	if (d->discr == 0)
	{
		d->t1 = -b / (2 * a);
		d->t2 = d->t1;
		d->tmin = d->t1;
		d->tmax = d->t1;
	}
	else
	{
		d->t1 = (-b + sqrt(d->discr)) / (2 * a);
		d->t2 = (-b - sqrt(d->discr)) / (2 * a);
		test_quad_sol(d);
	}
}
