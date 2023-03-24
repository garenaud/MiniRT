/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:56:16 by grenaud-          #+#    #+#             */
/*   Updated: 2023/03/17 11:17:50 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	printll(t_list *lst)
{
	printf("start");
	while (lst)
	{
		printf("-->[%s]\n", (lst->data));
		lst = lst->next;
	}
	printf("-->[end]\n");
}

void	print_ic(t_list_i *lst_i, t_list *lst)
{
	printf("start\n");
	while (lst && lst_i)
	{
		printf("[%d]-->[%s]\n", (lst_i->data), (lst->data));
		lst = lst->next;
		lst_i = lst_i->next;
	}
	printf("-->[end]\n");
}
