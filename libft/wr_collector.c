/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wr_collector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:01:10 by grenaud-          #+#    #+#             */
/*   Updated: 2023/04/04 15:07:11 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_listl	**wrgetter(void)
{
	static t_listl	*wrm;

	return (&wrm);
}

void	*wrmalloc(unsigned long size)
{
	char	*buffer;
	t_listl	*new_elem;

	buffer = malloc(size);
	if (!buffer)
	{
		wrdestroy();
		ft_putstr("ERROR Malloc\n");
		exit (1);
	}
	new_elem = malloc(sizeof(t_listl));
	if (!new_elem)
	{
		free(buffer);
		wrdestroy();
		ft_putstr("ERROR Malloc\n");
		exit (1);
	}
	new_elem->content = buffer;
	new_elem->next = 0;
	ft_lstadd_back(wrgetter(), new_elem);
	return (buffer);
}

int	wrfree(void *ptr)
{
	t_listl	*prev;
	t_listl	*current;
	t_listl	*next;
	t_listl	**wrstart;

	prev = 0;
	wrstart = wrgetter();
	current = *wrstart;
	while (current)
	{
		next = current->next;
		if (current->content == ptr)
		{
			free(ptr);
			free(current);
			if (prev)
				prev->next = next;
			else
				*wrstart = next;
			return (1);
		}
		prev = current;
		current = current->next;
	}
	return (0);
}

void	wrdestroy(void)
{
	t_listl	*current;
	t_listl	*next;
	t_listl	**wrstart;

	wrstart = wrgetter();
	current = *wrstart;
	while (current)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
	*wrstart = 0;
}
