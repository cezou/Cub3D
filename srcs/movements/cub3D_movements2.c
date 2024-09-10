/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_movements2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 18:24:52 by pmagnero          #+#    #+#             */
/*   Updated: 2024/09/09 16:01:53 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

// static void	shiftmaphor(t_vars *v, t_point d, int b)
// {
// 	if (d.color == EAST
// 		&& (v->img[ESPAWN].posx + v->img[ESPAWN].xdelta + d.z) * v->mouse.zoom
// 		>= v->screen.resw * v->mapv.resdeltax)
// 	{
// 		b = 1;
// 		v->mapv.shiftx += -v->screen.resw;
// 		v->mapv.resdeltax++;
// 	}
// 	else if (d.color == WEST
// 		&& (v->img[ESPAWN].posx + v->img[ESPAWN].xdelta + d.z) * v->mouse.zoom
// 		<= v->screen.resw * (v->mapv.resdeltax - 1))
// 	{
// 		b = 1;
// 		v->mapv.shiftx += v->screen.resw;
// 		v->mapv.resdeltax--;
// 	}
// 	if (b == 1)
// 	{
// 		v->img[ESPAWN].xdelta = 60;
// 		v->img[ESPAWN].ydelta = 0;
// 		v->img[EGUARD].xdelta = 0;
// 		v->img[EGUARD].ydelta = 0;
// 		render((v->game.refreshmap = 1, v->game.start = 2, v));
// 	}
// }

// static void	shiftmapvert(t_vars *v, t_point d, int b)
// {
// 	if (d.color == NORTH
// 		&& (v->img[ESPAWN].posy + v->img[ESPAWN].ydelta + d.z) * v->mouse.zoom
// 		<= v->screen.resh * (v->mapv.resdeltay - 1))
// 	{
// 		b = 1;
// 		v->mapv.shifty += v->screen.resh;
// 		v->mapv.resdeltay--;
// 	}
// 	else if (d.color == SOUTH
// 		&& (v->img[ESPAWN].posy + v->img[ESPAWN].ydelta + d.z) * v->mouse.zoom
// 		>= v->screen.resh * (v->mapv.resdeltay))
// 	{
// 		b = 1;
// 		v->mapv.shifty += -v->screen.resh;
// 		v->mapv.resdeltay++;
// 	}
// 	if (b == 1)
// 	{
// 		v->img[ESPAWN].xdelta = 60;
// 		v->img[ESPAWN].ydelta = 0;
// 		v->img[EGUARD].xdelta = 0;
// 		v->img[EGUARD].ydelta = 0;
// 		render((v->game.refreshmap = 1, v->game.start = 2, v));
// 	}
// }

static void	kek(t_vars *v, t_map *dir, int ent, int d)
{
	// d++;
	(void)dir;
	(void)v;
	// printmap2(v);
	// if (ent == ESPAWN && dir->val == EXIT
	// 	&& v->player.pocket == v->objs.collect)
	// 	mlx_loop_end((v->game.won = 1, v->mlx));
	// if (ent == ESPAWN && dir->val == EXIT
	// 	&& v->player.pocket != v->objs.collect)
	// 	mlx_loop_end((v->game.won = 2, v->mlx));
	if (ent == ESPAWN)
	{
		if (v->player.player->val == N || v->player.player->val == S
			|| v->player.player->val == E || v->player.player->val == W)
			v->player.player->val = SPACE;
		v->player.player = dir;
		if (v->player.player->val == SPACE)
			v->player.player->val = d;
		// ft_printf(1, "\anb of movement: %d\n", ++v->player.nbmove);
	}
	// else
	// {
	// 	if (v->guard.guard->val == GUARD)
	// 		v->guard.guard->val = SPACE;
	// 	v->guard.guard = dir;
	// 	if (v->guard.guard->val == SPACE)
	// 		v->guard.guard->val = GUARD;
	// }
}

void	moveshor(t_vars *v, t_map *dir, t_point d, int ent)
{
	// if (ent == ESPAWN)
	// 	shiftmaphor(v, d, 0);
	// if (d.y && floor((v->img[ent].posx + v->img[ent].xdelta + d.z)
	// 		/ v->img[EWALL].width) == dir->x)
	// {
		if (dir->val != WALL)
			kek(v, dir, ent, d.color);
		else
			v->img[ent].xdelta += d.x;
	// }
	// if (ent == EGUARD && (dir->val == COLLECT
	// 		|| v->guard.guard->val == COLLECT))
	// 	iscollected(v, -1, EGUARD, (t_point){0});
	// if (ent == EGUARD && (dir->val == SPAWN || v->guard.guard->val == SPAWN))
	// 	checkhitmonster(v,
	// 		(t_point){v->img[ESPAWN].posx + v->img[ESPAWN].xdelta,
	// 		v->img[ESPAWN].posy + v->img[ESPAWN].ydelta, 40, ESPAWN});
}

void	movesvert(t_vars *v, t_map *dir, t_point d, int ent)
{
	// if (ent == ESPAWN)
	// 	shiftmapvert(v, d, 0);
	// if (!d.y && floor((v->img[ent].posy + v->img[ent].ydelta + d.z)
	// 		/ v->img[EWALL].height) == dir->y)
	// {
		if (dir->val != WALL)
			kek(v, dir, ent, d.color);
		else
			v->img[ent].ydelta += d.x;
	// }
	// if (ent == EGUARD && (dir->val == COLLECT
	// 		|| v->guard.guard->val == COLLECT))
	// 	iscollected(v, -1, EGUARD, (t_point){0});
	// if (ent == EGUARD && (dir->val == SPAWN || v->guard.guard->val == SPAWN))
	// 	checkhitmonster(v,
	// 		(t_point){v->img[ESPAWN].posx + v->img[ESPAWN].xdelta,
	// 		v->img[ESPAWN].posy + v->img[ESPAWN].ydelta, 40, ESPAWN});
}
