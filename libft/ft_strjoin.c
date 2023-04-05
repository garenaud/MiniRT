/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 16:31:29 by marvin            #+#    #+#             */
/*   Updated: 2023/04/05 11:38:27 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str = wrmalloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, s1_len + 1);
	ft_strlcat(str + (s1_len), s2, s2_len + 1);
	return (str);
}

char	*ft_strjoin2(char *left_str, char *buff)
{
	size_t	i;
	size_t	j;
	char	*s;

	if (!left_str)
	{
		left_str = wrmalloc(sizeof(char) * 1);
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
	wrfree(left_str);
	return (s);
}
