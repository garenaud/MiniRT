/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 11:22:38 by grenaud-          #+#    #+#             */
/*   Updated: 2023/05/16 12:03:11 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

t_plan	*create_plan(void)
{
	t_plan	*plan;

	plan = wrmalloc(sizeof(t_plan));
	if (plan == NULL)
		wrdestroy();
	return (plan);
}

t_sphere	*create_sp(void)
{
	t_sphere	*sphere;

	sphere = wrmalloc(sizeof(t_sphere));
	if (sphere == NULL)
		wrdestroy();
	return (sphere);
}

t_cyl	*create_cy(void)
{
	t_cyl	*cyl;

	cyl = wrmalloc(sizeof(t_cyl));
	if (cyl == NULL)
		wrdestroy();
	return (cyl);
}

t_discr	*create_discriminant(void)
{
	t_discr	*ds;

	ds = wrmalloc(sizeof(t_discr));
	if (ds == NULL)
		wrdestroy();
	return (ds);
}

t_closest	*create_closest(void)
{
	t_closest	*clos;

	clos = wrmalloc(sizeof(t_closest));
	if (clos == NULL)
		wrdestroy();
	return (clos);
}
