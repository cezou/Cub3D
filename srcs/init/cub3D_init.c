/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:09:56 by pmagnero          #+#    #+#             */
/*   Updated: 2024/10/28 23:23:55 by pmagnero         ###   ########.fr       */
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

void	initvars(t_vars *v)
{
	v->game.fps = 1000;
	v->hud.refresh = 1;
	v->hud.refreshhealth = 1;
	v->hud.refresharmor = 1;
	v->hud.refreshammo = 1;
	v->hud.refreshammun = 1;
	v->hud.refreshweapon = 1;
	v->hud.refreshcards = 1;
	v->hud.refreshdh = 1;
	init_player_datas(v);
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
	if (argc > 5)
		exit((prterr(v, "Too many arguments\n", 1, 1), 1));
}

// v->game.nb_actors = v->game.nb_guard + NUM_OBJS;
// printactors(v);
void	check_map(t_vars *v)
{
	init_random_melting_array(v);
	parse(v, -1, NULL);
	v->player.x = v->player.player->x + 0.5;
	v->player.y = v->player.player->y + 0.5;
	init_actors(v);
}

void	init2(t_vars *v)
{
	inittextures(v, 4);
	initsounds(v);
	inithud(v);
	initplayeranim(v);
	initweapon(v);
	initguardanim(v);
	check_map(v);
	init_thread_pool(v, -1);
	init_player_dir(v);
	mlx_do_key_autorepeatoff(v->mlx);
}

void	init(t_vars *v, int argc, char **argv)
{
	int	i;

	i = -1;
	ft_memset(v, 0, sizeof(t_vars));
	v->mlx = mlx_init();
	if (!v->mlx)
		exit((perr("MLX init failed"), FAIL));
	v->mapv.filename = argv[1];
	parsing(argc, v->mapv.filename, v);
	if (argc == 3 || argc == 5)
		parsing_csv((v->game.ext = argv[2], v->game.ext), v);
	v->img = (t_imga *)malloc(sizeof(t_imga) * (COMP_N + 1));
	if (!v->img)
		exit((prterr(v, ERRMALL, 1, 1), 1));
	while (v->img && ++i <= COMP_N)
		v->img[i] = (t_imga){0};
	(ft_bzero(v->keys, MAX_KEYS), ft_bzero(v->mouses, MAX_MOUSE));
	initwindow(v, argc, argv);
	initmodes(v, argc);
	init2(v);
}
