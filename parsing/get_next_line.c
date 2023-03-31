/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 14:17:14 by grenaud-          #+#    #+#             */
/*   Updated: 2023/03/31 20:38:11 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"
#include "get_next_line.h"

char	*ft_get_start(char *raw_line)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (raw_line[i] && raw_line[i] != '\n')
		i++;
	if (!raw_line[i])
	{
		free (raw_line);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(raw_line) - i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (raw_line[i])
		str[j++] = raw_line[i++];
	str[j] = '\0';
	free (raw_line);
	return (str);
}

char	*ft_get_line(char *raw_line)
{
	int		i;
	char	*str;

	i = 0;
	if (!raw_line[i])
		return (NULL);
	while (raw_line[i] && raw_line[i] != '\n')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (raw_line[i] && raw_line[i] != '\n')
	{
		str[i] = raw_line[i];
		i++;
	}
	if (raw_line[i] == '\n')
		str[i] = '\0';
	return (str);
}

char	*ft_get_raw_line(int fd, char *raw_line)
{
	char	*buff;
	int		bytes;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	bytes = 1;
	while (!ft_strchr2(raw_line, '\n') && bytes != 0)
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes == -1)
		{
			free (buff);
			return (NULL);
		}
		buff[bytes] = '\0';
		raw_line = ft_strjoin2(raw_line, buff);
	}
	free (buff);
	return (raw_line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*raw_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	raw_line = ft_get_raw_line(fd, raw_line);
	if (!raw_line)
		return (NULL);
	line = ft_get_line(raw_line);
	raw_line = ft_get_start(raw_line);
	line = trim_line(line);
	return (line);
}

/* int		main(int argc, char **argv)
{
	int		fd;
	int		i;
	char	*ret;

	i = 0;
	(void)argc;
	fd = open((argv[1]), O_RDONLY);
	while (i < 4)
	{
		ret = get_next_line(fd);
		printf("|%s|\n", ret);
		i++;
	}
} */
