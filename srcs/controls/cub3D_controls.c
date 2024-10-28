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

void	menuexit(t_vars *v)
{
	if (v->game.won < 4 && (MANDATORY || v->game.won > 0))
		exit((mlx_do_key_autorepeaton(v->mlx), cleardata(v, 1), 0));
	v->hud.refreshammo = 1;
	v->hud.refreshcards = 1;
	v->hud.refreshammun = 1;
	v->hud.refresharmor = 1;
	v->hud.refreshhealth = 1;
	v->hud.refreshdh = 1;
	v->hud.refreshweapon = 1;
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

// void	attack(t_vars *v)
// {
// 	if (v->game.won == 2 || v->game.won == 1)
// 	{
// 		if (ACTIVATE_SOUND)
// 		{
// 			ma_sound_set_looping(&v->sound.sound[ECRED], MA_TRUE);
// 			ma_sound_set_fade_start_in_milliseconds(&v->sound.sound[ECRED],
// 				0.0f, 0.8f, 3000, 3000);
// 			ma_sound_start(&v->sound.sound[ECRED]);
// 		}
// 		mlx_loop_end((v->game.won = 3, v->mlx));
// 	}
// 	if (!v->game.won)
// 	{
// 		v->player.animp = EATTACK;
// 		v->proj.dirproj = v->player.dir;
// 		if (ACTIVATE_SOUND)
// 		{
// 			if (ma_sound_is_playing(&v->sound.sound[EATT]))
// 				ma_sound_seek_to_pcm_frame((ma_sound_stop(
// 							&v->sound.sound[EATT]), &v->sound.sound[EATT]), 0);
// 			ma_sound_start(&v->sound.sound[EATT]);
// 		}
// 		render((v->player.pattack = 1, v->proj.atttravel = 1, v));
// 	}
// }
