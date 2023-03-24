/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 09:50:19 by grenaud-          #+#    #+#             */
/*   Updated: 2023/03/23 20:54:56 by grenaud-         ###   ########.fr       */
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
	char	*test;
	double	num;
	p->c.pos.vec[0] = ascii_to_double(get_numb(line));
	p->c.pos.vec[1] = ascii_to_double(get_numb(line));
	p->c.pos.vec[2] = ascii_to_double(get_numb(line));
	p->c.dir.vec[0] = ascii_to_double(get_numb(line));
	p->c.dir.vec[1] = ascii_to_double(get_numb(line));
	p->c.dir.vec[2] = ascii_to_double(get_numb(line));
	test = get_numb(line);
	num = ascii_to_double(test);
	p->c.fov = num;
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

void	parsing(t_scene *p, char **argv)
{
	int		fd;
	char	*line;
	//(void)	p;
	//int		i = 0;

	fd = open(argv[1], O_RDONLY);
	while (fd)
	{
 		//line = malloc(sizeof(char *) * 1000);
		printf(BLUE"tour de boucle, fd = %d \n"ENDC, fd);
		line = get_next_line(fd);
		if (line == NULL)
			break;
		if (line != NULL)
			printf(RED"line[0] = %c, line = %s\n\n"ENDC, line[0], line);
		if (line[0] == 'A')
			init_ambiant(p, line);
		if (line[0] == 'C')
			init_cam(p, line);
		if (line[0] == 'L')
			init_light(p, line);
/*		if (line[0] == 's' && line[1] == 'p')
			init_sp(p, line);
		if (line[0] == 'p' && line[1] == 'l')
			init_pl(p, line);
		if (line[0] == 'c' && line[1] == 'y')
			init_cy(p, line);*/
		else
		{
			printf("error dans le parsing line[0] = %c\n", line[0]);
			//break;
		}
		//free(line);
	}
	close(fd);
}

char	*get_numb(char *line)
{
	static int		i;
	int				j;
	int				k;
	int				linelen;
	char			*lum = NULL;
	
	i = 1;
	k = 0;
	linelen = ft_strlen(line) - 1;
	while(line[i] != '\0')
	{
		while (line[i] == ' ' && linelen >= i)
			i++;
		if (i == linelen)
			break;
		j = i;
		if (line[i] != ',' && line[i] != ' ')
		{
			while (line[i] != ',' && line[i] != ' ')
				i++;
		}
		if (line[i] == ',')
			line[i] = ' ';
  		lum = malloc(sizeof(char *) * (i - j));
		if (lum == NULL)
			printf(RED"error Malloc!\n"ENDC);
		while (j < i)
		{
			lum[k] = line[j];
			line[j] = ' ';
			k++;
			j++;
			if (j == i)
			{
				lum[k] = '\0';
				return (lum);
			}
		}
		i++;
	}
	return (lum);
}
