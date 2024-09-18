/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:22:43 by cviegas           #+#    #+#             */
/*   Updated: 2024/09/15 15:42:12 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	parse_ids(t_vars *v, int fd, size_t *i)
{
	char	*line;
	char	**l;

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

void	store_map(t_vars *v)
{
	int	fd;
	int	i;

	fd = open(v->mapv.filename, O_RDONLY);
	if (fd == -1)
		(perr("Malloc Failed"), clean_exit(v->infos.map, 666, v, 0));
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

void	parse_map(t_vars *v, int fd, int i)
{
	calculate_mapsize_checking(skip_whitespaces(v, fd, &i), v, fd, i);
	store_map(v);
	// if (!is_map_closed(v->infos.map))
	// 	clean_exit(v->infos.map, 666, v, 1);
	freeall(v->infos.map);
}

void	parse_file(int fd, t_vars *v)
{
	size_t	i;

	i = 0;
	parse_ids(v, fd, &i);
	parse_map(v, fd, i);
}

void	parsing(int ac, char **av, t_vars *v)
{
	int	fd;

	if (ac < 2)
		(perr(E_ARG), exit(FAIL));
	if (isnt_cub_ended(av[1]))
		exit((merr("file name needs to end with \".cub\""), FAIL));
	v->mapv.filename = av[1];
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		exit((merr("file doesn't exist or open failed"), FAIL));
	v->mlx = mlx_init();
	if (!v->mlx)
		exit((close(fd), perr("MLX init failed"), FAIL));
	init_imgs(v);
	parse_file(fd, v);
}
