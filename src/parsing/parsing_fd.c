/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 09:50:19 by grenaud-          #+#    #+#             */
/*   Updated: 2023/05/16 16:41:37 by grenaud-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	init_obj(t_scene *p, char *line, int index)
{
	if (line[0] == 's' && line[1] == 'p')
		push_sp(p, index);
	if (line[0] == 'p' && line[1] == 'l')
		push_pl(p, index);
	if (line[0] == 'c' && line[1] == 'y')
		push_cy(p, index);
}

void	parsing(t_scene *p, char **argv)
{
	int			fd;
	int			i;

	init_check(p, argv);
	fd = open(argv[1], O_RDONLY);
	i = 1;
	while (i++ <= p->check.fd_lines)
		read_fd(p, fd, i);
	check_struct(p);
	p->forme = wrmalloc(size_stack_obj(p->obj) * sizeof(t_objet));
	if (p->forme == NULL)
		wrdestroy();
	create_array(p);
	close(fd);
}

void	read_fd(t_scene *p, int fd, int i)
{
	p->line = get_next_line(fd);
	if (is_empty(p->line) == 0 && p->line != NULL)
	{
		p->line = clean_comm(p, p->line);
		p->line = trim_end(p->line);
	}
	if (is_empty(p->line) == 0 && p->line != NULL)
	{
		p->line = trim_line(p->line);
		if (p->line[0] == 'A')
			init_ambiant(p, i - 1);
		else if (p->line[0] == 'C')
			init_cam(p, i - 1);
		else if (p->line[0] == 'L')
			init_light(p, i - 1);
		else if (p->line[0] == 'p' && p->line[1] == 'l')
			init_obj(p, p->line, i - 1);
		else if (p->line[0] == 'c' && p->line[1] == 'y')
			init_obj(p, p->line, i - 1);
		else if (p->line[0] == 's' && p->line[1] == 'p')
			init_obj(p, p->line, i - 1);
		else
			message("Unknow element on line", i - 1);
	}
}

char	*get_numb(t_scene *p, int index)
{
	int				i;
	char			*num;

	i = 0;
	if (p->line == NULL)
		message("Your fd doesn't have enough information on line", index);
	num = NULL;
	while (p->line[i] != '\0')
	{
		while (ft_isdigit2(p->line[i]) == 0 && p->line[i] != '\0')
			i++;
		p->line = trim_numb(p->line, i);
		i = 0;
		while (ft_isdigit2(p->line[i]) == 1)
			i++;
		if (i > 0)
			num = ft_strdup_num(p->line, 0, i);
		p->line = trim_numb(p->line, i);
		return (num);
		i++;
	}
	message("Your fd doesn't have enough information on line", index);
	return (num);
}
