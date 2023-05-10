/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   progressbar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:30:03 by grenaud-          #+#    #+#             */
/*   Updated: 2023/05/09 14:58:14 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	console_info_processing(double perc)
{
	printf(GREEN"Processing : %*.2lf%%\r"ENDC, 6, perc * 100);
	fflush(stdout);
}

void	screen_info_processing(t_scene *p)
{
	double	perc;

	p->process += 1;
	perc = ((double)p->process / 1000);
	console_info_processing(perc);
	if (p->process > VIEWPORT_HEIGHT - 1)
		p->process = 0;
}

double	get_duration(void)
{
	static struct timeval	old_t = {0};
	struct timeval			t;
	float					sec;

	gettimeofday(&t, NULL);
	sec = (float)(t.tv_sec - old_t.tv_sec)
		+ ((float)(t.tv_usec - old_t.tv_usec) / 1000000);
	old_t = t;
	return (sec);
}
