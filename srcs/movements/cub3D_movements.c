/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_movements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 18:24:52 by pmagnero          #+#    #+#             */
/*   Updated: 2024/09/19 19:44:47 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	rotatecamx(t_vars *v, int d, double rotspeed)
{
	double	oldir;
	double	oldplane;

	if (d != LEFT && d != RIGHT)
		return ;
	v->player.angle = atan2(v->player.dir_y, v->player.dir_x);
	if (d == RIGHT)
		rotspeed = -rotspeed;
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
}

void	rotatecamy(t_vars *v, int d, double rotspeed, int mul)
{
	if (d == UP)
	{
		v->ray.pitch += mul * rotspeed;
		if (v->ray.pitch > LOOKUP_MAX)
			v->ray.pitch = LOOKUP_MAX;
	}
	else if (d == DOWN)
	{
		v->ray.pitch -= mul * rotspeed;
		if (v->ray.pitch < -LOOKUP_MAX)
			v->ray.pitch = -LOOKUP_MAX;
	}
}

static void	moveplayery(t_vars *v, int d)
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
	set_pos(v, k);
}

static void	moveplayerx(t_vars *v, int d)
{
	t_point2	k;
	t_point2	p;

	k = (t_point2){0.0, 0.0, 0, 0};
	p = (t_point2){0.0, 0.0, 0, 0};
	if (d == WEST)
	{
		p = get_90_angle(-1, v->player.dir_x, v->player.dir_y);
		k.x = v->player.x + p.x * v->player.movespeedx;
		k.y = v->player.y + p.y * v->player.movespeedx;
	}
	else if (d == EAST)
	{
		p = get_90_angle(-1, v->player.dir_x, v->player.dir_y);
		k.x = v->player.x - p.x * v->player.movespeedx;
		k.y = v->player.y - p.y * v->player.movespeedx;
	}
	k.z = (int)k.x;
	k.t = (int)k.y;
	set_pos(v, k);
}

void	move(t_vars *v, int d)
{
	if (v->game.pause)
		return (menuarrow(v, d));
	printmap2(v);
	if (ACTIVATE_SOUND && (d < UP))
	{
		ma_sound_set_pitch(&v->sound.sound[1], 2.5);
		ma_sound_start(&v->sound.sound[1]);
	}
	v->player.moving = 1;
	v->player.animp = EWALK;
	rotatecamx(v, d, v->player.rotspeed);
	rotatecamy(v, d, v->player.rotspeed, 500);
	moveplayerx(v, d);
	moveplayery(v, d);
	// if (d == 8)
		// v->player.z = 200;
	if (d == 8)
	{
		if (v->door.d[0].color == EOPEN)
			v->door.d[0].color = ECLOSING;
		else if (v->door.d[0].color == ECLOSE)
			v->door.d[0].color = EOPENING;
	}
	// ft_bzero((mlx_clear_window(v->mlx, v->screen.win), v->img[EMAP].addr),
	// 	v->screen.resw * v->screen.resh * (v->img[EMAP].bpp / 8));
	render((v->game.refreshmap = 1, v));
}
