/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:09:56 by pmagnero          #+#    #+#             */
/*   Updated: 2024/09/19 16:23:39 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	initvars(t_vars *v)
{
	v->mapv = (t_mapv){0};
	v->player = (t_player){0};
	v->guard = (t_guard){NULL, 0, 1, 0, 5, 0, 0, 0};
	v->proj = (t_proj){0};
	v->menu = (t_menu){0};
	v->objs = (t_objs){0};
	v->door = (t_door){0};
	v->game = (t_game){0};
	v->last = NULL;
	v->exit = NULL;
	v->ray = (t_ray){0};
	v->sprite = (t_sprite){0};
	v->game.fps = 64;
	v->game.refreshmap = 1;
	v->player.movespeedy = 0.11;
	v->player.movespeedx = 0.11;
	v->player.rotspeed = 0.05;
	v->player.mouserotspeed = 0.05;
}

void	initmodes(t_vars *v, int argc)
{
	initvars(v);
	v->ray.zbuffer = (int *)malloc(sizeof(int) * v->screen.resw);
	if (!v->ray.zbuffer)
		exit((prterr(v, ERRMALL, 1, 1), 1));
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
	if (v->player.player->val == 'N')
	{
		set_player_dir(v, 0, -1);
		set_player_plane(v, 0.66, 0);
	}
	else if (v->player.player->val == 'S')
	{
		set_player_dir(v, 0, 1);
		set_player_plane(v, -0.66, 0);
	}
	else if (v->player.player->val == 'E')
	{
		set_player_dir(v, -1, 0);
		set_player_plane(v, 0, -0.66);
	}
	else if (v->player.player->val == 'W')
	{
		set_player_dir(v, 1, 0);
		set_player_plane(v, 0, 0.66);
	}
}

void	check_map(t_vars *v, int argc, char **argv)
{
	int		i;
	t_map	*tmp;

	i = -1;
	if (argc > 1)
	{
		v->mapv.filename = argv[1];
		if (!v->mapv.filename)
			exit((map_clear(v->mapv.map), 1));
		parse(v, -1, NULL);
		v->player.x = v->player.player->x;
		v->player.y = v->player.player->y;
		v->door.d = (t_point *)malloc(sizeof(t_point) * (v->door.nb));
		if (!v->door.d)
			exit((prterr(v, ERRMALL, 1, 0), 1));
		tmp = v->mapv.map;
		// ft_printf(1, "door nb: %d\n", v->door.nb);
		while (tmp)
		{
			if (tmp->val == 'D')
			{
				v->door.d[++i] = (t_point){tmp->x, tmp->y, 0, ECLOSE};
				// ft_printf(1, "x: %d y: %d\n", v->door.d[i].x, v->door.d[i].y);
			}
			tmp = tmp->right;
		}
		v->img[EDOOR].xdelta = v->img[EDOOR].width;
		// v->img[ESPACE].xdelta = v->img[ESPACE].width;
	}
}

void	init(t_vars *v, int argc, char **argv)
{
	int	i;

	i = -1;
	v->mlx = mlx_init();
	v->screen.win = NULL;
	v->mapv.map = NULL;
	v->sound.init = 0;
	v->objs.objs = NULL;
	while (v->img && ++i <= COMP_N)
		v->img[i] = (t_imga){0};
	if (!v->mlx)
		exit((prterr(v, "MLX init failed\n", 1, 1), 1));
	mlx_do_key_autorepeaton(v->mlx);
	initwindow(v, argc, argv);
	mlx_mouse_hide(v->mlx, v->screen.win);
	v->img->fontname = FONT1;
	v->img->fontname2 = FONT2;
	initmodes(v, argc);
	inittextures(v, 0);
	initsounds(v);
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
}
