/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_movements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 18:24:52 by pmagnero          #+#    #+#             */
/*   Updated: 2024/09/11 17:37:51 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

# define M_PI		3.14159265358979323846	/* pi */

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

void	setplayerpos(t_vars *v, t_point2 k)
{
	TRACE("x: %f, y: %f\n", k.x, k.y);
	TRACE("px: %d, py: %f\n", (int)(v->player.x), v->player.y - v->player.dir_y * 0.05);
	TRACE("upx: %d, upy: %d\n", v->player.player->up->x,
		v->player.player->up->y);
	if ((int)(k.x) == v->player.player->up->x
		&& (int)(k.y - 0.5 + v->player.player->up->y - v->player.player->y) == v->player.player->up->y)
	// if ((int)v->player.y >= (int)(v->player.y - v->player.dir_y * 0.05))
	{
		v->player.player = v->player.player->up;
		v->player.x += k.x;
		v->player.y += k.y;
	}
}

void	get_pos(t_vars *v, double x, double y)
{
	t_map	*tmp;
	double	tx;
	double	ty;
	int		ix;
	int		iy;

	tx = x;
	ty = y;
	ix = (int)tx;
	iy = (int)ty;
	tmp = v->player.player;
	// tmp = v->mapv.map;
	// while (tmp)
	// {
	// 	if (tmp->x == ix && tmp->y == iy
	// 		&& tmp->val != '1')
	// 	{
	// 		v->player.x = x;
	// 		v->player.y = y;
	// 		v->player.player = tmp;
	// 		break ;
	// 	}
	// 	tmp = tmp->right;
	// }
	TRACE("tx: %f, ty: %f\n", tx, ty);
	TRACE("upx, %d, upy: %d, ix: %d, iy: %d, val: %c\n", tmp->up->x, tmp->up->y, ix, iy, tmp->up->val);
	if (tmp->x == ix && tmp->y == iy && tmp->val != '1')
	{
		v->player.x = x;
		v->player.y = y;
	}
	else if (tmp->up->y != 0 && tmp->up->x == ix && tmp->up->y == iy)
	{
		v->player.x = x;
		v->player.y = y;
		if (tmp->up->val != '1')
			v->player.player = tmp->up;
	}
	else if (tmp->up->left->y != 0 && tmp->up->left->x != 0 && tmp->up->left->x == ix && tmp->up->left->y == iy)
	{
		v->player.x = x;
		v->player.y = y;
		if (tmp->up->left->val != '1')
			v->player.player = tmp->up->left;
	}
	else if (tmp->up->right->y != 0 && tmp->up->right->x != v->mapv.mapw - 1 && tmp->up->right->x == ix && tmp->up->right->y == iy)
	{
		v->player.x = x;
		v->player.y = y;
		if (tmp->up->right->val != '1')
			v->player.player = tmp->up->right;
	}
	else if (tmp->down->y != v->mapv.maph - 1 && tmp->down->x == ix && tmp->down->y == iy)
	{
		v->player.x = x;
		v->player.y = y;
		if (tmp->down->val != '1')
			v->player.player = tmp->down;
	}
	else if (tmp->down->left->y != v->mapv.maph - 1 && tmp->down->left->x != 0 && tmp->down->left->x == ix && tmp->down->left->y == iy)
	{
		v->player.x = x;
		v->player.y = y;
		if (tmp->down->left->val != '1')
			v->player.player = tmp->down->left;
	}
	else if (tmp->down->right->y != v->mapv.maph - 1 && tmp->down->right->x != v->mapv.mapw && tmp->down->right->x == ix && tmp->down->right->y == iy)
	{
		v->player.x = x;
		v->player.y = y;
		if (tmp->down->right->val != '1')
			v->player.player = tmp->down->right;
	}
	else if (tmp->left->x != 0 && tmp->left->x == ix && tmp->left->y == iy)
	{
		v->player.x = x;
		v->player.y = y;
		if (tmp->left->val != '1')
			v->player.player = tmp->left;
	}
	else if (tmp->right->x != v->mapv.mapw - 1 && tmp->right->x == ix && tmp->right->y == iy)
	{
		v->player.x = x;
		v->player.y = y;
		if (tmp->right->val != '1')
			v->player.player = tmp->right;
	}
}

static void	movearrows(t_vars *v, t_map *dir, int d)
{
	double		frametime;
	double		movespeed;
	double		rotspeed;
	t_point2	p;
	t_point2	k;
	double		oldir;
	double		oldplane;

	frametime = 0.05;
	movespeed = 0.1;
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
	}
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
	}
	else if (d == NORTH)
	{
		k.x = v->player.x + v->player.dir_x * movespeed;
		k.y = v->player.y + v->player.dir_y * movespeed;
		TRACE("NORTH\n");
		TRACE("x: %f, y: %f\n", k.x, k.y);
		TRACE("px: %d, py: %d\n", v->player.player->x, v->player.player->y);
		TRACE("dx: %d, dy: %d\n", v->player.player->up->x,
			v->player.player->up->y);
		// if (v->player.player->up->val != '1')
		get_pos(v, k.x, k.y);
	}
	else if (d == SOUTH)
	{
		k.x = v->player.x - v->player.dir_x * movespeed;
		k.y = v->player.y - v->player.dir_y * movespeed;
		TRACE("SOUTH\n");
		TRACE("x: %f, y: %f\n", k.x, k.y);
		TRACE("px: %d, py: %d\n", v->player.player->x, v->player.player->y);
		TRACE("dx: %d, dy: %d\n", v->player.player->down->x,
			v->player.player->down->y);
		get_pos(v, k.x, k.y);
	}
	else if (d == WEST)
	{
		p = get_90_angle(v, -1);
		k.x = v->player.x + p.x * movespeed;
		k.y = v->player.y + p.y * movespeed;
		TRACE("WEST\n");
		TRACE("x: %f, y: %f\n", k.x, k.y);
		TRACE("px: %d, py: %d\n", v->player.player->x, v->player.player->y);
		TRACE("dx: %d, dy: %d\n", v->player.player->left->x,
			v->player.player->left->y);
		get_pos(v, k.x, k.y);
	}
	else if (d == EAST)
	{
		p = get_90_angle(v, -1);
		k.x = v->player.x - p.x * movespeed;
		k.y = v->player.y - p.y * movespeed;
		TRACE("EAST\n");
		TRACE("x: %f, y: %f\n", v->player.x, v->player.y);
		TRACE("x: %f, y: %f\n", k.x, k.y);
		TRACE("px: %d, py: %d\n", v->player.player->x, v->player.player->y);
		TRACE("dx: %d, dy: %d\n", v->player.player->right->x,
			v->player.player->right->y);
		get_pos(v, k.x, k.y);
	}
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
