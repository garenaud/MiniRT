/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 10:35:49 by grenaud-          #+#    #+#             */
/*   Updated: 2023/03/20 16:02:29 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_listl	*ft_lstmap(t_listl *lst, void *(*f)(void *), void (*del)(void *))
{
	t_listl	*tmp;
	t_listl	*ret;

	if (!lst)
		return (0);
	ret = ft_lstnew((*f)(lst->content));
	if (!ret)
		return (0);
	tmp = ret;
	lst = lst->next;
	while (lst)
	{
		tmp->next = ft_lstnew((*f)(lst->content));
		if (!tmp->next)
		{
			ft_lstclear(&ret, del);
			return (0);
		}
		tmp = tmp->next;
		lst = lst->next;
	}
	return (ret);
}
