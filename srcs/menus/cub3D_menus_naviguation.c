/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_menus_naviguation.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 18:24:52 by pmagnero          #+#    #+#             */
/*   Updated: 2024/04/05 12:19:12 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	menuarrowdown(t_vars *v)
{
	v->menu.menui++;
	if (v->menu.menu == 1 && v->menu.menui > 3)
		v->menu.menui = 0;
	else if (v->menu.menu == 2 && v->menu.menui > 3)
		v->menu.menui = 0;
}

void	menuarrowup(t_vars *v)
{
	v->menu.menui--;
	if (v->menu.menu == 1 && v->menu.menui < 0)
		v->menu.menui = 3;
	else if (v->menu.menu == 2 && v->menu.menui < 0)
		v->menu.menui = 3;
}

void	menuarrowleft(t_vars *v)
{
	if (ACTIVATE_SOUND)
	{
		v->sound.volume += 0.2f;
		if (v->sound.volume >= 5.0f)
		{
			v->sound.volume = 5.0f;
			return ;
		}
		ma_engine_set_volume(&v->sound.engine, v->sound.volume);
	}
}

void	menuarrowright(t_vars *v)
{
	if (ACTIVATE_SOUND)
	{
		v->sound.volume -= 0.2f;
		if (v->sound.volume <= 0)
		{
			v->sound.volume = 0;
			return ;
		}
		ma_engine_set_volume(&v->sound.engine, v->sound.volume);
	}
}

void	menuarrow(t_vars *v, int d)
{
	if (v->menu.menu != 3 && d == SOUTH)
		menuarrowdown(v);
	else if (v->menu.menu != 3 && d == NORTH)
		menuarrowup(v);
	else if (v->menu.menu == 3 && d == EAST)
		menuarrowleft(v);
	else if (v->menu.menu == 3 && d == WEST)
		menuarrowright(v);
	else
		return ;
	if (ACTIVATE_SOUND && v->sound.volume > 0 && v->sound.volume < 5.0f)
	{
		ma_sound_is_playing(&v->sound.sound[EBUTTC2]);
		ma_sound_stop(&v->sound.sound[EBUTTC2]);
		ma_sound_start(&v->sound.sound[EBUTTC2]);
	}
	v->game.refreshmap = 0;
	render(v);
}
