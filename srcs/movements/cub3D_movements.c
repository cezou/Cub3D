/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_movements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 18:24:52 by pmagnero          #+#    #+#             */
/*   Updated: 2024/09/10 12:41:19 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

#define M_PI 3.14159265358979323846

float	rad_to_deg(float rad)
{
	float	deg;

	deg = rad * (180 / M_PI);
	if (deg < 0)
		deg += 360;
	return (deg);
}

float	deg_to_rad(float deg)
{
	float	rad;

	rad = deg * (M_PI / 180);
	return (rad);
}

t_point2	get_90_angle(t_vars *v, int dir)
{
	double		deg;
	double		rad;
	t_point2	p;

	deg = rad_to_deg(atan2(v->player.dir_y, v->player.dir_x)) + (90 * dir);
	rad = deg_to_rad(deg);
	p.x = (cos(rad));
	p.y = (sin(rad));
	p.x += v->player.dir_x;
	p.y += v->player.dir_y;
	deg = (atan2(p.y - v->player.dir_y, p.x - v->player.dir_x));
	return ((t_point2){cos(deg), sin(deg), 0, 0});
}

void	setplayerpos(t_vars *v)
{
	TRACE("x: %f, y: %f = %d\n", v->player.x, v->player.y, (int)v->player.y);
	TRACE("px: %d, py: %d\n", (int)(v->player.x + 0.5 - 2.0), (int)(v->player.y
			+ 0.5 - 2.0));
	TRACE("upx: %d, upy: %d\n", v->player.player->up->x,
		v->player.player->up->y);
	if ((int)(v->player.x + 0.5 - 2.0) == v->player.player->up->x
		&& (int)(v->player.y + 0.5 - 2.0) == v->player.player->up->y)
		v->player.player = v->player.player->up;
}

static void	movearrows(t_vars *v, t_map *dir, int d)
{
	double		frametime;
	double		movespeed;
	double		rotspeed;
	t_point2	p;
	double		oldir;
	double		oldplane;

	frametime = 0.05;
	movespeed = 0.05;
	rotspeed = frametime;
	(void)dir;
	v->player.moving = 1;
	v->player.animp = EWALK;
	if (d == 4)
	{
		v->player.angle = atan2(v->player.dir_y, v->player.dir_x);
		oldir = v->player.dir_x;
		v->player.dir_x = v->player.dir_x * cos(-rotspeed) - v->player.dir_y
			* sin(-rotspeed);
		v->player.dir_y = oldir * sin(-rotspeed) + v->player.dir_y
			* cos(-rotspeed);
		oldplane = v->player.plane_x;
		v->player.plane_x = v->player.plane_x * cos(-rotspeed)
			- v->player.plane_y * sin(-rotspeed);
		v->player.plane_y = oldplane * sin(-rotspeed) + v->player.plane_y
			* cos(-rotspeed);
		// moveshor((v->img[ESPAWN].xdelta += v->player.movspeed, v), dir,
		// 	(t_point){-v->player.movspeed, 1, 50, W}, ESPAWN);
	}
	// v->player.player->val = 'E';
	else if (d == 5)
	{
		v->player.angle = atan2(v->player.dir_y, v->player.dir_x);
		oldir = v->player.dir_x;
		v->player.dir_x = v->player.dir_x * cos(rotspeed) - v->player.dir_y
			* sin(rotspeed);
		v->player.dir_y = oldir * sin(rotspeed) + v->player.dir_y
			* cos(rotspeed);
		oldplane = v->player.plane_x;
		v->player.plane_x = v->player.plane_x * cos(rotspeed)
			- v->player.plane_y * sin(rotspeed);
		v->player.plane_y = oldplane * sin(rotspeed) + v->player.plane_y
			* cos(rotspeed);
		// moveshor((v->img[ESPAWN].xdelta -= v->player.movspeed, v), dir,
		// 	(t_point){v->player.movspeed, 1, 10, E}, ESPAWN);
		// v->player.player->val = 'W';
	}
	else if (d == NORTH)
	{
		// v->player.player = v->player.player->up;
		// if (v->player.angle < 0.0)
		// 	v->player.player = v->player.player->down->down;
		v->player.x += v->player.dir_x * movespeed;
		v->player.y += v->player.dir_y * movespeed;
		setplayerpos(v);
		// movesvert((v->img[ESPAWN].ydelta -= v->player.movspeed, v), dir,
		// 	(t_point){v->player.movspeed, 0, 31, N}, ESPAWN);
		// v->player.player->val = 'N';
	}
	else if (d == SOUTH)
	{
		// v->player.player = v->player.player->down;
		// if (v->player.angle < 0.0)
		// 	v->player.player = v->player.player->up->up;
		v->player.x -= v->player.dir_x * movespeed;
		v->player.y -= v->player.dir_y * movespeed;
		TRACE("x: %f, y: %f\n", v->player.x, v->player.y);
		TRACE("px: %d, py: %d\n", v->player.player->x, v->player.player->y);
		TRACE("upx: %d, upy: %d\n", v->player.player->up->x,
			v->player.player->up->y);
		// movesvert((v->img[ESPAWN].ydelta += v->player.movspeed, v), dir,
		// 	(t_point){-v->player.movspeed, 0, 52, S}, ESPAWN);
	}
	else if (d == WEST)
	{
		p = get_90_angle(v, -1);
		v->player.x += p.x * movespeed;
		v->player.y += p.y * movespeed;
		// movesvert((v->img[ESPAWN].ydelta += v->player.movspeed, v), dir,
		// 	(t_point){-v->player.movspeed, 0, 52, W}, ESPAWN);
	}
	else if (d == EAST)
	{
		p = get_90_angle(v, -1);
		v->player.x -= p.x * movespeed;
		v->player.y -= p.y * movespeed;
		// movesvert((v->img[ESPAWN].ydelta += v->player.movspeed, v), dir,
		// 	(t_point){-v->player.movspeed, 0, 52, E}, ESPAWN);
	}
	// v->player.dir = d;
	// printf("angle: %f", v->player.angle);
}

void	arrows(t_vars *v, t_map *dir, int d)
{
	if (v->game.pause)
		return (menuarrow(v, d));
	printmap2(v);
	if (ACTIVATE_SOUND && (d != 4 && d == 5))
	{
		ma_sound_set_pitch(&v->sound.sound[1], 2.5);
		ma_sound_start(&v->sound.sound[1]);
	}
	movearrows(v, dir, d);
	// if (dir->val == COLLECT || v->player.player->val == COLLECT)
	// 	iscollected(v, -1, ESPAWN, (t_point){0});
	// if (dir->val == GUARD || v->player.player->val == GUARD)
	// 	checkhitmonster(v,
	// 		(t_point){v->img[ESPAWN].posx + v->img[ESPAWN].xdelta,
	// 		v->img[ESPAWN].posy + v->img[ESPAWN].ydelta, 40, ESPAWN});
	ft_bzero((mlx_clear_window(v->mlx, v->screen.win), v->img[COMP_N].addr),
		v->screen.resw * v->screen.resh * (v->img[COMP_N].bpp / 8));
	render((v->game.refreshmap = 1, v));
}

int	keys_release(int keycode, t_vars *v)
{
	if (v->game.start > 1 && ACTIVATE_SOUND && (keycode == XK_Up
			|| keycode == XK_Down || keycode == XK_Left || keycode == XK_Right))
		ma_sound_stop(&v->sound.sound[1]);
	return (0);
}
