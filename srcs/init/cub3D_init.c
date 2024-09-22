/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:09:56 by pmagnero          #+#    #+#             */
/*   Updated: 2024/10/04 11:25:33 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/// @brief Array of objects
///	{x, y, sprite ID, scale factor, vertical position}
const t_point3	g_objs[2] = {
{14.0, 8.0, EPARMOR, 5.0, 128.0},
{15.0, 8.0, EPARMOR, 1.0, 0}
};

void	initvars(t_vars *v)
{
	v->game.fps = 60;
	v->hud.refresh = 1;
	v->hud.refreshhealth = 1;
	v->hud.refresharmor = 1;
	v->hud.refreshammo = 1;
	v->hud.refreshammun = 1;
	v->hud.refreshweapon = 1;
	v->hud.refreshcards = 1;
	v->hud.refreshdh = 1;
	v->player.movespeedx = 3.0;
	v->player.rotspeed = 2.0;
	v->player.mouserotspeed = 0.1;
	v->player.accx = 5.0;
	v->player.accy = 0.08;
	v->player.maxspeedx = 0.1;
	v->player.maxspeedy = 5.0;
	v->player.deccx = 0.1;
	v->player.deccy = 0.2;
	v->mouse.sensx = 20.0;
	v->mouse.sensy = 10.0;
	v->player.hp = 100;
	v->player.maxammo[0] = 200;
	v->player.maxammo[1] = 50;
	v->player.maxammo[2] = 50;
	v->player.maxammo[3] = 300;
	v->player.weapons[0] = 1;
	v->player.weapons[1] = 1;
	v->player.ammo[0] = 50;
	v->player.cards[0] = 2;
	v->player.cards[1] = 2;
	v->player.cards[2] = 1;
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

void	init_guard(t_vars *v, int j, t_map *tmp, int i)
{
	while (tmp)
	{
		if (tmp->val == 'G')
		{
			v->sprites[++j] = (t_sprite){0};
			v->sprites[j].x = tmp->x;
			v->sprites[j].y = tmp->y;
			v->sprites[j].hp = 100;
			v->sprites[j].img_i = EGUARDW;
			v->sprites[j].vdiv = 1.0;
			v->sprites[j].udiv = 1.0;
			v->sprites[j].isguard = 1;
		}
		tmp = tmp->right;
	}
	while (++j < v->game.nb_sprites)
	{
		v->sprites[j] = (t_sprite){0};
		v->sprites[j].x = g_objs[++i].x;
		v->sprites[j].y = g_objs[i].y;
		v->sprites[j].img_i = g_objs[i].z;
		v->sprites[j].vdiv = g_objs[i].uv;
		v->sprites[j].udiv = g_objs[i].uv;
		v->sprites[j].vmove = g_objs[i].v;
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
	v->game.nb_sprites = v->game.nb_guard + 2;
	init_doors(v);
	v->sprites = (t_sprite *)malloc(sizeof(t_sprite) * (v->game.nb_sprites));
	if (!v->sprites)
		exit((prterr(v, ERRMALL, 1, 0), 1));
	init_guard(v, -1, v->mapv.map, -1);
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
