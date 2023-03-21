/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 09:50:19 by grenaud-          #+#    #+#             */
/*   Updated: 2023/03/21 16:27:45 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	readfd(t_scene *p, char **argv)
{
	int		fd;
	char	*line;
	char	*ret;
	(void) p;

	fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	printf("\nline est = %s\n", line);
	ret = get_numb(line);
	//ret = malloc(sizeof(char *) * 100);
/*  	while (fd)
	{
		//line = malloc(sizeof(char *) * (ft_strlen(get_next_line(fd))));
		line = get_next_line(fd);
		printf("\nline est = %s\n", line);
		//parsing(p, line);
		//printf("after line est = %s\n", line);
		ret = get_numb(line);
		//printf("ret = %s\n", ret);
		//free(&line);
	} */
	close(fd);
}

void	parsing(t_scene *p, char *line)
{
	int	i;
	(void) p;

	i = 0;
	printf("dans parsing line = %s \n", line);
/* 	while (line[i])
	{ */
		if (line[0] == 'A')
			get_numb(line);
			//init_ambiant(p, line);
/* 		if (line[0] == 'C')
			init_cam(p, line);
		if (line[0] == 'L')
			init_light(p, line);
		if (line[0] == 's' && line[1] == 'p')
			init_sp(p, line);
		if (line[0] == 'p' && line[1] == 'l')
			init_pl(p, line);
		if (line[0] == 'c' && line[1] == 'y')
			init_cy(p, line); */
		else
			printf("error dans le parsing\n");
		//i++;
	//}
}

char	*get_numb(char *line)
{
	int		i;
	int		j;
	int		k;
	int		len;
	int		linelen;
	char	*lum = NULL;
	
	i = 1;
	j = 0;
	k = 0;
	len = 0;
	linelen = 0;
	//lum = malloc(sizeof(char *) * 100);
	linelen = ft_strlen(line);
	printf(RED"dans get_numb line = %s linelen = %d\n"ENDC, line, linelen);
	//lum[3] = NULL;
	while(i < linelen)
	{
		printf("i = %d get_numb = %s ", i, line);
		while (line[i] == ' ' && linelen >= i)
			i++;
		printf(YEL"\n j'ai passe les espaces i = %d\n"ENDC, i);
		j = i;
		if (line[i] != ',' && line[i] != ' ')
		{
			printf("\n je passe dans le if\n");
			while (line[i] != ',' && line[i] != ' ')
			{
				printf(YEL"line[i] = %c "ENDC, line[i]);
				if (i <= linelen)
					break;
				i++;
			}
		}
		if (line[i] == ',')
			line[i] = ' ';
		len = i - j;
		printf(BLUE"i = %d j = %d len = %d\n"ENDC, i, j, len);
		lum = malloc(sizeof(char *) * len);
		if (lum == NULL)
			printf(RED"error Malloc!\n"ENDC);
		printf(RED"len = %d line[j] = %c line[j + 1] = %c line[j + 2] = %c\n"ENDC, len, line[j], line[j + 1], line[j + 2]);
		while (len-- > 0)
		{
			lum[k] = line[j];
			printf(BLUE"len = %d lum[k] = %c line[j] = %c\n"ENDC, len, lum[k], line[j]);
			line[j] = ' ';
			k++;
			j++;
		}
		printf(YEL"linelen = %d j = %d i = %d\n"ENDC, linelen, j, i);
		i++;
	}
	printf(RED"fin de fonction line = %s\nlum = %s\n"ENDC, line, lum);
	return (lum);
}


/* void	init_ambiant(t_scene *p, char *line)
{
	int i;
	int j;
	p->a.lum = ascii_to_double(get_numb(line));
	p->a.color.rgb[0] = ft_atoi(get_numb(line));
	p->a.color.rgb[1] = ft_atoi(get_numb(line));
	p->a.color.rgb[2] = ft_atoi(get_numb(line));
} */
/* 
void	create_plist(char **av)
{
	t_dico	parsing;
	int		i;
	
	fd = open(argv[1], O_RDONLY);
}

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
} */
