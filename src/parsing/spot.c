/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:08:31 by jsollett          #+#    #+#             */
/*   Updated: 2023/04/27 10:11:31 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	init_spot(t_scene *l, t_scene *p)
{// a continuer
//	int	i;
	int	obj;
	obj = 0;
	while (obj < p->n_obj)
	{
		if (p->forme[obj].id == 1)
		{// plan

		}
		if (p->forme[obj].id == 2)
		{// sphere
		//	(t_sphere *)(p->forme[obj].ptr)->OC =sub(p->l.pos, )
		}
		if (p->forme[obj].id == 3)
		{// cylindre

		}
	l->c.pos = p->l.pos;
		obj++;
	}
	//l->c.vp_middle
}
