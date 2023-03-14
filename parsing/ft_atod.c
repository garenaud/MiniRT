/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aToDouble.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:19:09 by grenaud-          #+#    #+#             */
/*   Updated: 2023/03/14 17:08:19 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int	sign_atod(char c)
{
	if (c == '-')
		return (-1);
	else
		return (1);
}

double	int_part(char c, double result)
{
	if (c >= '0' && c <= '9')
		result = result * 10.0 + (c - '0');
	else
		return (0.0 / 0.0);
	return (result);
}

double	frac_part(char *str)
{
	int		i;
	double	frac;

	i = 1;
	frac = 0;
	while (str[i] != '\0')
	{
		frac = int_part(str[i], frac);
		i++;
	}
	return (frac);
}

int	frac_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i - 1);
}

double	ascii_to_double(char *str)
{
	double	result;
	double	frac;
	double	sign;
	int		fraclen;

	sign = 1;
	if (*str == '-' || *str == '+')
	{
		sign = sign_atod(*str);
		str++;
	}
	while (*str != '\0' && *str != '.')
	{
		result = int_part(*str, result);
		str++;
	}
	if (*str == '.')
	{
		frac = frac_part(str);
		fraclen = frac_len(str);
	}
	if (fraclen)
		result += frac / pow(10.0, fraclen);
	return (result *= sign);
}

/* int	main(int ac, char **av)
{
	double	number;
	double test = 0.000000001;

	number = ascii_to_double(av[1]);
	printf("en str: %s et en double: %lf test: %lf", av[1], number, test);
	return (0);
} */