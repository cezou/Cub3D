/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:32:25 by pmagnero          #+#    #+#             */
/*   Updated: 2024/10/23 23:31:09 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void	map_trunc(t_vars *v, t_map **tmp, t_map **left)
{
	if (v->mapv.mapw > 1)
	{
		(*tmp)->left = *left;
		(*tmp)->right = NULL;
		if (!v->mapv.map)
		{
			(*tmp)->right = (v)->mapv.map;
			(*tmp)->left = *left;
		}
	}
	v->mapv.tmpx = 0;
	if (*tmp)
		(*tmp)->right = NULL;
	v->last = (*tmp);
}

static t_map	*populate_map(char *tab, t_vars *v, t_map *p, t_map *prev)
{
	t_map	*n;
	t_map	*tmp;
	t_map	*left;
	int		i;

	i = -1;
	n = NULL;
	left = NULL;
	tmp = (v)->last;
	while (tab[++i])
	{
		if (tab[i] == '\n')
			continue ;
		if (v->mapv.map && !v->last)
			(tmp) = n;
		n = new_point(v, tab[i], &p);
		if (!n && map_clear(v->mapv.map))
			return (free(n), NULL);
		if (i == 0)
			prev = n;
		add_element((v->mapv.tmpx += 1, &v->mapv.map), &n, &tmp, &left);
	}
	if (i > v->mapv.mapw)
		v->mapv.mapw = i;
	return ((map_trunc(v, &tmp, &left), prev));
}

int	parse(t_vars *v, int j, t_map *p)
{
	int	i;

	i = -1;
	while (v->infos.map[++i])
	{
		p = populate_map((j++, v->infos.map[i]), v, p, NULL);
		v->mapv.tmpy += 1;
	}
	v->mapv.maph = v->mapv.tmpy;
	return (1);
}
