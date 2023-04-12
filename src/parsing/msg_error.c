/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:45:13 by grenaud-          #+#    #+#             */
/*   Updated: 2023/04/05 19:27:59 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	message(char *msg, int index)
{
	printf(RED"Error\n");
	if (index == 0)
		printf("%s"ENDC, msg);
	else
		printf("%s %d"ENDC, msg, index);
	wrdestroy();
	exit(0);
}

void	check_fd(int fd, char **argv)
{
	if (fd < 0)
	{
		printf(RED"Error\nNo files found\n"ENDC);
		exit (0);
	}
	if (ft_strnstr(argv[1], ".rt", ft_strlen(argv[1])) == NULL)
	{
		printf(RED"Error\nyou need a .rt extension\n"ENDC);
		exit (0);
	}
}

void	check_struct(t_scene *p)
{
	if (p->a.check_a == 0)
		message("You forgot to add an ambient lightining", 0);
	if (p->c.check_c == 0)
		message("You forgot to add a camera", 0);
	if (p->l.check_l == 0)
		message("You forgot to add a light", 0);
}

void	check_double(double value, int check, int index)
{
	if (check == 1)
		if (value < 0 || value > 1)
			message("Your lightning/brightness ratio has to \
 be between 0.0 and 1.0 on line", index);
	if (check == 2)
		if (value < -1 || value > 1)
			message("Your orientation vector has to \
 be between -1 and 1.0 on line", index);
}

void	check_int(int value, int check, int index)
{
	if (check == 1)
		if (value < 0 || value > 255)
			message("Your RGB values has to \
 be between 0 and 255 on line", index);
	if (check == 2)
		if (value < 0 || value > 180)
			message("Your FOV values has to \
 be between 0 and 180 on line", index);
}
