/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_raycasting_skybox.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 21:30:54 by pmagnero          #+#    #+#             */
/*   Updated: 2024/10/11 16:30:04 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3D.h"

/// @brief Set skybox datas
/// @param v Vars
static void	set_skybox(t_vars *v)
{
	v->ray.dir_x = v->player.dir_x - v->player.plane_x;
	v->ray.dir_y = v->player.dir_y - v->player.plane_y;
	v->ray.dir_x1 = v->player.dir_x + v->player.plane_x;
	v->ray.dir_y1 = v->player.dir_y + v->player.plane_y;
	v->ray.tx0 = (int)(-atan2(v->ray.dir_x, v->ray.dir_y)
			* (double)v->game.skybox.width / (2 * M_PI) * SKYBOX_REPEATS);
	v->ray.tx1 = (int)(-atan2(v->ray.dir_x1, v->ray.dir_y1)
			* (double)v->game.skybox.width / (2 * M_PI) * SKYBOX_REPEATS);
	while (v->ray.tx1 < v->ray.tx0)
		v->ray.tx1 += v->game.skybox.width;
	while (v->ray.tx0 < 0)
	{
		v->ray.tx0 += v->game.skybox.width;
		v->ray.tx1 += v->game.skybox.width;
	}
	v->ray.dtx = v->ray.tx1 - v->ray.tx0;
	v->ray.dy = v->screen.gameh / 2 + v->ray.pitch;
	v->ray.dty = v->game.skybox.height * (v->screen.gameh / 2 + v->ray.pitch)
		/ (v->screen.gameh / 2 + v->screen.gameh / 2) - 1;
	v->ray.ty0 = v->game.skybox.height - 1 - v->ray.dty;
}

/// @brief Go through the rows of the screen and add pixels to the buffer
/// @param v Vars
/// @param p Pixel to add to the buffer
/// @param tx Texture x coordinate
/// @param ty Texture y coordinate
static void	surf_rows(t_vars *v, t_point p, int *t)
{
	int	cy;

	cy = 0;
	while (++p.y < v->ray.dy)
	{
		p.z = (t[1] * v->game.skybox.len) + (t[0] * 4);
		if (p.z < v->ray.lim && p.z >= 0 && p.x >= 0 && p.x < v->screen.gamew
			&& p.y >= 0)
			add_pix(v, p, (t_point3){0}, (t_point){0});
		cy += v->ray.dty;
		while (cy > v->ray.dy)
		{
			t[1] += 1;
			cy -= v->ray.dy;
		}
	}
}

/// @brief Draw the skybox on the screen
/// @param v Vars
/// @param p Pixel to add to the buffer
/// @param tx Texture x coordinate
/// @param ty Texture y coordinate
///	@note 
void	draw_skybox(t_vars *v, t_point p, int *t)
{
	v->ray.lim = ((v->game.skybox.height - 1) * v->game.skybox.len)
		+ ((v->game.skybox.width - 1) * 4);
	set_skybox(v);
	while (++p.x < v->screen.resw)
	{
		t[0] = v->ray.tx0;
		if (v->ray.tx0 >= v->game.skybox.width)
			t[0] = v->ray.tx0 - v->game.skybox.width;
		p.y = -1;
		t[1] = v->ray.ty0;
		surf_rows(v, p, t);
		p.z += v->ray.dtx;
		while (p.z > v->screen.resw)
		{
			v->ray.tx0 += 1;
			p.z -= v->screen.resw;
		}
	}
}
