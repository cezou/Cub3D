/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_raycasting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 21:30:54 by pmagnero          #+#    #+#             */
/*   Updated: 2024/10/08 18:01:38 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/// @brief Init the datas needed for the raycasting algorithm
/// @param x X pixel position
/// @param v Vars
void	init_raycasting_info(int x, t_vars *v)
{
	v->ray.camera_x = 2 * x / (double)v->screen.resw - 1;
	v->ray.dir_x = v->player.dir_x + v->player.plane_x * v->ray.camera_x;
	v->ray.dir_y = v->player.dir_y + v->player.plane_y * v->ray.camera_x;
	v->ray.map_x = v->player.x;
	v->ray.map_y = v->player.y;
	v->ray.deltadist_x = fabs(1 / v->ray.dir_x);
	v->ray.deltadist_y = fabs(1 / v->ray.dir_y);
}

/// @brief Calculate the distance and height of the wall
///	from the player position
/// @param v Vars
void	calculate_line_height(t_vars *v)
{
	v->ray.line_height = (int)(v->screen.gameh / v->ray.wall_dist);
	v->ray.draw_start = -(v->ray.line_height) / 2 + v->screen.gameh / 2
		+ v->ray.pitch + (v->player.z / v->ray.wall_dist);
	if (v->ray.draw_start < 0)
		v->ray.draw_start = 0;
	v->ray.draw_end = v->ray.line_height / 2 + v->screen.gameh / 2
		+ v->ray.pitch + (v->player.z / v->ray.wall_dist);
	if (v->ray.draw_end >= v->screen.gameh)
		v->ray.draw_end = v->screen.gameh - 1;
	if (v->ray.side == 0)
		v->ray.wall_x = v->player.y + v->ray.wall_dist * v->ray.dir_y;
	else
		v->ray.wall_x = v->player.x + v->ray.wall_dist * v->ray.dir_x;
	v->ray.wall_x -= floor(v->ray.wall_x);
}

/// @brief Get texture from paths in file
/// @param v Vars
static void	get_texture_index(t_vars *v)
{
	if (v->ray.img.id != ESPACE)
		return ;
	if (v->ray.side == 0)
	{
		if (v->ray.dir_x < 0)
			v->ray.img = v->infos.west.imga;
		else
			v->ray.img = v->infos.east.imga;
	}
	else
	{
		if (v->ray.dir_y > 0)
			v->ray.img = v->infos.south.imga;
		else
			v->ray.img = v->infos.north.imga;
	}
}

/// @brief Transform the wall/door distance into pixels coordinate
///	from the texture to add to the buffer
/// @param v Vars
/// @param p Pixel to add in the buffer: {x, y, 0, color}
/// @param texx Texture x coordinate
/// @param texy Texture y coordinate
/// color = v->tex[2][128 * texy + texx];
void	update_texture_pixels(t_vars *v, t_point p, int *t)
{
	get_texture_index(v);
	t[0] = (int)(v->ray.wall_x * v->ray.img.width);
	t[0] = door_extend_ray(v, p, t);
	if (t[0] < 0)
		return ;
	if ((v->ray.side == 0 && v->ray.dir_x > 0) || (v->ray.side == 1
			&& v->ray.dir_y < 0))
		t[0] = v->ray.img.width - t[0] - 1;
	v->ray.step = 1.0 * v->ray.img.width / v->ray.line_height;
	v->ray.pos = (v->ray.draw_start - v->ray.pitch - (v->player.z
				/ v->ray.wall_dist) - v->screen.gameh / 2 + v->ray.line_height
			/ 2) * v->ray.step;
	p.y = v->ray.draw_start - 1;
	while (++p.y < v->ray.draw_end)
	{
		t[1] = (int)v->ray.pos & (v->tmp[0].width - 1);
		v->ray.pos += v->ray.step;
		p.z = (t[1] * v->tmp[0].len) + (t[0] * 4);
		if (p.z < v->ray.lim && v->ray.side == 0)
			add_pix(v, p, (t_point2){1, v->ray.wall_dist, FOGC, FOGL},
				(t_point){1, 0, 0, 0});
		else if (p.z < v->ray.lim && v->ray.side == 1)
			add_pix(v, p, (t_point2){1, v->ray.wall_dist, FOGC, FOGL},
				(t_point){0});
	}
}

/// @brief Raycasting algorithm
/// @note We draw the skybox
/// @note We draw the floor and the ceiling with the horizontal method
/// @note We then draw the walls and doors with the raycasting algorithm
/// @note We draw the sprites
/// @param v Vars
/// @return
int	raycasting(t_vars *v, t_imga dest)
{
	int	t[2];

	v->tmp[1] = dest;
	v->ray.x = -1;
	v->tmp[0] = v->game.skybox;
	if (v->ray.pitch > v->screen.gameh / 2)
		v->ray.pitch = v->screen.gameh / 2;
	if (v->ray.pitch < (-v->screen.gameh / 2) * 3)
		v->ray.pitch = -(v->screen.gameh / 2) * 3;
	draw_skybox(v, (t_point){-1, -1, 0, 0}, t);
	draw_floor_ceiling(v);
	while (++v->ray.x < v->screen.resw)
	{
		init_raycasting_info(v->ray.x, v);
		set_dda(v);
		perform_dda(v, v->player.player, 0);
		calculate_line_height(v);
		update_texture_pixels(v, (t_point){v->ray.x, 0, 0, 0}, t);
		v->ray.zbuffer[v->ray.x] = v->ray.wall_dist;
	}
	draw_sprites(v);
	return (1);
}
