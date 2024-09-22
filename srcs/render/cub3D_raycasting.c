/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_raycasting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 21:30:54 by pmagnero          #+#    #+#             */
/*   Updated: 2024/09/22 14:24:55 by pmagnero         ###   ########.fr       */
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
	v->ray.line_height = (int)(v->screen.resh / v->ray.wall_dist);
	v->ray.draw_start = -(v->ray.line_height) / 2
		+ v->screen.resh / 2 + v->ray.pitch + (v->player.z / v->ray.wall_dist);
	if (v->ray.draw_start < 0)
		v->ray.draw_start = 0;
	v->ray.draw_end = v->ray.line_height / 2
		+ v->screen.resh / 2 + v->ray.pitch + (v->player.z / v->ray.wall_dist);
	if (v->ray.draw_end >= v->screen.resh)
		v->ray.draw_end = v->screen.resh - 1;
	if (v->ray.side == 0)
		v->ray.wall_x = v->player.y + v->ray.wall_dist * v->ray.dir_y;
	else
		v->ray.wall_x = v->player.x + v->ray.wall_dist * v->ray.dir_x;
	v->ray.wall_x -= floor(v->ray.wall_x);
}

// static void	get_texture_index(t_vars *v)
// {
// 	if (v->ray.side == 0)
// 	{
// 		if (v->ray.dir_x < 0)
// 			v->texinfo.index = WEST;
// 		else
// 			v->texinfo.index = EAST;
// 	}
// 	else
// 	{
// 		if (v->ray.dir_y > 0)
// 			v->texinfo.index = SOUTH;
// 		else
// 			v->texinfo.index = NORTH;
// 	}
// }

/// @brief Update doors animation
/// @param v Vars
void	loadtexture(t_vars *v)
{
	int	i;

	i = -1;
	// i = find_door(v, v->ray.hit->x, v->ray.hit->y);
	while (++i < v->game.nb_door)
	{
		if (v->door[i].state == EOPENING
			&& timestamp_in_ms(v) -v->door[i].time
			>= (uint64_t)(5000 / v->game.fps))
		{
			v->door[i].xdelta -= 3;
			v->door[i].time = timestamp_in_ms(v);
		}
		else if (v->door[i].state == ECLOSING
			&& timestamp_in_ms(v) - v->door[i].time
			>= (uint64_t)(5000 / v->game.fps))
		{
			v->door[i].xdelta += 3;
			v->door[i].time = timestamp_in_ms(v);
		}
		if (v->door[i].state == EOPENING
			&& v->door[i].xdelta <= 0)
			v->door[i].state = EOPEN;
		else if (v->door[i].state == ECLOSING
			&& v->door[i].xdelta >= v->img[EDOOR].width)
			v->door[i].state = ECLOSE;
	}
}

/// @brief Transform the wall/door distance into pixels coordinate
///	from the texture to add to the buffer
/// @param v Vars
/// @param p Pixel to add in the buffer: {x, y, 0, color}
/// @param texx Texture x coordinate
/// @param texy Texture y coordinate
/// color = v->tex[2][128 * texy + texx];
void	update_texture_pixels(t_vars *v, t_point p, int texx, int texy)
{
	double		step;
	double		pos;

	texx = (int)(v->ray.wall_x * v->ray.img.width);
	if (v->ray.img.id == EDOOR)
	{
		texx -= v->ray.img.width - v->ray.door.xdelta;
		if (texx < 0)
		{
			v->ray.hit = NULL;
			perform_dda(v, 1);
			calculate_line_height(v);
			update_texture_pixels(v, p, 0, 0);
			return ;
		}
	}
	if ((v->ray.side == 0 && v->ray.dir_x > 0)
		|| (v->ray.side == 1 && v->ray.dir_y < 0))
		texx = v->ray.img.width - texx - 1;
	step = 1.0 * v->ray.img.width / v->ray.line_height;
	pos = (v->ray.draw_start - v->ray.pitch - (v->player.z / v->ray.wall_dist)
			- v->screen.resh / 2 + v->ray.line_height / 2) * step;
	p.y = v->ray.draw_start;
	while (p.y < v->ray.draw_end)
	{
		texy = (int)pos & (v->ray.img.width - 1);
		pos += step;
		p.z = (texy * v->ray.img.len) + (texx * 4);
		if (v->ray.side == 0)
			p.color = 1;
		add_pix_to_buffer(v, v->ray.img, p,
			(t_point2){1, v->ray.wall_dist, FOG_COLOR, FOG_LEVEL});
		p.y++;
	}
}

/// @brief Raycasting algorithm
/// @note We draw the skybox
/// @note We draw the floor and the ceiling with the horizontal method
/// @note We then draw the walls and doors with the raycasting algorithm
/// @note We draw the sprites
/// @note And finally we update the states of all the animations
/// @param v Vars
/// @return 
int	raycasting(t_vars *v)
{
	int		x;
	int		y;

	x = 0;
	y = -1;
	draw_skybox(v, (t_point){-1, -1, 0, 0}, 0, 0);
	draw_floor_ceiling(v);
	while (x < v->screen.resw)
	{
		init_raycasting_info(x, v);
		set_dda(v);
		perform_dda(v, 1);
		calculate_line_height(v);
		update_texture_pixels(v, (t_point){x, 0, 0, 0}, 0, 0);
		v->ray.zbuffer[x] = v->ray.wall_dist;
		x++;
	}
	draw_sprites(v, &v->sprite, (t_point){0, 0, 0, 0});
	animations(v);
	loadtexture(v);
	return (1);
}
