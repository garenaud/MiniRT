/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsollett <jsollett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:14:59 by jsollett          #+#    #+#             */
/*   Updated: 2023/03/22 11:15:14 by jsollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../miniRT.h"

void	printv(t_vector *v)
{
	printf(" %f %f %f \n", v->vec[0], v->vec[1], v->vec[2]);
}

void	print(t_rgb **a, int col, int row)
{
	int	i;
	int	j;

	printf("P3\n");
	printf("%d", col);
	printf(" ");
	printf("%d", row);
	printf("\n255\n");
	j = row - 1;
	while (j >= 0)
	{
		i = 0;
		while (i < col)
		{
			printf("%d %d %d \n ", a[i][j].rgb[0],
				a[i][j].rgb[1], a[i][j].rgb[2]);
			++i;
		}
	--j;
	}
}
