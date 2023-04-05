/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 12:50:35 by grenaud-          #+#    #+#             */
/*   Updated: 2023/04/05 11:10:47 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_listl	*ft_lstnew(void *content)
{
	t_listl	*result;

	result = wrmalloc(sizeof(t_listl) * 1);
	if (!result)
		return (NULL);
	result->content = content;
	result->next = NULL;
	return (result);
}
