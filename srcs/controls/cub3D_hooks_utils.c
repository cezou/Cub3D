/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_hooks_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:07:21 by pmagnero          #+#    #+#             */
/*   Updated: 2024/10/01 12:19:11 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/// @brief Hook function when the user press the exit cross of the window.
/// @param v Vars
/// @return 0
int	closecross(t_vars *v)
{
	exit((cleardata(v, 1), 0));
	return (0);
}

/// @brief Hook function when the key is released.
/// @param keycode Keyboard key released
/// @param v Vars
/// @return 0
int	keys_release(int keycode, t_vars *v)
{
	if (v->keys[XK_w] && !v->keys[XK_a] && !v->keys[XK_s] && !v->keys[XK_d])
		v->player.dir = NORTH;
	else if (!v->keys[XK_w] && v->keys[XK_a]
		&& !v->keys[XK_s] && !v->keys[XK_d])
		v->player.dir = WEST;
	else if (!v->keys[XK_w] && !v->keys[XK_a]
		&& v->keys[XK_s] && !v->keys[XK_d])
		v->player.dir = SOUTH;
	else if (!v->keys[XK_w] && !v->keys[XK_a]
		&& !v->keys[XK_s] && v->keys[XK_d])
		v->player.dir = EAST;
	v->keys[keycode] = false;
	if (!v->keys[XK_w] && !v->keys[XK_a] && !v->keys[XK_s] && !v->keys[XK_d])
		v->player.moving = 0;
	if (v->game.start > 1 && ACTIVATE_SOUND && (keycode == XK_w
			|| keycode == XK_a || keycode == XK_s || keycode == XK_d))
		ma_sound_stop(&v->sound.sound[1]);
	return (0);
}
