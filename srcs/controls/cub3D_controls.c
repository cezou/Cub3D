/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_controls.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 18:24:52 by pmagnero          #+#    #+#             */
/*   Updated: 2024/04/05 18:13:58 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	hotreload(t_vars *v)
{
	loading(v);
	if (v->mapv.map)
		map_clear(v->mapv.map);
	v->game.start = 2;
	initvars(v);
	// clearimgs(v);
	// inittextures(v, 0);
	// initplayeranim(v, -1);
	// initobjectsanim(v, 0, ECOLLECT);
	// initguardanim(v, -1);
	parse(v, -1, NULL);
	init_player_dir(v);
	// flood_fill(v, &v->player.player, &v->player.pocket);
	// if (!v->mapv.mapvalid || v->player.pocket != v->objs.collect)
	// 	exit((prterr(v, ERRFF, 1, 1), 1));
	v->player.pocket = 0;
	ma_sound_stop(&v->sound.sound[ECRED]);
	if (ACTIVATE_SOUND && !ma_sound_is_playing(&v->sound.sound[2]))
	{
		ma_sound_set_looping(&v->sound.sound[2], 1);
		ma_sound_start(&v->sound.sound[2]);
	}
	// init_cam(v);
	mlx_loop_end((v->game.won = 0, v->mlx));
}

void	resetpos(t_vars *v, int renderb)
{
	mlx_clear_window(v->mlx, v->screen.win);
	v->mouse.xoff = 0;
	v->mouse.yoff = 0;
	v->mouse.xangle = -0.1515472907;
	v->mouse.yangle = -0.523599;
	v->mouse.zangle = 0.1515472907;
	v->mouse.zheight = 1;
	v->mapv.shiftx = -(v->player.player->x * v->img[EWALL].width
			/ v->screen.resw) * v->screen.resw;
	v->mapv.resdeltax = (v->player.player->x * v->img[EWALL].width
			/ v->screen.resw) + 1;
	v->mapv.shifty = -(v->player.player->y * v->img[EWALL].height
			/ v->screen.resh) * v->screen.resh;
	v->mapv.resdeltay = (v->player.player->y * v->img[EWALL].height
			/ v->screen.resh) + 1;
	v->mouse.zoom = 1;
	v->game.refreshmap = 1;
	v->game.start = 2;
	if (renderb)
		(ft_printf(1, "Reset View\n"));
	render(v);
}

void	menuexit(t_vars *v)
{
	if (MANDATORY || v->game.won > 0)
		exit((cleardata(v, 1), 0));
	if (v->menu.menu == 2)
	{
		v->menu.menu = 0;
		v->game.pause = 0;
		v->menu.menui = 0;
		return ;
	}
	if (v->game.start > 2)
	{
		v->game.pause = 1;
		v->menu.menu = 2;
	}
}

void	menuoptions(t_vars *v)
{
	if (v->game.start > 2)
	{
		v->game.pause = 1;
		v->menu.menu = 3;
		v->menu.menui = 0;
	}
}

void	attack(t_vars *v)
{
	if (v->game.won == 2 || v->game.won == 1)
	{
		if (ACTIVATE_SOUND)
		{
			ma_sound_set_looping(&v->sound.sound[ECRED], MA_TRUE);
			ma_sound_set_fade_start_in_milliseconds(&v->sound.sound[ECRED],
				0.0f, 0.8f, 3000, 3000);
			ma_sound_start(&v->sound.sound[ECRED]);
		}
		mlx_loop_end((v->game.won = 3, v->mlx));
	}
	if (!v->game.won)
	{
		v->player.animp = EATTACK;
		v->proj.dirproj = v->player.dir;
		if (ACTIVATE_SOUND)
		{
			if (ma_sound_is_playing(&v->sound.sound[EATT]))
				ma_sound_seek_to_pcm_frame((ma_sound_stop(
							&v->sound.sound[EATT]), &v->sound.sound[EATT]), 0);
			ma_sound_start(&v->sound.sound[EATT]);
		}
		render((v->player.pattack = 1, v->proj.atttravel = 1, v));
	}
}
