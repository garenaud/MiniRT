/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 09:50:19 by grenaud-          #+#    #+#             */
/*   Updated: 2023/03/29 16:27:05 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

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
		return (NULL);
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

	i = 2;
	while (line[i] != '\0')
	{
		while (ft_isdigit2(line[i]) == 0 && line[i] != '\0')
			i++;
		j = i;
		while (ft_isdigit2(line[i]) == 1 && line[i + 1] != '\0')
			i++;
		if (j < i)
			return (ft_strdup_num(line, j, i));
		i++;
	}
	return (ft_strdup_num(line, j, i));
}
