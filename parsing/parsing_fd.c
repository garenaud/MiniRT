/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 09:50:19 by grenaud-          #+#    #+#             */
/*   Updated: 2023/04/04 12:05:07 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	init_obj(t_scene *p, char *line, int index)
{
/*  	if (p->obj == NULL)
	{
		p->obj = (t_listobj *)malloc(sizeof(t_listobj));
		printf(BLUE"p->obj = %p\n"ENDC, p->obj);
	} */
	if (line[0] == 's' && line[1] == 'p')
		push_sp(p, line, index);
	if (line[0] == 'p' && line[1] == 'l')
		push_pl(p, line, index);
	if (line[0] == 'c' && line[1] == 'y')
		push_cy(p, line, index);
}

void	parsing(t_scene *p, char **argv)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(argv[1], O_RDONLY);
	i = 1;
	while (i <= p->check.fd_lines)
	{
		line = get_next_line(fd);
		printf("is_empty = %d line au debut = [%s]\n", is_empty(line), line);
		line = clean_comm(p, line);
/* 		if (is_empty(line) == 0 && line != NULL)
			line = clean_comm(p, line); */
		printf("is_empty = %dline au clean = [%s]\n", is_empty(line), line);
		if (is_empty(line) == 0 && line != NULL)
		{
			line = trim_line(line);
			printf("line = [%s]\n", line);
			if (line[0] == 'A')
				init_ambiant(p, line, i);
			if (line[0] == 'C')
				init_cam(p, line, i);
			if (line[0] == 'L')
				init_light(p, line, i);
			if (line[0] == 's' || line[0] == 'p' || line[0] == 'c')
				init_obj(p, line, i);
			free(line);
		}
		else if (is_empty(line) == 1 || line == NULL)
			free(line);
		i++;
	}
	close(fd);
}

char	*get_numb(char *line, int index)
{
	static int		i;
	int				j;
	int				k;

	i = 2;
	k = ft_strlen(line);
	while (line[i] != '\0')
	{
		while (ft_isdigit2(line[i]) == 0 && line[i] != '\0')
			i++;
		j = i;
		while (ft_isdigit2(line[i]) == 1)// && line[i + 1] != '\0')
			i++;
		if (i > k)
			message("Your fd doesn't have enough information on line", index);
		if (j < i)
			return (ft_strdup_num(line, j, i));
		i++;
	}
	message(RED"Your fd doesn't have enough information on line"ENDC, index);
	return (ft_strdup_num(line, j, i));
}
