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

// /// @brief Display strings on the screen
// /// @param v Vars
// /// @param str String
// /// @param str2 String
// void	displaytext(t_vars *v, char *str, char *str2)
// {
// 	(void)str;
// 	(void)str2;
// 	if (v->game.god)
// 	{
// 		// mlx_string_put(v->mlx, v->screen.win, 50, 50, W_P, "[ESC] Exit");
// 	// mlx_string_put(v->mlx, v->screen.win, 50, 70, W_P, "Zoom: Mouse wheel");
// 	// mlx_string_put(v->mlx, v->screen.win, 50, 90, W_P, "Drag: Mouse");
// 	// mlx_string_put(v->mlx, v->screen.win, 50, 110, W_P, "[r] Reset view");
// 	// mlx_string_put(v->mlx, v->screen.win, 50, 170, W_P, "[F5] Hotreload");
// 	// mlx_string_put(v->mlx, v->screen.win, 50, 190, W_P, "[F1] GOD mode");
// 	}
// }

/// @brief Init the random melting array that store the delay of each columns
/// @param v Vars
void	init_random_melting_array(t_vars *v)
{
	int	r;
	int	i;
	int	w;

	v->tmp[0] = v->img[COMP_N];
	v->tmp[1] = v->img[EBUFF];
	w = v->tmp[0].width / 5;
	i = 0;
	v->rand = (int *)malloc(sizeof(int) * w);
	if (!v->rand)
		exit((prterr(v, ERRMALL, 1, 1), 1));
	v->rand[0] = -(m_random(v) % 16);
	while (++i < w)
	{
		r = (m_random(v) % 3) - 1;
		v->rand[i] = v->rand[i - 1] + r;
		if (v->rand[i] > 0)
			v->rand[i] = 0;
		else if (v->rand[i] == -16)
			v->rand[i] = -15;
	}
}

/// @brief Melting effect like in Doom original.
///	We use the random array for each column of the screen
///	and delay the drop of each column. If the column value is not 0 in the array
///	we delay it.
/// @param v Vars
/// @param done Is the wipe done
/// @param x Iterator for the loop =-1
void	melting(t_vars *v, bool *done, int x)
{
	t_point	p;
	int		d;

	p.x = -1;
	while (++p.x < v->tmp[0].width)
	{
		p.y = -1;
		x = p.x / 5;
		if (x >= v->tmp[0].width / 5)
			x = v->tmp[0].width / 5 - 1;
		while (++p.y < v->tmp[0].height)
		{
			d = p.y + v->rand[x] * 20;
			if (p.y == v->tmp[0].height - 1 && p.x % 5 == 4)
				v->rand[x] += 1;
			if (d >= v->tmp[0].height - 1)
				continue ;
			if (v->rand[x] < 0)
				d = p.y;
			p.z = (p.y * v->tmp[0].len) + (p.x * 4);
			add_pix((*done = false, v), (t_point){p.x, d, p.z, getcolorpix(v,
					v->tmp[0].addr, p.z)}, (t_point3){0}, (t_point){0, 1, 0,
				0});
		}
	}
}

/// @brief Game loop that render the game on the screen at fps rate
/// @param v Vars
/// @return
int	render(t_vars *v)
{
	v->hud.refreshfps = 1;
	key_management(v);
	raycasting(v, v->img[EBUFF]);
	render_player(v, (t_point){0});
	rendermenu(v);
	renderhud(v, v->img[EBUFF]);
	if (!v->game.god)
		rendermap(v);
	update_animations(v);
	mlx_put_image_to_window(v->mlx, v->screen.win, v->img[EBUFF].img, 0, 0);
	v->player.attack = 0;
	v->game.oldtime = v->game.time;
	v->game.time = timestamp_in_ms(v);
	v->game.frametime = (v->game.time - v->game.oldtime) / 1000.0;
	if (v->game.frametime > 0.0f)
		v->game.fps = (int)(1.0 / v->game.frametime);
	return (v->game.start++, 0);
}

// if (!v->screen.win || v->game.won > 0 || !v->game.start
// 	|| timestamp_in_ms(v) - v->game.updated_at < (uint64_t)(1000
// 	/ v->game.fps))
// 	return (1);
// v->game.updated_at = timestamp_in_ms(v);
//	displaytext(v, NULL, NULL)
// save_screen_to_buffer(v->img[EBUFF], v->img[EMAP], 0);
// mlx_clear_window(v->mlx, v->screen.win);
// mlx_put_image_to_window(v->mlx, v->screen.win, v->img[EHUD].img, 0, 0);

// printf("%f\n", 1.0 / v->game.frametime);
// ft_bzero(v->img[EMAP].addr, v->screen.gamew * v->screen.gameh
// 	* (v->img[EMAP].bpp / 8));