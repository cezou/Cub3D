/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:09:56 by pmagnero          #+#    #+#             */
/*   Updated: 2024/09/20 19:22:35 by pmagnero         ###   ########.fr       */
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
	v->door = NULL;
	v->game = (t_game){0};
	v->mouse = (t_mouse){0};
	v->last = NULL;
	v->exit = NULL;
	v->ray = (t_ray){0};
	v->sprite = (t_sprite){0};
	v->floor = (t_floor){0};
	v->game.fps = 64;
	v->player.movespeedy = 0.04;
	v->player.movespeedx = 0.04;
	v->player.rotspeed = 0.05;
	v->player.mouserotspeed = 0.04;
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

void	check_map(t_vars *v)
{
	int		i;
	t_map	*tmp;

	i = -1;
	parse(v, -1, NULL);
	v->player.x = v->player.player->x;
	v->player.y = v->player.player->y;
	v->door = (t_door *)malloc(sizeof(t_door) * (v->game.nb_door));
	if (!v->door)
		exit((prterr(v, ERRMALL, 1, 0), 1));
	tmp = v->mapv.map;
	ft_printf(1, "door nb: %d\n", v->game.nb_door);
	while (tmp)
	{
		if (tmp->val == 'D')
		{
			v->door[++i].x = tmp->x;
			v->door[i].y = tmp->y;
			v->door[i].time = 0;
			v->door[i].state = ECLOSE;
			v->door[i].xdelta = v->img[EDOOR].width;
			ft_printf(1, "x: %d y: %d\n", v->door[i].x, v->door[i].y);
		}
		tmp = tmp->right;
	}
}

void	init(t_vars *v, int argc, char **argv)
{
	int	i;

	i = -1;
	parsing(argc, argv, v);
	v->screen.win = NULL;
	v->mapv.map = NULL;
	v->sound.init = 0;
	v->objs.objs = NULL;
	v->img = (t_imga *)malloc(sizeof(t_imga) * (COMP_N + 1));
	if (!v->img)
		exit((prterr(v, ERRMALL, 1, 1), 1));
	while (v->img && ++i <= COMP_N)
		v->img[i] = (t_imga){0};
	(ft_bzero(v->keys, MAX_KEYS), initwindow(v, argc, argv));
	mlx_mouse_hide(v->mlx, v->screen.win);
	v->img->fontname = FONT1;
	v->img->fontname2 = FONT2;
	initmodes(v, argc);
	inittextures(v, 4);
	v->game.skybox = v->img[ESKYBOX];
	initsounds(v);
	initguardanim(v, -1);
	check_map(v);
	init_player_dir(v);
	mlx_do_key_autorepeatoff(v->mlx);
}
