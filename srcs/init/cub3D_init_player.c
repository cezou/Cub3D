/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_init_player.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:09:56 by pmagnero          #+#    #+#             */
/*   Updated: 2024/10/28 23:19:21 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

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

/// @brief Init Weapon stats
/// @param v Vars
/// {active, ammo, maxammo, typeammo, dmg, soundid, isprojectile,
// 	dmgtic, range, img}
void	initweapon(t_vars *v)
{
	v->player.weapon[EFIST] = (t_weapon){1, -1, -1, NOAMMO, 20, 0, 0, 4, 2.0,
		v->img[EIFIST]};
	v->player.weapon[EGUN] = (t_weapon){1, 50, 200, EBULL, 15, 0, 0, 4, 1000.0,
		v->img[EIGUN]};
	v->player.weapon[ESHOTGUN] = (t_weapon){1, 8, 50, ESHELL, 100, 0, 0, 4,
		1000.0, v->img[EISHOTGUN]};
	v->player.weapon[EGATLIN] = (t_weapon){1, 20, 200, EBULL, 15, 0, 0, 3,
		1000.0, v->img[EIGATLIN]};
	v->player.weapon[EROCKETL] = (t_weapon){1, 2, 50, EROCK, 160, 0, 1, -1,
		1000.0, v->img[EIROCKl]};
	v->player.weapon[EPLASMA] = (t_weapon){1, 40, 300, ECELL, 40, 0, 1, -1,
		1000.0, v->img[EIPLASMA]};
	v->player.weapon[ECHAINSAW] = (t_weapon){1, -1, -1, NOAMMO, 20, 0, 0, 4,
		2.0, v->img[EICHAINSAW]};
	v->player.weapon[ESUPERSHOTGUN] = (t_weapon){1, 8, 50, ESHELL, 300, 245,
		0, 4, 1000.0, v->img[EISUPERSHOTGUN]};
	v->player.weapon[EBFG] = (t_weapon){1, 40, 300, ECELL, 800, 0, 1, -1,
		1000.0, v->img[EIBFG]};
	v->player.currweapon = v->player.weapon[EFIST];
}

void	init_player_datas(t_vars *v)
{
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
	v->player.animp = EIFIST;
	v->player.animoff = 0;
}
