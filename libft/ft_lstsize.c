/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:22:02 by grenaud-          #+#    #+#             */
/*   Updated: 2023/03/20 16:04:50 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_listl *lst)
{
	unsigned int	size;
	t_listl			*lst_tmp;

	lst_tmp = lst;
	size = 0;
	while (lst_tmp)
	{
		size++;
		lst_tmp = lst_tmp->next;
	}
	return (size);
}
