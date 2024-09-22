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

/// @brief Action when Down arrow key is pressed
/// @param v Vars
void	menuarrowdown(t_vars *v)
{
	v->menu.menui++;
	if (v->menu.menu == 1 && v->menu.menui > 3)
		v->menu.menui = 0;
	else if (v->menu.menu == 2 && v->menu.menui > 3)
		v->menu.menui = 0;
}

/// @brief Action when Up arrow key is pressed
/// @param v Vars
void	menuarrowup(t_vars *v)
{
	v->menu.menui--;
	if (v->menu.menu == 1 && v->menu.menui < 0)
		v->menu.menui = 3;
	else if (v->menu.menu == 2 && v->menu.menui < 0)
		v->menu.menui = 3;
}

/// @brief Action when Left arrow key is pressed
/// @param v Vars
void	menuarrowleft(t_vars *v)
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

/// @brief Action when Right arrow key is pressed
/// @param v Vars
void	menuarrowright(t_vars *v)
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

/// @brief Naviguate in the menus when an arrow key is pressed
/// @param v Vars
/// @param d Arrow key pressed
void	menuarrow(t_vars *v, int d)
{
	if (v->menu.menu != 3 && (d == XK_Down || d == XK_s))
		menuarrowdown(v);
	else if (v->menu.menu != 3 && (d == XK_Up || d == XK_w))
		menuarrowup(v);
	else if (v->menu.menu == 3 && (d == XK_Left || d == XK_a))
		menuarrowleft(v);
	else if (v->menu.menu == 3 && (d == XK_Right || d == XK_d))
		menuarrowright(v);
	else
		return ;
	if (ACTIVATE_SOUND && v->sound.volume > 0 && v->sound.volume < 5.0f)
	{
		ma_sound_is_playing(&v->sound.sound[EBUTTC2]);
		ma_sound_stop(&v->sound.sound[EBUTTC2]);
		ma_sound_start(&v->sound.sound[EBUTTC2]);
	}
	render(v);
}
