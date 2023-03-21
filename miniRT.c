/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:04:14 by grenaud-          #+#    #+#             */
/*   Updated: 2023/03/21 13:53:03 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* int	main(int ac, char **av)
{
 	double	number;
	double test = 0.000000001;

	number = ascii_to_double(av[1]);
	printf("ac = %d en str: %s et en double: %lf test: %lf", ac, av[1], number, test);
	return (0);
} */

int		main(int argc, char **argv)
{
	t_scene	*p;
	(void) argc;
	
 	p = NULL;
	//int		fd;
	//char	*line;
	(void) p;

	//fd = open(argv[1], O_RDONLY);
	//line = malloc(sizeof(char *) * (ft_strlen(get_next_line(fd))));
	//line = get_next_line(fd);
	//printf("line est = %s et fd = %d", line, fd);
/*	p->a.lum = 0;
	p->a.color.rgb[0] = 0;
	p->a.color.rgb[1] = 0;
	p->a.color.rgb[2] = 0; */
	
	readfd(p, argv);
	//printf("lumiere = %f, R = %d, G = %d, B = %d", p->a.lum, p->a.color.rgb[0], p->a.color.rgb[1], p->a.color.rgb[2]);
	return (0);
}
