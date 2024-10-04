/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:22:37 by cviegas           #+#    #+#             */
/*   Updated: 2024/09/18 21:53:13 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

char	*skip_whitespaces(t_vars *v, int fd, int *i)
{
	char	*line;

	while (++(*i))
	{
		line = get_next_line(fd);
		if (!line)
			(lerr(*i, "There is no map"), clean_exit((char **)line, fd, v, 0));
		if (there_is_only_whitespaces(line) && (free(line), 1))
			continue ;
		v->infos.map_index = *i - 1;
		return (line);
	}
	return (NULL);
}

bool	check_line(char *line, t_vars *v, size_t ind)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (!is_char_valid(line[i]))
			return (free(line), lerr(ind, "There is an unvalid char"), 0);
		if (is_player_char(line[i]))
		{
			if (v->infos.player)
				return (free(line), lerr(ind, "There is a second char player"),
					0);
			v->infos.player = 1;
		}
	}
	return (free(line), 1);
}

void	calculate_mapsize_checking(char *line, t_vars *v, int fd, int i)
{
	size_t	j;

	v->infos.player = 0;
	if (!check_line(line, v, i))
		clean_exit((char **)line, fd, v, 0);
	j = 0;
	while (++i && ++j)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!check_line(line, v, i))
			clean_exit((char **)j, fd, v, 0);
	}
	v->infos.map_height = j + 1;
	close(fd);
}

void	store_map(t_vars *v)
{
	int	fd;
	int	i;

	fd = open(v->mapv.filename, O_RDONLY);
	if (fd == -1)
		(perr("Malloc Failed"), clean_exit(v->infos.map, INT_MAX, v, 0));
	v->infos.map = malloc((v->infos.map_height + 1) * sizeof(char *));
	if (!v->infos.map)
		(perr("Malloc Failed"), clean_exit(v->infos.map, fd, v, 0));
	i = -1;
	while (++i < (int)v->infos.map_index - 1)
	{
		v->infos.map[0] = get_next_line(fd);
		free(v->infos.map[0]);
	}
	i = -1;
	while (++i < (int)v->infos.map_height)
	{
		v->infos.map[i] = get_next_line(fd);
		if (!v->infos.map[i])
			break ;
		v->infos.map[i][ft_strlen(v->infos.map[i]) - 1] = 0;
	}
	(close(fd), v->infos.map[i] = 0);
}
