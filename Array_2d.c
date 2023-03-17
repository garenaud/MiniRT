/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array_2d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 10:38:24 by jsollett          #+#    #+#             */
/*   Updated: 2023/03/17 10:38:33 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_rgb	**create_2d_rgb(int cols, int rows)
{
	t_rgb	**rgb;
	int		index;

	index = 0;
	rgb = malloc(cols * sizeof(*rgb));
	if (!rgb)
	{
		return (NULL);
	}
	while (index < cols)
	{
		rgb[index] = malloc(rows * sizeof(*rgb[index]));
		if (!rgb[index])
		{
			return (NULL);
		}
		index++;
	}
	return (rgb);
}

t_vector	**create_2d_vector(int cols, int rows)
{
	t_vector	**vec;
	int			index;

	index = 0;
	vec = malloc(cols * sizeof(*vec));
	if (!vec)
	{
		return (NULL);
	}
	while (index < cols)
	{
		vec[index] = malloc(rows * sizeof(*vec[index]));
		if (!vec[index])
		{
			return (NULL);
		}
		index++;
	}
	return (vec);
}

void	free_2d_rgb(t_rgb **rgb, int cols)
{
	int	i;

	i = 0;
	while (i < cols)
	{
		free(rgb[i]);
		i++;
	}
	free(rgb);
}

void	free_2d_vector(t_vector **vec, int cols)
{
	int	i;

	i = 0;
	while (i < cols)
	{
		free(vec[i]);
		i++;
	}
	free(vec);
}
