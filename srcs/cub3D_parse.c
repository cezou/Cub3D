/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:32:25 by pmagnero          #+#    #+#             */
/*   Updated: 2024/09/12 17:27:42 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

// int	is_invalid_char(char val)
// {
// 	if (MANDATORY && val != COLLECT && val != SPACE && val != SPAWN
// 		&& val != EXIT && val != WALL)
// 		return (1);
// 	if (!MANDATORY && val != COLLECT && val != SPACE && val != SPAWN
// 		&& val != EXIT && val != WALL && val != GUARD)
// 		return (1);
// 	return (0);
// }

// static int	checkcomp(t_vars *v, t_map *k)
// {
// 	t_map	*n;

// 	n = k;
// 	while (n)
// 	{
// 		if (is_invalid_char(n->val))
// 			exit((prterr(v, ERRINVC, 1, 1), 1));
// 		if ((n->x == 0 && n->val != WALL)
// 			|| (n->right && n->right->x == 0 && n->val != WALL)
// 			|| (n->y == 0 && n->val != WALL)
// 			|| (n->y == v->mapv.maph - 1 && n->val != WALL))
// 			exit((prterr(v, ERRMNC, 1, 1), 1));
// 		if ((n->x >= v->mapv.mapw)
// 			|| (n->right && n->right->x == 0 && n->x != v->mapv.mapw - 1)
// 			|| (v->last->x != v->mapv.mapw - 1))
// 			exit((prterr(v, ERRNUMC, 1, 1), 1));
// 		n = n->right;
// 	}
// 	if (v->objs.collect == 0)
// 		exit((prterr(v, "No collectible on the map\n", 1, 1), 1));
// 	return (0);
// }

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
	return ((map_trunc(v, &tmp, &left), prev));
}

int	parse(t_vars *v, int j, t_map *p)
{
	int i;

	i = -1;
	while (v->infos.map[++i])
	{
		p = populate_map((j++, v->infos.map[i]), v, p, NULL);
		v->mapv.tmpy += 1;
	}
	v->mapv.maph = j + 1;
	return (1);
}