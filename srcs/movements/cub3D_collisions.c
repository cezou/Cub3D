/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_collisions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 18:24:52 by pmagnero          #+#    #+#             */
/*   Updated: 2024/04/05 12:19:12 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static void	playcollectingsound(t_vars *v)
{
	int	j;

	j = EBABY1 - 1;
	if (ACTIVATE_SOUND)
	{
		while (++j <= EBABY3)
		{
			if (ma_sound_is_playing(&v->sound.sound[j]))
			{
				ma_sound_stop(&v->sound.sound[j]);
				ma_sound_seek_to_pcm_frame(&v->sound.sound[j], 0);
			}
		}
		ma_sound_start(&v->sound.sound[EBABY1 + myrand(3)]);
	}
}

void	iscollected(t_vars *v, int i, int ent, t_point p)
{
	p.x = v->img[ent].posx + v->img[ent].xdelta;
	p.y = v->img[ent].posy + v->img[ent].ydelta;
	while (++i < v->objs.collect)
	{
		p.z = v->objs.objs[i].x + v->img[ESPACE].width / 2;
		p.color = v->objs.objs[i].y + v->img[ESPACE].height / 2;
		if (v->objs.objs[i].z != 1 && p.x <= p.z + 30 && p.x + 62 >= p.z
			&& p.y <= p.color + v->img[ECOLLECT].height
			&& p.y + v->img[ent].height >= p.color)
		{
			if (ent == ESPAWN)
			{
				playcollectingsound((v->player.pocket++,
						v->objs.objs[i].z = 1, v));
				return (v->player.player->val = SPAWN, (void)v);
			}
			else
			{
				v->player.pocket--;
				v->objs.objs[i].z = 1;
				v->guard.guard->val = GUARD;
			}
		}
	}
}

int	checkhitmonster(t_vars *v, t_point p)
{
	int			ow;
	int			oh;

	ow = v->img[EGUARD].posx + v->img[EGUARD].xdelta;
	oh = v->img[EGUARD].posy + v->img[EGUARD].ydelta;
	if (!v->guard.guardhit && p.x <= ow + 80 && p.x + p.z >= ow
		&& p.y <= oh + v->img[EGUARD].height
		&& p.y + v->img[p.color].height >= oh)
	{
		if (p.color == EPROJ)
		{
			v->proj.atttravelframe = 300;
			if (v->guard.guardhp-- < 0)
				if (ACTIVATE_SOUND)
					return (ma_sound_start(&v->sound.sound[EGUARDD]),
						v->guard.guarddeath = 1, 1);
			v->guard.guardhit = 1;
			if (ACTIVATE_SOUND)
				ma_sound_start(&v->sound.sound[EGUARDI]);
			return (1);
		}
		else
			return (mlx_loop_end((v->game.won = 2, v->mlx)), 1);
	}
	return (0);
}

int	checkcollisionsprojectiles(t_vars *v, t_point dir)
{
	int		px;
	int		py;
	t_map	*map;

	map = v->mapv.map;
	px = v->img[ESPAWN].posx + v->img[ESPAWN].xdelta + 15
		+ v->img[EPROJ].anim[v->proj.dirproj].xdelta
		+ v->proj.atttravelframe * dir.color;
	py = v->img[ESPAWN].posy + v->img[ESPAWN].ydelta + 20
		+ v->img[EPROJ].anim[v->proj.dirproj].ydelta
		+ v->proj.atttravelframe * dir.y;
	while (map)
	{
		if (map->x == px / v->img[ESPACE].width
			&& map->y == py / v->img[ESPACE].height)
			break ;
		map = map->right;
	}
	if ((map && map->val == WALL) || !map)
		return (v->proj.atttravelframe = 300, 1);
	return (checkhitmonster(v, (t_point){px, py, 35, EPROJ}));
}
