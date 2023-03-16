/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:31:08 by grenaud-          #+#    #+#             */
/*   Updated: 2022/04/26 13:57:25 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include "libft.h" */
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

size_t	ft_strlen(char const *s)
{
	unsigned int	size;

	size = 0;
	while (s[size] != '\0')
		size++;
	return (size);
}

char	*strchr_gnl(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

char	*strjoin_gnl(char *left_str, char *buff)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!left_str)
	{
		left_str = (char *)malloc(1 * sizeof(char));
		left_str[0] = '\0';
	}
	if (!left_str || !buff)
		return (NULL);
	str = malloc(sizeof(char) * ((ft_strlen(left_str) + ft_strlen(buff)) + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (left_str)
		while (left_str[++i] != '\0')
			str[i] = left_str[i];
	while (buff[j] != '\0')
		str[i++] = buff[j++];
	str[ft_strlen(left_str) + ft_strlen(buff)] = '\0';
	free(left_str);
	return (str);
}

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
	{
		str[i] = raw_line[i];
		i++;
	}
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
	while (!strchr_gnl(raw_line, '\n') && bytes != 0)
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes == -1)
		{
			free (buff);
			return (NULL);
		}
		buff[bytes] = '\0';
		raw_line = strjoin_gnl(raw_line, buff);
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
	return (line);
}

int main()
{
    char    *temp[20];
    int fd;
    int i;
    int j;

    j = 0;
    fd = open("test.ber", O_RDONLY);
    while(fd==1)
    {
        temp[j] = get_next_line(fd);
        printf("%s \n", *temp);
        j++;
    };
    return (0);
}