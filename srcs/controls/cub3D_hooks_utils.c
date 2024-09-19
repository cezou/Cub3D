/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_hooks_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:07:21 by pmagnero          #+#    #+#             */
/*   Updated: 2024/09/16 10:29:37 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	closecross(t_vars *v)
{
	exit((cleardata(v, 1), 0));
	return (0);
}

int	keys_release(int keycode, t_vars *v)
{
	if (v->game.start > 1 && ACTIVATE_SOUND && (keycode == XK_w
			|| keycode == XK_a || keycode == XK_s || keycode == XK_d))
		ma_sound_stop(&v->sound.sound[1]);
	return (0);
}
