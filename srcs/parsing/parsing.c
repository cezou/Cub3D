/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:22:43 by cviegas           #+#    #+#             */
/*   Updated: 2024/10/25 08:08:49 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void	parse_ids(t_vars *v, int fd, size_t *i)
{
	char	*line;
	char	**l;

	l = NULL;
	while (++(*i))
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		l = ft_split(line, WHITESPACES);
		free(line);
		if (!l)
			(perr("Malloc Failed"), clean_exit(l, fd, v, 1));
		if (!l[0] && (freeall(l), 1))
			continue ;
		if (tab_len(l) != 2)
			(lerr(*i, "Too much or not enough values"), clean_exit(l, fd, v,
					1));
		if (set_a_value(&v->infos, l, *i, v->mlx) == -1)
			clean_exit(l, fd, v, 1);
		freeall(l);
		if (is_everything_set(v->infos))
			return ;
	}
	(lerr(*i, "There are values missing"), clean_exit(l, fd, v, 0));
}

static void	parse_map(t_vars *v, int fd, int i)
{
	calculate_mapsize_checking(skip_whitespaces(v, fd, &i), v, fd, i);
	store_map(v, 0, -1);
	if (!is_map_closed(v->infos.map, v->infos.map_index))
		clean_exit(v->infos.map, INT_MAX, v, 0);
	if (!MANDATORY && is_there_unclosed_doors(v->infos.map, v))
		clean_exit(v->infos.map, INT_MAX, v, 1);
}

void	parsing(int ac, char *filename, t_vars *v)
{
	int		fd;
	size_t	i;

	if (MANDATORY && ac != 2)
		(perr(E_ARG), clean_exit((char **)v->img, INT_MAX, v, 0));
	if (!MANDATORY && (ac < 2 || ac > 5))
		(perr(E_ARGB), clean_exit((char **)v->img, INT_MAX, v, 0));
	if (isnt_ended_by(filename, ".cub"))
		(merr("file name needs to end with \".cub\""),
			clean_exit((char **)v->img, INT_MAX, v, 0));
	init_infos(v, filename, &fd);
	i = 0;
	parse_ids(v, fd, &i);
	parse_map(v, fd, i);
}
