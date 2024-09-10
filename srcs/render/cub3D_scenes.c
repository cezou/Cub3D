/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_scenes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 09:51:53 by pmagnero          #+#    #+#             */
/*   Updated: 2024/06/10 10:16:29 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	win(t_vars *v)
{
	if (!v->screen.win || timestamp_in_ms(v) - v->game.updated_at
		< (uint64_t)(1000 / v->game.fps))
		return (1);
	v->game.updated_at = timestamp_in_ms(v);
	if (ACTIVATE_SOUND && v->game.updated_at >= (uint64_t)(1000 / v->game.fps))
	{
		if (ma_sound_is_playing(&v->sound.sound[2]))
			ma_sound_stop(&v->sound.sound[2]);
		ma_sound_set_fade_start_in_milliseconds(&v->sound.sound[EWIN],
			0.0f, 0.8f, 3000, 3000);
		ma_sound_start(&v->sound.sound[EWIN]);
	}
	mlx_clear_window(v->mlx, v->screen.win);
	mlx_set_font(v->mlx, v->screen.win, v->img->fontname2);
	mlx_string_put(v->mlx, v->screen.win,
		v->screen.resw * 0.40, v->screen.resh / 2, G_P,
		"CONGRATULATIONS, YOU WON");
	mlx_do_sync(v->mlx);
	return (0);
}

int	lose(t_vars *v)
{
	if (!v->screen.win || timestamp_in_ms(v) - v->game.updated_at
		< (uint64_t)(1000 / v->game.fps))
		return (1);
	v->game.updated_at = timestamp_in_ms(v);
	if (ACTIVATE_SOUND && v->game.updated_at >= (uint64_t)(1000 / v->game.fps))
	{
		if (ma_sound_is_playing(&v->sound.sound[2]))
			ma_sound_stop(&v->sound.sound[2]);
		ma_sound_set_fade_start_in_milliseconds(&v->sound.sound[ELOSE],
			0.0f, 0.8f, 3000, 3000);
		ma_sound_start(&v->sound.sound[ELOSE]);
	}
	mlx_clear_window(v->mlx, v->screen.win);
	mlx_set_font(v->mlx, v->screen.win, v->img->fontname2);
	mlx_string_put(v->mlx, v->screen.win,
		v->screen.resw * 0.45, v->screen.resh / 2, R_P,
		"GAME OVER");
	mlx_do_sync(v->mlx);
	return (0);
}

int	credits(t_vars *v)
{
	static float	h = 0;
	int				rh;

	rh = v->screen.resh;
	if (!v->screen.win || timestamp_in_ms(v) - v->game.updated_at
		< (uint64_t)(1000 / v->game.fps))
		return (1);
	v->game.updated_at = timestamp_in_ms(v);
	mlx_do_sync((mlx_clear_window(v->mlx, v->screen.win), v->mlx));
	scrolling(v, &h, "PRODUCER AND DIRECTED BY",
		(t_point2){0.395f, rh + 155, 1, BU_P});
	scrolling(v, &h, "MAGNERON PIERRE", (t_point2){0.435f, rh + 185, 0, W_P});
	scrolling(v, &h, "WRITTEN BY", (t_point2){0.435f, rh + 285, 1, BU_P});
	scrolling(v, &h, "MAGNERON PIERRE", (t_point2){0.435f, rh + 315, 0, W_P});
	scrolling(v, &h, "MUSIC BY", (t_point2){0.44f, rh + 415, 1, BU_P});
	scrolling(v, &h, "INTERNET", (t_point2){0.45f, rh + 445, 0, W_P});
	scrolling(v, &h, "GAME DESIGNER", (t_point2){0.425f, rh + 545, 1, BU_P});
	scrolling(v, &h, "MAGNERON PIERRE", (t_point2){0.435f, rh + 575, 0, W_P});
	scrolling(v, &h, "ART DIRECTOR", (t_point2){0.428f, rh + 675, 1, BU_P});
	scrolling(v, &h, "MAGNERON TIKIN", (t_point2){0.435f, rh + 705, 0, W_P});
	scrolling(v, &h, "SOUND DIRECTOR", (t_point2){0.425f, rh + 805, 1, BU_P});
	scrolling(v, &h, "MAGNERON PIERRE", (t_point2){0.435f, rh + 835, 0, W_P});
	scrolling(v, &h, "PROGRAM DIRECTOR", (t_point2){0.42f, rh + 935, 1, BU_P});
	scrolling(v, &h, "MAGNERON PIERRE", (t_point2){0.435f, rh + 965, 0, W_P});
	return (scrolling(v, &h, "STAFF", (t_point2){0.45f, rh, 1, R_P}), 0);
}

void	loading(t_vars *v)
{
	mlx_clear_window(v->mlx, v->screen.win);
	mlx_set_font(v->mlx, v->screen.win, v->img->fontname2);
	if (ACTIVATE_SOUND && ma_sound_is_playing(&v->sound.sound[2]))
		ma_sound_stop(&v->sound.sound[2]);
	mlx_string_put(v->mlx, v->screen.win,
		v->screen.resw * 0.45, v->screen.resh * 0.90, W_P, "Loading...");
	mlx_set_font(v->mlx, v->screen.win, v->img->fontname);
	mlx_do_sync(v->mlx);
}

int	maintitleanim(t_vars *v)
{
	if (!v->screen.win || timestamp_in_ms(v) - v->game.updated_at
		< (uint64_t)(1000 / v->game.fps))
		return (1);
	v->game.updated_at = timestamp_in_ms(v);
	mlx_do_sync((mlx_clear_window(v->mlx, v->screen.win), v->mlx));
	mlx_set_font(v->mlx, v->screen.win, v->img->fontname2);
	if (ACTIVATE_SOUND && !ma_sound_is_playing(&v->sound.sound[0]))
	{
		ma_sound_set_volume(&v->sound.sound[0], 0.5f);
		ma_sound_start(&v->sound.sound[0]);
	}
	mlx_put_image_to_window(v->mlx, v->screen.win,
		v->img[ETITLE].img, v->screen.resw / 2 - v->img[ETITLE].width / 2,
		v->img[ETITLE].height * 0.15);
	mlx_string_put(v->mlx, v->screen.win,
		v->screen.resw * 0.45, v->screen.resh * 0.80, W_P, "Press Enter");
	if (v->game.start == 1)
	{
		mlx_set_font(v->mlx, v->screen.win, v->img->fontname2);
		mlx_string_put(v->mlx, v->screen.win,
			v->screen.resw * 0.44, v->screen.resh * 0.75, R_P,
			"Are you ready ?");
		mlx_set_font(v->mlx, v->screen.win, v->img->fontname);
	}
	return (0);
}
