/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 09:50:19 by grenaud-          #+#    #+#             */
/*   Updated: 2023/03/28 23:01:01 by grenaud-         ###   ########.fr       */
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
	//free(test);
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

void	init_obj(t_scene *p, char *line)
{
	if (line[0] == 's' && line[1] == 'p')
		push_sp(p, line);
	if (line[0] == 'p' && line[1] == 'l')
		push_pl(p, line);
	if (line[0] == 'c' && line[1] == 'y')
		push_cy(p, line);
}

void	parsing(t_scene *p, char **argv)
{
	int		fd;
	char	*line;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return ;
	while (fd)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (line[0] == 'A')
			init_ambiant(p, line);
		if (line[0] == 'C')
			init_cam(p, line);
		if (line[0] == 'L')
			init_light(p, line);
		if (line[0] == 's' || line[0] == 'p' || line[0] == 'c')
			init_obj(p, line);
	}
	free(line);
	close(fd);
}

char	*clean_line(char *line)
{
	int		i;
	int		j;
	char	*new;
	
	i = 0;
	j = 0;
	while (ft_isspace(line[i]))
		i++;
	new = (char *)malloc(sizeof(char) * (ft_strlen(line) - i + 1));
	if (!new)
		return NULL;
	while (line[i])
	{
		new[j] = line[i];
		i++;
		j++;
	}
	free(line);
	return (new);
}

char	*get_numb(char *line)
{
	static int		i;
	int				j;
	int				k;
	int				linelen;
	char			*lum = NULL;
	
	i = 2;
	k = 0;
	linelen = ft_strlen(line);
	while(line[i] != '\0')
	{
		while (line[i] == ' ' && linelen >= i)
			i++;
		j = i;
		while (line[i] != ',' && line[i] != ' ')
			i++;
		if (line[i] == ',')
			line[i] = ' ';
  		lum = malloc(sizeof(char *) * (i - j));
		if (lum == NULL)
			return NULL;
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
/*
char	*get_numb(char *line)
{
	static int		i;
	int				j;
	int				k;
	int				linelen;
	char			*lum = NULL;
	
	i = 1;
	k = 0;
	linelen = ft_strlen(line);
	while(line[i] != '\0')
	{
		while (ft_isdigit(line[i]) != 1)
			i++;
		printf(RED"\n i = %d j = \n", i);
		j = i;
		if (ft_isdigit(line[i]) == 1)
				i++;
		else if (line[i] == ',')
			line[i] = ' ';
		else if (j != i)
		{
			lum = ft_strdup_num(line, j, i);
			while (j++ < i)
				line[j] = ' ';
			printf(BLUE"\nlum = %s line = %s\n"ENDC, lum, line);
			return (lum);
		}
		i++;
	}
	return (lum);
}


char	*get_numb(char *line)
{
	static int		i;
	int				j;
	int				k;
	int				linelen;
	char			*num = NULL;
	
	i = 1;
	k = 0;
	linelen = ft_strlen(line);
	while(line[i] != '\0')
	{
		while (line[i] == ' ' && linelen >= i)
			i++;
		j = i;
		while (line[i] != ',' && line[i] != ' ')
			i++;
		if (line[i] == ',')
			line[i] = ' ';
		if (j < i)
		{
			num = ft_strdup_num(line, j, i);
			//printf(BLUE"le num est: %s"ENDC, num);
			return(num);
		}
		i++;
	}
	return (num);
}  */
