/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:01:00 by grenaud-          #+#    #+#             */
/*   Updated: 2023/05/16 16:07:00 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

int	atoi_c(const char *str, int check, int index)
{
	int	neg;
	int	i;
	int	num;

	i = 0;
	neg = 1;
	num = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		num = num * 10 + (str[i] - 48);
		i++;
	}
	check_int((num * neg), check, index);
	return (num * neg);
}

void	*trim_numb(char *line, int i)
{
	int		j;
	int		k;
	char	*new;

	k = 0;
	j = ft_strlen(line) - 1;
	if (j <= 0)
		return (NULL);
	new = wrmalloc(sizeof(char *) * ((j - i) + 2));
	if (!new)
		return (NULL);
	while (i <= j)
		new[k++] = line[i++];
	new[k] = '\0';
	return (new);
}

void	*trim_end(char *line)
{
	int		len;
	int		i;
	char	*new;

	len = ft_strlen(line) - 1;
	i = -1;
	while (len >= 0)
	{
		while (ft_isdigit2(line[len]) == 0 || line[len] == 44)
			len--;
		break ;
	}
	new = wrmalloc(sizeof(char *) * ((len) + 2));
	while (i++ <= len)
		new[i] = line[i];
	if (new[i - 1] == 44)
		new[i - 1] = '\0';
	else
		new[i] = '\0';
	wrfree(line);
	return (new);
}
