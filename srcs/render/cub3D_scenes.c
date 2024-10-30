/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_scenes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 09:51:53 by pmagnero          #+#    #+#             */
/*   Updated: 2024/10/30 10:26:28 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/// @brief Win loop/screen to display when the player win
/// @param v Vars
/// @return
int	win(t_vars *v)
{
	if (!v->screen.win || timestamp_in_ms(v)
		- v->game.updated_at < (uint64_t)(100))
		return (1);
	v->game.updated_at = timestamp_in_ms(v);
	if (ACTIVATE_SOUND && v->game.updated_at >= (uint64_t)(100))
	{
		if (ma_sound_is_playing(&v->sound.sound[2]))
			ma_sound_stop(&v->sound.sound[2]);
		ma_sound_set_fade_start_in_milliseconds(&v->sound.sound[EWIN], 0.0f,
			0.8f, 3000, 3000);
		ma_sound_start(&v->sound.sound[EWIN]);
	}
	mlx_clear_window(v->mlx, v->screen.win);
	mlx_set_font(v->mlx, v->screen.win, v->img->fontname2);
	mlx_string_put(v->mlx, v->screen.win, v->screen.resw * 0.40, v->screen.resh
		/ 2, G_P, "CONGRATULATIONS, YOU WON");
	mlx_do_sync(v->mlx);
	return (0);
}

/// @brief Lose loop/screen to dsiplay when the player lose
/// @param v Vars
/// @return
int	lose(t_vars *v)
{
	if (!v->screen.win || timestamp_in_ms(v)
		- v->game.updated_at < (uint64_t)(100))
		return (1);
	v->game.updated_at = timestamp_in_ms(v);
	if (ACTIVATE_SOUND && v->game.updated_at >= (uint64_t)(100))
	{
		if (ma_sound_is_playing(&v->sound.sound[2]))
			ma_sound_stop(&v->sound.sound[2]);
		ma_sound_set_fade_start_in_milliseconds(&v->sound.sound[ELOSE], 0.0f,
			0.8f, 3000, 3000);
		ma_sound_start(&v->sound.sound[ELOSE]);
	}
	mlx_clear_window(v->mlx, v->screen.win);
	mlx_set_font(v->mlx, v->screen.win, v->img->fontname2);
	mlx_string_put(v->mlx, v->screen.win, v->screen.resw * 0.45, v->screen.resh
		/ 2, R_P, "GAME OVER");
	mlx_do_sync(v->mlx);
	return (0);
}

/// @brief Credits loop/screen to display at the end of the game
/// @param v Vars
/// @return
int	credits(t_vars *v)
{
	(void)v;
	return (0);
}

// if (!delta && timestamp_in_ms(v) - v->game.updated_at < (uint64_t)5000)
// 	return (mlx_put_image_to_window(v->mlx, v->screen.win,
// 			v->img[COMP_N].img, 0, 0), delta = 0, 1);
/// @brief Transition screen to display
/// @param v Vars
int	transition_melt_screen(t_vars *v)
{
	static bool	done = true;
	static int	delta = 0;

	done = true;
	(void)delta;
	if (!v->screen.win || timestamp_in_ms(v)
		- v->game.updated_at < (uint64_t)(4))
		return (delta = 1, 1);
	delta = 1;
	v->game.updated_at = timestamp_in_ms(v);
	ft_bzero(v->img[EBUFF].addr, v->screen.resw * v->screen.resh
		* (v->img[EBUFF].bpp / 8));
	save_screen_to_buffer(v->img[EBUFF], v->img[EMAP], 0);
	save_screen_to_buffer(v->img[EBUFF], v->img[EHUD], (v->img[EMAP].width
			* v->img[EMAP].height * (v->img[EMAP].bpp / 8)));
	v->tmp[0] = v->img[COMP_N];
	v->tmp[1] = v->img[EBUFF];
	melting(v, &done, -1);
	if (done)
		mlx_loop_end((v->game.won = 0, v->mlx));
	mlx_put_image_to_window(v->mlx, v->screen.win, v->img[EBUFF].img, 0, 0);
	return (0);
}
// mlx_set_font(v->mlx, v->screen.win, v->img->fontname2);
// mlx_string_put(v->mlx, v->screen.win, v->screen.resw * 0.45,
// v->screen.resh
// 	* 0.90, W_P, "Loading...");
// mlx_set_font(v->mlx, v->screen.win, v->img->fontname);

/// @brief Main title loop/screen displayed at the begining of the game
/// @param v Vars
/// @return
int	maintitleanim(t_vars *v)
{
	if (!v->screen.win || timestamp_in_ms(v)
		- v->game.updated_at < (uint64_t)(10))
		return (1);
	v->game.updated_at = timestamp_in_ms(v);
	mlx_set_font(v->mlx, v->screen.win, v->img->fontname2);
	if (ACTIVATE_SOUND && !ma_sound_is_playing(&v->sound.sound[0]))
	{
		ma_sound_set_volume(&v->sound.sound[0], 0.2f);
		ma_sound_start(&v->sound.sound[0]);
	}
	mlx_put_image_to_window(v->mlx, v->screen.win, v->img[ETITLE].img,
		v->screen.resw / 2 - v->img[ETITLE].width / 2, v->img[ETITLE].height
		* 0.15);
	mlx_string_put(v->mlx, v->screen.win, v->screen.resw * 0.45, v->screen.resh
		* 0.80, W_P, "Press Enter");
	if (v->game.start == 1)
	{
		mlx_set_font(v->mlx, v->screen.win, v->img->fontname2);
		mlx_string_put(v->mlx, v->screen.win, v->screen.resw * 0.44,
			v->screen.resh * 0.75, R_P, "Are you ready ?");
		mlx_set_font(v->mlx, v->screen.win, v->img->fontname);
	}
	return (0);
}
