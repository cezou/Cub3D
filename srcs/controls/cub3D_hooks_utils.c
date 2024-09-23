/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_hooks_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:07:21 by pmagnero          #+#    #+#             */
/*   Updated: 2024/09/23 01:52:25 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	closecross(t_vars *v)
{
	mlx_do_key_autorepeaton(v->mlx);
	exit((cleardata(v, 1), 0));
	return (0);
}

int	keys_release(int keycode, t_vars *v)
{
	v->keys[keycode] = false;
	if (v->game.start > 1 && ACTIVATE_SOUND && (keycode == XK_w
			|| keycode == XK_a || keycode == XK_s || keycode == XK_d))
		ma_sound_stop(&v->sound.sound[1]);
	return (0);
}
