/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:14:07 by pmagnero          #+#    #+#             */
/*   Updated: 2024/04/05 12:19:12 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/// @brief Display strings on the screen
/// @param v Vars
/// @param str String
/// @param str2 String
void	displaytext(t_vars *v, char *str, char *str2)
{
	(void)str;
	(void)str2;
	if (v->game.god)
	{
		mlx_string_put(v->mlx, v->screen.win, 50, 50, W_P, "[ESC] Exit");
		mlx_string_put(v->mlx, v->screen.win, 50, 70, W_P, "Zoom: Mouse wheel");
		mlx_string_put(v->mlx, v->screen.win, 50, 90, W_P, "Drag: Mouse");
		mlx_string_put(v->mlx, v->screen.win, 50, 110, W_P, "[r] Reset view");
		mlx_string_put(v->mlx, v->screen.win, 50, 170, W_P, "[F5] Hotreload");
		mlx_string_put(v->mlx, v->screen.win, 50, 190, W_P, "[F1] GOD mode");
	}
}

/// @brief Game loop that render the game on the screen at fps rate
/// @param v Vars
/// @return
int	render(t_vars *v)
{
	if (!v->screen.win || v->game.won > 0 || !v->game.start
		|| timestamp_in_ms(v) - v->game.updated_at < (uint64_t)(1000
		/ v->game.fps))
		return (1);
	v->game.updated_at = timestamp_in_ms(v);
	if (v->game.start == 2 && ACTIVATE_SOUND
		&& !ma_sound_is_playing(&v->sound.sound[2]))
	{
		ma_sound_stop(&v->sound.sound[0]);
		ma_sound_set_looping(&v->sound.sound[2], MA_TRUE);
		ma_sound_set_fade_start_in_milliseconds(&v->sound.sound[2], 0.0f, 0.8f,
			3000, 3000);
		ma_sound_start(&v->sound.sound[2]);
		mlx_loop_end(v->mlx);
	}
	key_management(v);
	raycasting(v);
	renderhud(v);
	rendermenu(v);
	mlx_put_image_to_window(v->mlx, v->screen.win, v->img[EMAP].img, 0, 0);
	v->game.oldtime = v->game.time;
	v->game.time = timestamp_in_ms(v);
	v->game.frametime = (v->game.time - v->game.oldtime) / 1000.0;
	return (displaytext(v, NULL, NULL), v->game.start++, 0);
}
	// printf("%f\n", 1.0 / v->game.frametime);
	// ft_bzero(v->img[EMAP].addr, v->screen.gamew * v->screen.gameh
	// 	* (v->img[EMAP].bpp / 8));