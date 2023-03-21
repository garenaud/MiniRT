/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:42:55 by grenaud-          #+#    #+#             */
/*   Updated: 2023/03/20 15:45:28 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	ft_window_size(t_game *game, char **argv)
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		ft_printf(RED"Error\nNo files found\n"ENDC);
		exit (0);
	}
	if (ft_strnstr(argv[1], ".rt", ft_strlen(argv[1])) == NULL)
	{
		ft_printf(RED"Error\nyou need a .rt extension\n"ENDC);
		exit (0);
	}
	game->size_x = (ft_line_length(fd) * 48);
	game->size_y = (ft_count_lines(fd) * 48);
}