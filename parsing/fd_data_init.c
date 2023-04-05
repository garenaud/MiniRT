/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_data_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:42:55 by grenaud-          #+#    #+#             */
/*   Updated: 2023/04/05 17:24:58 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	init_ambiant(t_scene *p, char *line, int index)
{
	if (p->a.check_a == 0)
	{
		printf("line = %s ", line);
		p->a.lum = ascii_to_double(get_numb(line, index), 1, index);
		printf("p->a.lum = %f\n", p->a.lum);
		p->a.color.rgb[0] = ft_atoi_check(get_numb(line, index), 1, index);
		p->a.color.rgb[1] = ft_atoi_check(get_numb(line, index), 1, index);
		p->a.color.rgb[2] = ft_atoi_check(get_numb(line, index), 1, index);
		p->a.check_a = 1;
	}
	else if (p->a.check_a > 0)
		message("Only one ambient lightning is allowed", 0);
}

void	init_cam(t_scene *p, char *line, int index)
{
	if (p->c.check_c == 0)
	{
		p->c.pos.vec[0] = ascii_to_double(get_numb(line, index), 0, index);
		p->c.pos.vec[1] = ascii_to_double(get_numb(line, index), 0, index);
		p->c.pos.vec[2] = ascii_to_double(get_numb(line, index), 0, index);
		p->c.dir.vec[0] = ascii_to_double(get_numb(line, index), 2, index);
		p->c.dir.vec[1] = ascii_to_double(get_numb(line, index), 2, index);
		p->c.dir.vec[2] = ascii_to_double(get_numb(line, index), 2, index);
		p->c.fov = ft_atoi_check(get_numb(line, index), 2, index);
		p->c.check_c = 1;
	}
	else
		message("Only one camera is allowed", 0);
}

void	init_light(t_scene *p, char *line, int index)
{
	if (p->l.check_l == 0)
	{
		p->l.pos.vec[0] = ascii_to_double(get_numb(line, index), 0, index);
		p->l.pos.vec[1] = ascii_to_double(get_numb(line, index), 0, index);
		p->l.pos.vec[2] = ascii_to_double(get_numb(line, index), 0, index);
		p->l.lum = ascii_to_double(get_numb(line, index), 1, index);
		p->l.color.rgb[0] = ft_atoi_check(get_numb(line, index), 1, index);
		p->l.color.rgb[1] = ft_atoi_check(get_numb(line, index), 1, index);
		p->l.color.rgb[2] = ft_atoi_check(get_numb(line, index), 1, index);
		p->l.check_l = 1;
	}
	else
		message("Only one light is allowed", 0);
}
