/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:41:20 by grenaud-          #+#    #+#             */
/*   Updated: 2023/03/20 16:02:55 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_listl **alst, t_listl *new)
{
	t_listl	*elem;

	if (alst != NULL && *alst != NULL)
	{
		elem = *alst;
		elem = ft_lstlast(*alst);
		elem->next = new;
		return ;
	}
	*alst = new;
}
