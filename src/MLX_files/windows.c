/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:03:44 by grenaud-          #+#    #+#             */
/*   Updated: 2023/04/06 14:36:55 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	destroy_window(t_game *game)
{
	ft_printf(BOLDRED"You ended the game\n"ENDC, game);
	free_and_exit(game);
	exit (0);
}

void	free_and_exit(t_game *game)
{
	int	i;

	i = 0;
	mlx_destroy_image(game->mlx, game->image.char_down.mlx_img);
	mlx_destroy_image(game->mlx, game->image.background.mlx_img);
	mlx_destroy_image(game->mlx, game->image.char_left.mlx_img);
	mlx_destroy_image(game->mlx, game->image.char_right.mlx_img);
	mlx_destroy_image(game->mlx, game->image.char_up.mlx_img);
	mlx_destroy_image(game->mlx, game->image.exit.mlx_img);
	mlx_destroy_image(game->mlx, game->image.coin.mlx_img);
	mlx_destroy_image(game->mlx, game->image.wall.mlx_img);
	mlx_destroy_window(game->mlx, game->window);
	while (i < ((game->size_y / 48) + 1))
	{
		free(game->map[i]);
		i++;
	}
	free(game->map);
	exit(0);
}
