/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:45:13 by grenaud-          #+#    #+#             */
/*   Updated: 2023/04/04 18:06:24 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	message(char *msg, int index)
{
	printf(RED"Error\n");
	if (index == 0)
		printf("%s"ENDC, msg);
	else
		printf("%s %d"ENDC, msg, index);
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
