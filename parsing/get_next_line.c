/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:08:12 by grenaud-          #+#    #+#             */
/*   Updated: 2023/03/16 12:23:14 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	gnl_read(char **buff_s, char **line, int fd, int bli)
{
	char		buff[BUFFER_SIZE + 1];
	int			ret;

	ft_strdupcat(line, *buff_s);
	while (ft_strichr(*line, '\n') == -1)
	{
		ret = read(fd, buff, BUFFER_SIZE);
		if (ret <= 0)
		{
			ft_strdel(buff_s);
			return (*line && (*line[0] != '\0'));
		}
		buff[ret] = '\0';
		ft_strdupcat(line, buff);
	}
	bli = ft_strichr(*line, '\n');
	if (bli >= 0)
	{
		ft_strdel(buff_s);
		ft_strdupcat(buff_s, &(*line)[bli + 1]);
		(*line)[bli + 1] = '\0';
	}
	return (1);
}

size_t	ft_strlen(char const *s)
{
	unsigned int	size;

	size = 0;
	while (s[size] != '\0')
		size++;
	return (size);
}

char	*get_next_line(int fd)
{
	static char	*data[FOPEN_MAX];
	char		*line;

	line = NULL;
	if (fd < FOPEN_MAX && fd >= 0 && !gnl_read(&(data[fd]), &line, fd, 0))
		ft_strdel(&line);
	return (line);
}

void	ft_strdel(char **str)
{
	if (str == NULL || *str == NULL)
		return ;
	else
	{
		free (*str);
		*str = NULL;
	}
}

char	*ft_strdupcat(char **s1, char *s2)
{
	char	*strnew;
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	if (!(*s1) && !s2)
		return (NULL);
	strnew = malloc(sizeof(char) * (ft_strlen(*s1) + ft_strlen(s2)) + 1);
	if (!strnew)
		return (NULL);
	while (*s1 && (*s1)[i])
		strnew[j++] = (*s1)[i++];
	i = 0;
	while (s2 && s2[i])
		strnew[j++] = s2[i++];
	strnew[j] = '\0';
	ft_strdel(s1);
	(*s1) = strnew;
	return (strnew);
}

int	ft_strichr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}
