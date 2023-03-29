/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_data_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:42:55 by grenaud-          #+#    #+#             */
/*   Updated: 2023/03/29 16:24:56 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	init_ambiant(t_scene *p, char *line)
{
	p->a.lum = ascii_to_double(get_numb(line));
	p->a.color.rgb[0] = ft_atoi(get_numb(line));
	p->a.color.rgb[1] = ft_atoi(get_numb(line));
	p->a.color.rgb[2] = ft_atoi(get_numb(line));
	free(line);
}

void	init_cam(t_scene *p, char *line)
{
	p->c.pos.vec[0] = ascii_to_double(get_numb(line));
	p->c.pos.vec[1] = ascii_to_double(get_numb(line));
	p->c.pos.vec[2] = ascii_to_double(get_numb(line));
	p->c.dir.vec[0] = ascii_to_double(get_numb(line));
	p->c.dir.vec[1] = ascii_to_double(get_numb(line));
	p->c.dir.vec[2] = ascii_to_double(get_numb(line));
	p->c.fov = ascii_to_double(get_numb(line));
	free(line);
}

void	init_light(t_scene *p, char *line)
{
	p->l.pos.vec[0] = ascii_to_double(get_numb(line));
	p->l.pos.vec[1] = ascii_to_double(get_numb(line));
	p->l.pos.vec[2] = ascii_to_double(get_numb(line));
	p->l.lum = ascii_to_double(get_numb(line));
	p->l.color.rgb[0] = ft_atoi(get_numb(line));
	p->l.color.rgb[1] = ft_atoi(get_numb(line));
	p->l.color.rgb[2] = ft_atoi(get_numb(line));
	free(line);
}
