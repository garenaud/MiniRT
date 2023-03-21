/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 12:50:35 by grenaud-          #+#    #+#             */
/*   Updated: 2023/03/20 16:04:37 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_listl	*ft_lstnew(void *content)
{
	t_listl	*result;

	result = (t_listl *)malloc(sizeof(t_listl));
	if (!result)
		return (NULL);
	result->content = content;
	result->next = NULL;
	return (result);
}
