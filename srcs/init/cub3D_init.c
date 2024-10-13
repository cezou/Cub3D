/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:09:56 by pmagnero          #+#    #+#             */
/*   Updated: 2024/10/13 19:41:48 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

// DAMAGES
//					HP		MIN	MAX

// Trooper 			20 		3 	15
// Seargeant 		30 		3 	(Per Pellet) 3 Pellets
// 15 (Per Pellet) 3 Pellets
// Imp 				60 		3 	24
// Commando 		70 		3 	15
// Lost Soul 		100 	3 	24
// Hell Knight 		500 	10 	(Melee) 8 (Ranged) 	80 (Melee) 64 (Ranged)
// Arachnotron 		500 	5 	40
// Baron of hell 	1,000 	10 	(Melee) 8 (Ranged) 	80 (Melee) 64 (Ranged)
// Mancubus 		600 	8 	(Per Fireball) 	64 (Per Fireball)
// Cacodemon 		400 	10 	(Melee) 5 (Ranged) 	60 (Melee) 40 (Ranged)
// Spiderdemon 		3,000 	3 	(Per Pellet) 	15 (Per Pellet)
// Cyberdemon 		4,000 	20 	(Direct Hit) 0 (Blast Damage) 
// 160 (Direct Hit) 128 (Blast Damage)
// Arch-Vile 		700 	20 	(Direct Hit) 0 (Blast Damage)
// 20 (Direct Hit) 70 (Blast Damage)
// Revenant 		300 	8 	(Melee) 10 (Ranged) 	64 (Melee) 80 (Ranged)
// Demon 			150 	4 	40
// Wolfenstein SS 	50 		3 	15

//	PAINCHANCE

// Commander Keen 		256 (100%) 		100
// Lost soul 			256 (100%) 		100
// Boss brain 			255 (99.61%) 	250
// Imp 					200 (79.30%) 	60
// Zombieman 			200 (79.30%) 	20
// Demon 				180 (70.70%) 	150
// Spectre 				180 (70.70%) 	150
// Heavy weapon dude 	170 (67.58%) 	70
// Wolfenstein SS 		170 (67.58%) 	50
// Shotgun guy 			170 (67.58%) 	30
// Arachnotron 			128 (50%) 		500
// Cacodemon 			128 (50%) 		400
// Pain elemental 		128 (50%) 		400
// Revenant 			100 (39.84%) 	300
// Mancubus 			80 (30.86%) 	600
// Baron of Hell 		50 (16.80%) 	1000
// Hell knight 			50 (16.80%) 	500
// Spiderdemon 			40 (12.89%) 	3000
// Cyberdemon 			20 (5.47%) 		4000
// Arch-vile 			10 (3.13%) 		700
// Barrel 				0 (0%) 			20

#define NUM_OBJS 21

/// @brief Array of objects
///	{x, y, sprite ID, scale factor, vertical position, hashitbox, pickable}
const t_obj	g_objs[NUM_OBJS] = {
{14.0, 9.0, EPARMOR, 5.0, 128.0, 1, 1}, // Scaled down
{14.0, 9.5, EPARMOR1, 5.0, 128.0, 1, 1},
{14.0, 10.0, ESTIM, 5.0, 128.0, 1, 1},
{14.0, 10.5, EMEDI, 5.0, 128.0, 1, 1},
{14.0, 11.0, EPCLIP, 5.0, 128.0, 1, 1},
{14.0, 11.5, EPSHELL, 5.0, 128.0, 1, 1},
{14.0, 12.0, EPROCK, 5.0, 128.0, 1, 1},
{14.0, 12.5, EPCELL, 5.0, 128.0, 1, 1},
{14.0, 13.0, EBKEY, 5.0, 128.0, 1, 1},
{14.0, 13.5, EYKEY, 5.0, 128.0, 1, 1},
{14.0, 14.0, ERKEY, 5.0, 128.0, 1, 1},
{14.0, 14.5, EBSKEY, 5.0, 128.0, 1, 1},
{14.0, 15.0, EYSKEY, 5.0, 128.0, 1, 1},
{14.0, 15.5, ERSKEY, 5.0, 128.0, 1, 1},
{14.0, 16.0, EPBFG, 2.0, 64.0, 1, 1},
{14.0, 16.5, EPSHOTGUN, 2.0, 64.0, 1, 1},
{14.0, 17.0, EPGATLIN, 2.0, 64.0, 1, 1},
{14.0, 17.5, EPROCKETL, 2.0, 64.0, 1, 1},
{14.0, 18.0, EPPLASMA, 2.0, 64.0, 1, 1},
{14.0, 18.5, EPCHAINSAW, 2.0, 64.0, 1, 1},
{14.0, 19.0, EPSUPERSHOTGUN, 2.0, 64.0, 1, 1}
};

/// @brief Init Weapon stats
/// @param v Vars
/// {active, ammo, maxammo, typeammo, dmg, soundid, range, img}
void	initweapon(t_vars *v)
{
	v->player.weapon[EFIST] = (t_weapon){1, -1, -1, -1, 20, 0, 2.0,
		v->img[EIFIST]};
	v->player.weapon[EGUN] = (t_weapon){1, 50, 200, EBULL, 15, 0, 1000.0,
		v->img[EIGUN]};
	v->player.weapon[ESHOTGUN] = (t_weapon){1, 8, 50, ESHELL, 100, 0, 1000.0,
		v->img[EIGUN]};
	v->player.weapon[EBFG] = (t_weapon){1, 40, 300, ECELL, 800, 0, 1000.0,
		v->img[EIGUN]};
	v->player.weapon[EGATLIN] = (t_weapon){1, 20, 200, EBULL, 15, 0, 1000.0,
		v->img[EIGUN]};
	v->player.weapon[EROCKETL] = (t_weapon){1, 2, 50, EROCK, 160, 0, 1000.0,
		v->img[EIGUN]};
	v->player.weapon[EPLASMA] = (t_weapon){1, 40, 300, ECELL, 40, 0, 1000.0,
		v->img[EIGUN]};
	v->player.weapon[ECHAINSAW] = (t_weapon){1, -1, -1, -1, 20, 0, 2.0,
		v->img[EIGUN]};
	v->player.weapon[ESUPERSHOTGUN] = (t_weapon){1, 8, 50, ESHELL, 245, 0,
		1000.0, v->img[EIGUN]};
	v->player.currweapon = v->player.weapon[EFIST];
}

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
	v->player.rotspeed = 1.0;
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
	v->player.maxammo[EBULL] = 200;
	v->player.maxammo[ESHELL] = 50;
	v->player.maxammo[EROCK] = 50;
	v->player.maxammo[ECELL] = 300;
	v->player.clipammo[EBULL] = 10;
	v->player.clipammo[ESHELL] = 4;
	v->player.clipammo[EROCK] = 1;
	v->player.clipammo[ECELL] = 20;
	v->player.weapons[0] = 1;
	v->player.weapons[1] = 1;
	v->player.ammo[0] = 50;
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

void	init_objects(t_vars *v, int j)
{
	int	i;

	i = -1;
	while (++j < v->game.nb_sprites)
	{
		v->sprites[j] = (t_sprite){0};
		v->sprites[j].x = g_objs[++i].x;
		v->sprites[j].y = g_objs[i].y;
		v->sprites[j].img_i = g_objs[i].img_id;
		v->sprites[j].vdiv = g_objs[i].uv;
		v->sprites[j].udiv = g_objs[i].uv;
		v->sprites[j].vmove = g_objs[i].v;
		v->sprites[j].hashitbox = g_objs[i].h;
		v->sprites[j].pickable = g_objs[i].pickable;
		v->sprites[j].active = 1;
	}
}

int	init_guard(t_vars *v, int j, t_map *tmp)
{
	while (tmp)
	{
		if (tmp->val == 'G')
		{
			v->sprites[++j] = (t_sprite){0};
			v->sprites[j].x = tmp->x;
			v->sprites[j].y = tmp->y;
			v->sprites[j].hp = 60;
			v->sprites[j].img_i = EGUARDW;
			v->sprites[j].vdiv = 1.0;
			v->sprites[j].udiv = 1.0;
			v->sprites[j].isguard = 1;
			v->sprites[j].ms = 2.2;
			v->sprites[j].painchance = 40;
			v->sprites[j].hasmelee = 0;
			v->sprites[j].hasrange = 1;
			v->sprites[j].hashitbox = 1;
			v->sprites[j].dmg = 15;
			v->sprites[j].active = 1;
		}
		tmp = tmp->right;
	}
	return (j);
}

void	init_sprites(t_vars *v)
{
	int	j;

	j = -1;
	j = init_guard(v, j, v->mapv.map);
	init_objects(v, j);
}

void	check_map(t_vars *v)
{
	init_random_melting_array(v);
	parse(v, -1, NULL);
	v->player.x = v->player.player->x + 0.5;
	v->player.y = v->player.player->y + 0.5;
	v->player.animp = EIFIST;
	v->player.animoff = 0;
	v->game.nb_sprites = v->game.nb_guard + NUM_OBJS;
	init_doors(v);
	v->sprites = (t_sprite *)malloc(sizeof(t_sprite) * (v->game.nb_sprites));
	if (!v->sprites)
		exit((prterr(v, ERRMALL, 1, 0), 1));
	init_sprites(v);
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
	(ft_bzero(v->keys, MAX_KEYS), ft_bzero(v->mouses, MAX_MOUSE));
	initwindow(v, argc, argv);
	initmodes(v, argc);
	inittextures(v, 4);
	v->game.skybox = v->img[ESKYBOX];
	initsounds(v);
	inithud(v);
	initplayeranim(v);
	initweapon(v);
	initguardanim(v);
	check_map(v);
	init_player_dir(v);
	mlx_do_key_autorepeatoff(v->mlx);
}
