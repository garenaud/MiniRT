/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 17:18:06 by grenaud-          #+#    #+#             */
/*   Updated: 2023/03/14 17:33:48 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define RED		"\033[1m\033[31m"
# define GREEN		"\033[1m\033[32m"
# define YEL		"\033[0;33m"
# define PURP		"\033[0;35m"
# define ENDC		"\033[0m"
# define BOLDRED	"\033[31m"
# define BLUE		"\033[1;34m"

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <math.h>

/* ************************************************************************** */
/* STRUCTS																	  */
/* ************************************************************************** */

/* ************************************************************************** */
/* FUNCTION PROTOTYPES														  */
/* ************************************************************************** */
//ft_atod.c
int		sign_atod(char c);
double	int_part(char c, double result);
double	frac_part(char *str);
int		frac_len(char *str);
double	ascii_to_double(char *str);
/* ************************************************************************** */

#endif