/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_movements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 18:24:52 by pmagnero          #+#    #+#             */
/*   Updated: 2024/10/30 13:17:08 by pmagnero         ###   ########.fr       */
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

	if ((d != LEFT && d != RIGHT) && (!v->keys[XK_Left] && !v->keys[XK_Right]))
		return ;
	v->player.angle = atan2(v->player.dir_y, v->player.dir_x);
	if (d == LEFT || v->keys[XK_Right])
	{
		if (v->hud.animoff != 0)
			v->hud.refreshdh = 1;
		v->hud.animoff = 0;
	}
	else if (d == RIGHT || v->keys[XK_Left])
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
	if (d == UP || v->keys[XK_Up])
	{
		v->ray.pitch += mul * rotspeed;
		if (v->ray.pitch > v->screen.gameh / 2)
			v->ray.pitch = v->screen.gameh / 2;
	}
	else if (d == DOWN || v->keys[XK_Down])
	{
		v->ray.pitch -= mul * rotspeed;
		if (v->ray.pitch < (-v->screen.gameh / 2) * 3)
			v->ray.pitch = -(v->screen.gameh / 2) * 3;
	}
}

/// @brief Move the player on the y axis if the key pressed are W/S
/// @param v Vars
void	moveplayery(t_vars *v, int d)
{
	t_point2	k;

	k = (t_point2){0.0, 0.0, 0, 0};
	if (d == NORTH || v->keys[XK_z])
	{
		k.x = v->player.x + v->player.dir_x * v->player.movespeedy;
		k.y = v->player.y + v->player.dir_y * v->player.movespeedy;
	}
	else if (d == SOUTH || v->keys[XK_s])
	{
		k.x = v->player.x - v->player.dir_x * v->player.movespeedy;
		k.y = v->player.y - v->player.dir_y * v->player.movespeedy;
	}
	k.z = (int)k.x;
	k.t = (int)k.y;
	v->player.player = set_pos(v, k, v->player.player, 0);
}

/// @brief Move the player on the x axis if the key pressed are A/D
/// @param v Vars
void	moveplayerx(t_vars *v, int d)
{
	t_point2	k;
	t_point2	p;
	double		speed;

	k = (t_point2){0.0, 0.0, 0, 0};
	p = (t_point2){0.0, 0.0, 0, 0};
	if (d == WEST || v->keys[XK_q])
	{
		speed = v->player.movespeedx * v->game.frametime;
		p = get_90_angle(-1, v->player.dir_x, v->player.dir_y);
		k.x = v->player.x + p.x * speed;
		k.y = v->player.y + p.y * speed;
	}
	else if (d == EAST || v->keys[XK_d])
	{
		speed = v->player.movespeedx * v->game.frametime;
		p = get_90_angle(-1, v->player.dir_x, v->player.dir_y);
		k.x = v->player.x - p.x * speed;
		k.y = v->player.y - p.y * speed;
	}
	k.z = (int)k.x;
	k.t = (int)k.y;
	v->player.player = set_pos(v, k, v->player.player, 0);
}

/// @brief Action to do when a movement key is pressed
/// @param v Vars
/// @param d Key input pressed
void	move(t_vars *v)
{
	if (v->game.pause)
		return ;
	if (ACTIVATE_SOUND && (v->keys[XK_z] || v->keys[XK_s]
			|| v->keys[XK_q] || v->keys[XK_d]))
	{
		ma_sound_set_pitch(&v->sound.sound[1], 1.0);
		ma_sound_start(&v->sound.sound[1]);
	}
	v->game.canhit = 0;
	rotatecamx(v, -1, v->player.rotspeed * v->game.frametime);
	rotatecamy(v, -1, v->player.rotspeed * v->game.frametime, 500);
	if (v->keys[XK_z] || v->keys[XK_s] || v->keys[XK_q] || v->keys[XK_d])
		v->player.moving = 1;
	if (v->keys[XK_z] || v->keys[XK_s])
		v->player.movingy = 1;
	moveplayerx(v, -1);
	moveplayery(v, -1);
	open_door(v);
}
