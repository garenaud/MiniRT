/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 10:23:16 by grenaud-          #+#    #+#             */
/*   Updated: 2023/03/31 20:48:12 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

char	*clean_line(t_scene *p, char *line)
{
	char	*new = NULL;
	(void)	p;
	(void) line;

	//new = trim_line(line);
	//new = clean_comm(p, new);
	if (new == NULL || is_empty(new))
		return (NULL);
	//free(line);
	return (new);
}

char	*trim_line(char *line)
{
	int		i;
	int		j;
	int		k;
	char	*new;

	i = 0;
	j = ft_strlen(line);
	if (j <= 0)
		return (NULL);
	k = 0;
	while (ft_isspace(line[i]))
		i++;
	while (ft_isspace(line[j]))
		j--;
	j -= i;
	new = (char *)malloc(sizeof(char) * (j + 2));
	if (!new)
		return (NULL);
	while (k <= j)
		new[k++] = line[i++];
	new[k] = '\0';
	free(line);
	return (new);
}

int	is_empty(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}

char	*clean_comm(t_scene *p, char *line)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = (char *)malloc(sizeof(char) * (strlen_comm(p, line) + 2));
	if (!new)
		return (NULL);
	while (line[i])
	{
		if (line[i] == '/' && line[i + 1] != '\0' && line[i + 1] == '*')
			p->check.comm = 1;
		else if (line[i] == '*' && line[i + 1] != '\0' && line[i + 1] == '/'
			&& p->check.comm == 1)
		{
			p->check.comm = 0;
			i += 2;
		}
		else if (line[i] == '/' && line[i + 1] != '\0' && line[i + 1] == '/')
			break;
		if (p->check.comm == 0)
			new[j++] = line[i++];
		else
			i++;
	}
	new[j] = '\0';
	free(line);
	return (new);
}

int		strlen_comm(t_scene *p, char *line)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '/' && line[i + 1] != '\0' && line[i + 1] == '*')
			p->check.comm = 1;
		else if (line[i] == '*' && line[i + 1] != '\0' && line[i + 1] == '/'
			&& p->check.comm == 1)
			p->check.comm = 0;
		else if (line[i] == '/' && line[i + 1] != '\0' && line[i + 1] == '/')
			return (i - j);
		if (p->check.comm == 1)
			j++;
		i++;
	}
	if (j >= i)
		return (-1);
	return ((i - j) - 2);
}

int	ft_count_lines(int fd)
{
	int		linecount;
	char	buffer[0];
	int		bytes;

	buffer[0] = '\0';
	linecount = 1;
	while (1)
	{
		bytes = read(fd, buffer, 1);
		if (bytes < 1)
			break ;
		if (buffer[0] == '\n')
			linecount++;
	}
	return (linecount);
}