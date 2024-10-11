/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:14:16 by cviegas           #+#    #+#             */
/*   Updated: 2024/10/11 17:22:46 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

bool	is_pressed(int key, t_vars *v)
{
	if (v->keys[key])
		return (1);
	return (0);
}

int	returnkey(t_vars *v)
{
	if ((v->menu.menu == 1 && v->menu.menui == 3) || (v->menu.menu == 2
			&& v->menu.menui == 3))
		exit((cleardata(v, 1), 0));
	if ((v->menu.menu == 2 && v->menu.menui == 0))
		menuoptions(v);
	v->game.start++;
	if (v->game.start > 3)
		v->game.start = 3;
	if (v->game.start == 2 && v->game.won == 0)
	{
		raycasting(v, v->img[EMAP]);
		rendermenu(v);
		render_player(v, (t_point){0});
		renderhud(v, v->img[EHUD]);
		save_screen_to_buffer(v->img[EBUFF], v->img[EMAP], 0);
		mlx_loop_end((v->game.won = 4, v->mlx));
	}
	return (0);
}

void	key_management(t_vars *v)
{
	if (v->game.start > 1 && ACTIVATE_SOUND
		&& !ma_sound_is_playing(&v->sound.sound[2]))
	{
		ma_sound_stop(&v->sound.sound[0]);
		ma_sound_set_looping(&v->sound.sound[2], MA_TRUE);
		ma_sound_set_fade_start_in_milliseconds(&v->sound.sound[2], 0.0f, 0.8f,
			3000, 3000);
		ma_sound_start(&v->sound.sound[2]);
		mlx_loop_end(v->mlx);
	}
	if (!v->player.moving && v->hud.animoff != v->hud.head.animx)
	{
		v->hud.refreshdh = 1;
		v->hud.animoff = v->hud.head.animx;
	}
	if (v->game.start > 1 && v->game.god && is_pressed(XK_m, v))
		hotreload(v);
	if (!v->game.won && v->game.won != 4 && v->game.start > 1)
		handle_movement(v);
}
