/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 14:05:55 by grenaud-          #+#    #+#             */
/*   Updated: 2023/03/21 12:36:54 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_listl **alst, t_listl *new)
{
	if (!alst || !new)
		return ;
	if (*alst)
		new->next = *alst;
	else
		new->next = NULL;
	*alst = new;
}
