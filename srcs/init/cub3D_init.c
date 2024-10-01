/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:09:56 by pmagnero          #+#    #+#             */
/*   Updated: 2024/10/01 12:18:06 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	initvars(t_vars *v)
{
	v->game.fps = 64;
	v->hud.refresh = 1;
	v->player.movespeedy = 0;
	v->player.movespeedx = 3.0;
	v->player.rotspeed = 2.0;
	v->player.mouserotspeed = 2.5;
	v->player.accx = 5.0;
	v->player.accy = 0.08;
	v->player.maxspeedx = 0.2;
	v->player.maxspeedy = 0.15;
	v->player.deccx = 0.1;
	v->player.deccy = 0.2;
}

void	initmodes(t_vars *v, int argc)
{
	v->img->fontname = FONT1;
	v->img->fontname2 = FONT2;
	initvars(v);
	v->ray.zbuffer = (int *)malloc(sizeof(int) * v->screen.resw);
	if (!v->ray.zbuffer)
		exit((prterr(v, ERRMALL, 1, 1), 1));
	initpathtext(v);
	if (argc < 2 || argc > 4)
		exit((prterr(v, "Too many/few arguments\n", 1, 1), 1));
}

void	init_doors(t_vars *v)
{
	int		i;
	t_map	*tmp;

	i = -1;
	tmp = v->mapv.map;
	v->door = (t_door *)malloc(sizeof(t_door) * (v->game.nb_door));
	if (!v->door)
		exit((prterr(v, ERRMALL, 1, 0), 1));
	while (tmp)
	{
		if (tmp->val == 'D')
		{
			v->door[++i].x = tmp->x;
			v->door[i].y = tmp->y;
			v->door[i].time = 0;
			v->door[i].state = ECLOSE;
			v->door[i].img_i = EDOOR;
			v->door[i].xdelta = v->img[v->door[i].img_i].width;
		}
		tmp = tmp->right;
	}
}

void	init_guard(t_vars *v, int j, t_map *tmp)
{
	v->guard = (t_guard *)malloc(sizeof(t_guard) * (v->game.nb_guard));
	if (!v->guard)
		exit((prterr(v, ERRMALL, 1, 0), 1));
	while (tmp)
	{
		if (tmp->val == 'G')
		{
			v->guard[++j].x = tmp->x;
			v->guard[j].y = tmp->y;
			v->guard[j].time = 0;
			v->guard[j].stop = 0;
			v->guard[j].hp = 100;
			v->guard[j].img_i = EGUARDW;
			v->guard[j].xdelta = 0;
			v->guard[j].vdiv = 1.0;
			v->guard[j].udiv = 1.0;
			v->guard[j].vmove = 0;
			v->guard[j].dist = 0;
			v->guard[j].animoff = v->img[v->guard[j].img_i].animx;
		}
		tmp = tmp->right;
	}
}

void	check_map(t_vars *v)
{
	init_random_melting_array(v);
	parse(v, -1, NULL);
	v->player.x = v->player.player->x + 0.5;
	v->player.y = v->player.player->y + 0.5;
	v->player.animp = EFIST;
	v->player.animoff = 0;
	init_doors(v);
	init_guard(v, -1, v->mapv.map);
}

void	init(t_vars *v, int argc, char **argv)
{
	int	i;

	i = -1;
	ft_memset(v, 0, sizeof(t_vars));
	v->mlx = mlx_init();
	if (!v->mlx)
		exit((perr("MLX init failed"), FAIL));
	parsing(argc, argv[1], v);
	v->img = (t_imga *)malloc(sizeof(t_imga) * (COMP_N + 1));
	if (!v->img)
		exit((prterr(v, ERRMALL, 1, 1), 1));
	while (v->img && ++i <= COMP_N)
		v->img[i] = (t_imga){0};
	(ft_bzero(v->keys, MAX_KEYS), initwindow(v, argc, argv));
	mlx_mouse_hide(v->mlx, v->screen.win);
	initmodes(v, argc);
	inittextures(v, 4);
	v->game.skybox = v->img[ESKYBOX];
	initsounds(v);
	inithud(v);
	initplayeranim(v);
	initguardanim(v);
	check_map(v);
	init_player_dir(v);
	mlx_do_key_autorepeatoff(v->mlx);
}
