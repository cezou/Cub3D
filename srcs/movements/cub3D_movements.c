/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_movements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 18:24:52 by pmagnero          #+#    #+#             */
/*   Updated: 2024/10/02 21:48:35 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/// @brief Rotate the camera on the x axis if the key pressed are LEFT/RIGHT
/// @param v Vars
/// @param d Key input pressed
/// @param rotspeed Rotation speed
/// @param mul Rotation speed factor
void	rotatecamx(t_vars *v, int d, double s)
{
	double	oldir;
	double	oldplane;

	if (d != LEFT && d != RIGHT)
		return ;
	v->player.angle = atan2(v->player.dir_y, v->player.dir_x);
	if (d == LEFT)
	{
		if (v->hud.animoff != 0)
			v->hud.refreshdh = 1;
		v->hud.animoff = 0;
	}
	else if (d == RIGHT)
	{
		s = -s;
		if (v->hud.animoff != v->hud.head.animx * 2)
			v->hud.refreshdh = 1;
		v->hud.animoff = v->hud.head.animx * 2;
	}
	oldir = v->player.dir_x;
	v->player.dir_x = v->player.dir_x * cos(s) - v->player.dir_y * sin(s);
	v->player.dir_y = oldir * sin(s) + v->player.dir_y * cos(s);
	oldplane = v->player.plane_x;
	v->player.plane_x = v->player.plane_x * cos(s) - v->player.plane_y * sin(s);
	v->player.plane_y = oldplane * sin(s) + v->player.plane_y * cos(s);
}

/// @brief Rotate the camera on the y axis if the key pressed are UP/DOWN
/// @param v Vars
/// @param d Key input pressed
/// @param rotspeed Rotation speed
/// @param mul Rotation speed factor
void	rotatecamy(t_vars *v, int d, double rotspeed, int mul)
{
	if (d == UP)
	{
		v->ray.pitch += mul * rotspeed;
		if (v->ray.pitch > v->screen.gameh / 2)
			v->ray.pitch = v->screen.gameh / 2;
	}
	else if (d == DOWN)
	{
		v->ray.pitch -= mul * rotspeed;
		if (v->ray.pitch < (-v->screen.gameh / 2) * 3)
			v->ray.pitch = -(v->screen.gameh / 2) * 3;
	}
}

/// @brief Move the player on the y axis if the key pressed are W/S
/// @param v Vars
/// @param d Key input pressed
void	moveplayery(t_vars *v, int d)
{
	t_point2	k;

	k = (t_point2){0.0, 0.0, 0, 0};
	if (d == NORTH)
	{
		k.x = v->player.x + v->player.dir_x * v->player.movespeedy;
		k.y = v->player.y + v->player.dir_y * v->player.movespeedy;
	}
	else if (d == SOUTH)
	{
		k.x = v->player.x - v->player.dir_x * v->player.movespeedy;
		k.y = v->player.y - v->player.dir_y * v->player.movespeedy;
	}
	k.z = (int)k.x;
	k.t = (int)k.y;
	v->player.player = set_pos(v, k, 0);
}

/// @brief Move the player on the x axis if the key pressed are A/D
/// @param v Vars
/// @param d Key Input pressed
void	moveplayerx(t_vars *v, int d)
{
	t_point2	k;
	t_point2	p;
	double		speed;

	k = (t_point2){0.0, 0.0, 0, 0};
	p = (t_point2){0.0, 0.0, 0, 0};
	if (d == WEST)
	{
		speed = v->player.movespeedx * v->game.frametime;
		p = get_90_angle(-1, v->player.dir_x, v->player.dir_y);
		k.x = v->player.x + p.x * speed;
		k.y = v->player.y + p.y * speed;
	}
	else if (d == EAST)
	{
		speed = v->player.movespeedx * v->game.frametime;
		p = get_90_angle(-1, v->player.dir_x, v->player.dir_y);
		k.x = v->player.x - p.x * speed;
		k.y = v->player.y - p.y * speed;
	}
	k.z = (int)k.x;
	k.t = (int)k.y;
	v->player.player = set_pos(v, k, 0);
}

/// @brief Action to do when a movement key is pressed
/// @param v Vars
/// @param d Key input pressed
void	move(t_vars *v, int d)
{
	if (v->game.pause)
		return ;
	printmap2(v);
	if (ACTIVATE_SOUND && (d < UP))
	{
		ma_sound_set_pitch(&v->sound.sound[1], 1.0);
		ma_sound_start(&v->sound.sound[1]);
	}
	v->game.canhit = 0;
	rotatecamx(v, d, v->player.rotspeed * v->game.frametime);
	rotatecamy(v, d, v->player.rotspeed * v->game.frametime, 500);
	if (d > -1 && d < 4)
		v->player.moving = 1;
	if (d == 0 || d == 1)
		v->player.movingy = 1;
	moveplayerx(v, d);
	moveplayery(v, d);
	open_door(v, d);
}
// if (d == 8)
// v->player.z = 200;
// ft_bzero((mlx_clear_window(v->mlx, v->screen.win), v->img[EMAP].addr),
// 	v->screen.resw * v->screen.resh * (v->img[EMAP].bpp / 8));