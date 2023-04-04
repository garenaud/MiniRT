/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin_gnl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 16:31:29 by marvin            #+#    #+#             */
/*   Updated: 2023/04/04 17:07:16 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*strjoin_gnl(char *left_str, char *buff)
{
	size_t	i;
	size_t	j;
	char	*s;

	if (!left_str)
	{
		left_str = wrmalloc(sizeof(char *) * (1));
		left_str[0] = '\0';
	}
	if (!left_str || !buff)
		return (NULL);
	s = wrmalloc(sizeof(char) * ((ft_strlen(left_str) + ft_strlen(buff)) + 1));
	if (s == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (left_str)
		while (left_str[++i] != '\0')
			s[i] = left_str[i];
	while (buff[j] != '\0')
		s[i++] = buff[j++];
	s[ft_strlen(left_str) + ft_strlen(buff)] = '\0';
	free(left_str);
	return (s);
}
