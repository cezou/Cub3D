/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_init_actors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:09:56 by pmagnero          #+#    #+#             */
/*   Updated: 2024/10/28 23:11:02 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	init_doors(t_vars *v)
{
	int		i;
	t_map	*tmp;

	i = -1;
	tmp = v->mapv.map;
	v->door = (t_door *)malloc(sizeof(t_door) * (v->game.nb_door));
	if (!v->door)
		exit((prterr(v, ERRMALL, 1, 1), 1));
	while (tmp)
	{
		if (tmp->val == 'D')
		{
			v->door[++i].x = tmp->x;
			v->door[i].y = tmp->y;
			v->door[i].time = 0;
			v->door[i].state = ECLOSE;
			v->door[i].img_i = EDOOR;
			v->door[i].xdelta = v->img[v->door[i].img_i].width;
		}
		tmp = tmp->right;
	}
}

void	init_objects(t_vars *v, t_actor *a)
{
	int	i;

	i = -1;
	while (++i < v->num_objs)
	{
		a = (t_actor *)ft_calloc(1, sizeof(t_actor));
		if (!a)
			exit((prterr(v, ERRMALL, 1, 1), 1));
		a->x = v->g_objs[i].x;
		a->y = v->g_objs[i].y;
		a->img_i = v->g_objs[i].img_id;
		a->vdiv = v->g_objs[i].uv;
		a->udiv = v->g_objs[i].uv;
		a->vmove = v->g_objs[i].v;
		a->hashitbox = v->g_objs[i].h;
		a->pickable = v->g_objs[i].pickable;
		v->img[v->g_objs[i].img_id].animx = v->img[v->g_objs[i].img_id].width
			/ v->g_objs[i].animx;
		a->active = 1;
		a->next = a;
		a->prev = a;
		add_actor(v, &v->actors, &a);
	}
}

void	init_guard_astar(t_vars *v, t_actor *a)
{
	int (i) = -1;
	a->astar = (t_astar){0};
	a->astar.celld = (t_cell **)ft_calloc(v->mapv.maph + 1, sizeof(t_cell *));
	if (!a->astar.celld)
		exit((prterr(v, ERRMALL, 1, 1), 1));
	a->astar.celld[v->mapv.maph] = NULL;
	while (++i < v->mapv.maph)
	{
		a->astar.celld[i] = (t_cell *)ft_calloc(v->mapv.mapw, sizeof(t_cell));
		if (!a->astar.celld[i])
			exit((prterr(v, ERRMALL, 1, 1), 1));
	}
	i = -1;
	a->astar.closedlst = (bool **)ft_calloc(v->mapv.maph + 1, sizeof(bool *));
	if (!a->astar.closedlst)
		exit((prterr(v, ERRMALL, 1, 1), 1));
	a->astar.closedlst[v->mapv.maph] = NULL;
	while (++i < v->mapv.maph)
	{
		a->astar.closedlst[i] = (bool *)ft_calloc(v->mapv.mapw, sizeof(bool));
		if (!a->astar.closedlst[i])
			exit((prterr(v, ERRMALL, 1, 1), 1));
	}
}

void	init_guard(t_vars *v, t_map *tmp, t_actor *a)
{
	while (tmp)
	{
		if (tmp->val == 'G')
		{
			a = new_actor(v);
			if (!a)
				exit((prterr(v, ERRMALL, 1, 1), 1));
			a->x = tmp->x;
			a->y = tmp->y;
			a->map_pos = tmp;
			a->hp = 60;
			a->img_i = EGUARDW;
			a->vdiv = 1.0;
			a->udiv = 1.0;
			a->isguard = 1;
			a->ms = 0.2;
			a->painchance = 40;
			a->hasrange = 1;
			a->hashitbox = 1;
			a->dmg = 15;
			a->active = 1;
			add_actor((init_guard_astar(v, a), v), &v->actors, &a);
		}
		tmp = tmp->right;
	}
}

void	init_actors(t_vars *v)
{
	init_doors(v);
	init_guard(v, v->mapv.map, NULL);
	init_objects(v, NULL);
}
