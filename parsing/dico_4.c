/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dico_4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 10:35:18 by jsollett          #+#    #+#             */
/*   Updated: 2023/03/20 16:43:51 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	duplicate(t_dico **orig, t_dico **copy)
{
	int		index;
	t_dico	*tmp;

	index = 0;
	while (index < (int)size_stack_dico(*orig))
	{
		tmp = NULL;
		tmp = getitem_dico(*orig, index);
		push_dico(copy, tmp->key, tmp->value);
		delete_dico(&tmp);
		index++;
	}
	*copy = reverse_dico(copy);
}

char	*getword1(t_list **raw, char *search)
{
	int		i;
	int		pos;
	char	*str;
	char	*c_tmp;

	i = 0;
	search = delimitateur(raw);
	pos = getpos_c(*raw, search);
	if (pos == -1)
		pos = size_stack(*raw);
	str = malloc((pos + 1) * sizeof(char));
	while (i < pos)
	{
		c_tmp = pop(raw);
		str[i] = *c_tmp;
		free(c_tmp);
		i++;
	}
	if (size_stack(*raw) != 0)
		remove_pos_c(raw, 0);
	str[i] = '\0';
	return (str);
}

char	*delimitateur(t_list **raw)
{
	if (ft_strncmp(getitem(*raw, 0), "\"", 1) == 0)
	{
		remove_pos_c(raw, 0);
		return ("\"");
	}
	else if (ft_strncmp(getitem(*raw, 0), "\'", 1) == 0)
	{
		remove_pos_c(raw, 0);
		return ("\'");
	}
	else
	{
		return (" ");
	}
}
