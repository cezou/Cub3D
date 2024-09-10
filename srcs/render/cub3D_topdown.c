/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_topdown.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:53:03 by pmagnero          #+#    #+#             */
/*   Updated: 2024/04/05 12:19:12 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void	puttextures(t_vars *v, int i, int ph, int pw)
{
	size_t	k;
	t_point	p;
	t_point	d;

	p.y = -1;
	while (++(p.y) < v->img[i].height)
	{
		p.x = v->img[i].animx - 1;
		while (++(p.x) < v->img[i].width)
		{
			k = (p.y * v->img[i].len) + (p.x * 4);
			if (v->img[i].addr[k + 3] == 0)
			{
				d.x = (p.x + pw) * v->mouse.zoom;
				d.y = (p.y + ph) * v->mouse.zoom;
				img_pix_put(&v->img[COMP_N],
					(t_point){d.x - (v->mapv.mapw * v->mouse.zoom / 2)
					+ v->mouse.xoff + v->mapv.shiftx,
					d.y - (v->mapv.maph * v->mouse.zoom / 2) + v->mouse.yoff
					+ v->mapv.shifty, 0,
					getcolorpix(v->img[i].addr, k, 0)},
					v->screen.resw, v->screen.resh);
			}
		}
	}
}

void	animations(t_vars *v)
{
	t_point	p;

	if (!MANDATORY && v->guard.guard)
	{
		if (v->guard.guarddir == EAST || v->guard.guarddir == NORTH)
			p = (t_point){0, 80, 3000, 0};
		else if (v->guard.guarddir == WEST || v->guard.guarddir == SOUTH)
			p = (t_point){1, 80, 3000, 0};
		if (v->guard.guardhit)
			p = (t_point){(v->guard.movingguard = 0, 2 + p.x), 96, 10000, 0};
		if (v->guard.guarddeath)
			p = (t_point){(v->guard.movingguard = 0, 4 + p.x), 96, 10000, 0};
		// guardanim(v, p);
	}
	// playeranim(v, 0);
	// objanim(v, -1);
}

void	displaytopdown(t_vars *v)
{
	t_point	p;
	t_point	d;

	p.y = -1;
	while (++(p.y) < v->img[EMAP].height)
	{
		p.x = -1;
		while (++(p.x) < v->img[EMAP].width)
		{
			d.x = p.x;
			d.y = p.y;
			img_pix_put(&v->img[EMAP], (t_point){d.x, d.y + v->mouse.yoff, 0,
				getcolorpix(v->img[COMP_N].addr,
					(p.y * v->img[COMP_N].len) + (p.x * 4), v->game.pause)},
				v->screen.resw, v->screen.resh);
		}
	}
	// if (!v->game.pause)
	// 	animations(v);
	rendermenu(v);
}

static void	render_entities(t_vars *v, t_map *tmp, t_point i)
{
	// static int	j = -1;

	if (v->game.refreshmap)
		puttextures(v, i.x, i.y, i.z);
	if (v->game.start == 2 && (tmp->val == E || tmp->val == W || tmp->val == N || tmp->val == S))
	{
		v->img[ESPAWN].posx = i.z;
		v->img[ESPAWN].posy = i.y;
	}
	// if (v->game.start == 2 && tmp->val == GUARD)
	// {
	// 	v->img[EGUARD].posx = i.z;
	// 	v->img[EGUARD].posy = i.y;
	// }
	// if (v->game.refreshmap && tmp->val == EXIT)
	// 	puttextures(v, EEXIT, i.y - 100, i.z + 1);
	// else if (v->objs.initobjs == 0 && tmp->val == COLLECT)
	// {
	// 	v->objs.objs[++(j)] = (t_point){i.z, i.y, 0, ECOLLECT};
	// 	if (j == v->objs.collect - 1)
	// 	{
	// 		v->objs.initobjs = 1;
	// 		j = -1;
	// 	}
	// }
}

void	topdown(t_vars *v, t_map *tmp, int prevw, int prevh)
{
	int	i;

	i = 1;
	// (void)v;
	// (void)prevw;
	// (void)prevh;
	while (tmp)
	{
		if (getindex(v, &i, tmp) && i < 0)
		{
			prevw += v->img[EWALL].width;
			if (tmp->right && tmp->right->x == 0)
			{
				prevw = 7;
				prevh += v->img[EWALL].height;
			}
			tmp = tmp->right;
			continue ;
		}
		render_entities(v, tmp, (t_point){i, prevh, prevw, 0});
		prevw += v->img[i].width;
		if (tmp->right && tmp->right->x == 0)
		{
			prevw = 7;
			prevh += v->img[i].height;
		}
		tmp = tmp->right;
	}
}
