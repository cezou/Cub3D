/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csv.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 08:16:53 by cviegas           #+#    #+#             */
/*   Updated: 2024/10/25 08:20:17 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3D.h"

void	store_ceil_infos(char **l, int fd, t_vars *v)
{
	long int	y;
	long int	x;

	if (tab_len(l) != 4)
		(eerr(ECEIL, 2), clean_exit(l, fd, v, 1));
	x = ft_atol(l[0]);
	if (x < 0)
		(eerr("Ceil: 1: bad coordinate.", 2), clean_exit(l, fd, v, 1));
	y = ft_atol(l[1]);
	if (y < 0 || y > (long int)v->infos.map_height)
		(eerr("Ceil: 2: bad coordinate.", 2), clean_exit(l, fd, v, 1));
	v->infos.ceil_topleft[0] = x;
	v->infos.ceil_topleft[1] = y;
	x = ft_atol(l[2]);
	if (x < 0)
		(eerr("Ceil: X: bad coordinate.", 2), clean_exit(l, fd, v, 1));
	y = ft_atol(l[3]);
	if (y < 0 || y > (long int)v->infos.map_height)
		(eerr("Ceil: Y: bad coordinate.", 2), clean_exit(l, fd, v, 1));
	v->infos.ceil_botright[0] = x;
	v->infos.ceil_botright[1] = y;
}

void	store_an_obj(char **l, int line, int fd, t_vars *v)
{
	static int	i = 0;

	if (i >= 200)
		return ;
	if (tab_len(l) != 7)
		(eerr("Bad object: Not 7 values", line), clean_exit(l, fd, v, 1));
	v->g_objs[i].img_id = get_sprite_id(v->sprite_map, l[0]);
	v->g_objs[i].x = ft_atoi(l[1]);
	v->g_objs[i].y = ft_atoi(l[2]);
	v->g_objs[i].uv = ft_atoi(l[3]);
	v->g_objs[i].v = ft_atoi(l[4]);
	v->g_objs[i].h = ft_atoi(l[5]);
	v->g_objs[i].pickable = ft_atoi(l[6]);
	i++;
}

void	parse_extension(int fd, t_vars *v)
{
	char	*s;
	char	**l;
	int		i;

	i = -1;
	ft_bzero(v->g_objs, 200);
	while (++i || 1)
	{
		s = get_next_line(fd);
		if (!s)
			break ;
		l = ft_split(s, ",\n");
		free(s);
		if (!l)
			(eerr("Malloc failed", i + 1), clean_exit(l, fd, v, 0));
		if (i == 2)
			store_ceil_infos(l, fd, v);
		if (i > 5)
			store_an_obj(l, i + 1, fd, v);
		freeall(l);
	}
	v->num_objs = i - 6;
	close(fd);
}

void	parsing_csv(char *filename, t_vars *v)
{
	int	fd;

	if (isnt_ended_by(filename, ".csv"))
		(merr("Map extension isn't csv ended."), clean_exit((char **)v->img,
				INT_MAX, v, 0));
	v->sprite_map = NULL;
	init_sprite_map(v, &v->sprite_map);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		(merr("file doesn't exist or open failed"), clean_exit((char **)v->img,
				INT_MAX, v, 0));
	parse_extension(fd, v);
	free_sprite_map(&v->sprite_map);
}
