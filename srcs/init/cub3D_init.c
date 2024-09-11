/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:09:56 by pmagnero          #+#    #+#             */
/*   Updated: 2024/09/09 16:44:49 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	initvars(t_vars *v)
{
	v->mapv = (t_mapv){NULL, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, v->mapv.filename};
	v->player = (t_player){NULL, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
		v->player.movspeed, 0, 0};
	v->guard = (t_guard){NULL, 0, 1, 0, 5, 0, v->guard.movspeedguard, 0, 0};
	v->proj = (t_proj){0};
	v->menu = (t_menu){0};
	v->objs = (t_objs){v->objs.objs, 0, 0, 0};
	v->game = (t_game){0, v->game.start, v->game.fps, 0, 0, 0, 1};
	v->last = NULL;
	v->exit = NULL;
	v->ray = (t_ray){0};
}

void	initmodes(t_vars *v, int argc)
{
	v->god = 0;
	v->game.start = 0;
	v->game.fps = 64;
	v->mapv.filename = NULL;
	v->player.movspeed = 10;
	v->guard.movspeedguard = 40;
	v->objs.objs = NULL;
	initvars(v);
	initpathtext(v);
	if (argc < 2 || argc > 4)
		exit((prterr(v, "Too many/few arguments\n", 1, 1), 1));
}

void	set_player_dir(t_vars *v, double x, double y)
{
	v->player.dir_x = x;
	v->player.dir_y = y;
}

void	set_player_plane(t_vars *v, double px, double py)
{
	v->player.plane_x = px;
	v->player.plane_y = py;
}

void	init_player_dir(t_vars *v)
{
	ft_printf(0, "Player dir: %d", v->player.dir);
	if (v->player.dir == NORTH || v->player.player->val == 'N')
	{
		set_player_dir(v, 0, 1);
		set_player_plane(v, -0.66, 0);
	}
	else if (v->player.dir == EAST || v->player.player->val == 'E')
	{
		set_player_dir(v, 0, -1);
		set_player_plane(v, 0.66, 0);
	}
	else if (v->player.dir == WEST || v->player.player->val == 'W')
	{
		set_player_dir(v, -1, 0);
		set_player_plane(v, 0, -0.66);
	}
	else if (v->player.dir == SOUTH || v->player.player->val == 'S')
	{
		set_player_dir(v, 1, 0);
		set_player_plane(v, 0, 0.66);
	}
}

void	check_map(t_vars *v, int argc, char **argv)
{
	int	i;

	i = -1;
	if (argc > 1)
	{
		v->mapv.filename = argv[1];
		if (!v->mapv.filename)
			exit((map_clear(v->mapv.map), 1));
		parse(v, -1, NULL);
		v->player.x = v->player.player->x;
		v->player.y = v->player.player->y;
		printmap2(v);
		// flood_fill(v, &v->player.player, &v->player.pocket);
		// if ((!v->mapv.mapvalid) || (v->player.pocket != v->objs.collect))
		// 	exit((prterr(v, ERRFF, 1, 1), 1));
		v->player.pocket = 0;
		v->objs.objs = (t_point *)malloc(sizeof(t_point) * (v->objs.collect));
		if (!v->objs.objs)
			exit((prterr(v, ERRMALL, 1, 0), 1));
		while (++i < v->objs.collect)
			v->objs.objs[i] = (t_point){0, 0, 0, ECOLLECT};
	}
}

void	init(t_vars *v, int argc, char **argv)
{
	v->mlx = mlx_init();
	v->screen.win = NULL;
	v->mapv.map = NULL;
	v->sound.init = 0;
	v->objs.objs = NULL;
	v->img[EMAP].img = NULL;
	if (!v->mlx)
		exit((prterr(v, "MLX init failed\n", 1, 1), 1));
	mlx_do_key_autorepeaton(v->mlx);
	initwindow(v, argc, argv);
	v->img->fontname = FONT1;
	v->img->fontname2 = FONT2;
	initmodes(v, argc);
	inittextures(v, 0);
	initsounds(v);
	initplayeranim(v, -1);
	initobjectsanim(v, 0, ECOLLECT);
	initguardanim(v, -1);
	check_map(v, argc, argv);
	init_player_dir(v);
}

void	init_cam(t_vars *v)
{
	v->mouse.button = 0;
	v->mouse.xoff = 0.0;
	v->mouse.yoff = 0.0;
	v->mouse.prevx = 1.0;
	v->mouse.prevy = 1.0;
	v->mouse.zoom = 1;
	v->mouse.xangle = -0.615472907;
	v->mouse.yangle = -0.523599;
	v->mouse.zangle = 0.615472907;
	v->mouse.zheight = 1;
	// v->mapv.shiftx = -(v->player.player->x * v->img[EWALL].width
	// 		/ v->screen.resw) * v->screen.resw;
	// v->mapv.resdeltax = (v->player.player->x * v->img[EWALL].width
	// 		/ v->screen.resw) + 1;
	// v->mapv.shifty = -(v->player.player->y * v->img[EWALL].height
	// 		/ v->screen.resh) * v->screen.resh;
	// v->mapv.resdeltay = (v->player.player->y * v->img[EWALL].height
	// 		/ v->screen.resh) + 1;
}
//(long double)(long double)v->resh
//	/ ((long double)v->maph * (long double)v->img[1].height);