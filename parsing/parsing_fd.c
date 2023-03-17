/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 09:50:19 by grenaud-          #+#    #+#             */
/*   Updated: 2023/03/17 11:41:44 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	create_map_line(t_readfd *test, char **argv)
{
	int		fd;
	int		i;
	int		j;

	fd = open(argv[1], O_RDONLY);
	i = 0;
	j = 0;
	test->fdcontent = ;
	while (fd)
	{
		game->map[i] = get_next_line(fd);
		while (j < (game->size_x / SIZE) + 1)
		{
			check_map_endline(game, i, j);
			j++;
		}
		i++;
	}
	create_floor(game);
	create_map(*game);
	close(fd);
}