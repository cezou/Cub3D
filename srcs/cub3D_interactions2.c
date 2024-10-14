/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_interactions2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 09:51:53 by pmagnero          #+#    #+#             */
/*   Updated: 2024/10/14 12:54:58 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

/// @brief 
/// @param v 
/// @param card 
/// @param mess 
bool	give_card(t_vars *v, t_card card, char *mess)
{
	if (v->player.cards[card % 3])
		return (false);
	v->game.message = mess;
	v->player.cards[card % 3] = 1 + card / 3;
	v->hud.refreshcards = 1;
	return (true);
}

/// @brief 
/// @param v 
/// @param card 
bool	give_cards(t_vars *v, t_actor *a)
{
	if (a->img_i == EBKEY)
		return (give_card(v, it_bluecard, GOTBLUECARD));
	else if (a->img_i == EYKEY)
		return (give_card(v, it_yellowcard, GOTYELWCARD));
	else if (a->img_i == ERKEY)
		return (give_card(v, it_redcard, GOTREDCARD));
	else if (a->img_i == EBSKEY)
		return (give_card(v, it_blueskull, GOTBLUESKUL));
	else if (a->img_i == EYSKEY)
		return (give_card(v, it_yellowskull, GOTYELWSKUL));
	else if (a->img_i == ERSKEY)
		return (give_card(v, it_redskull, GOTREDSKULL));
	return (true);
}

// a weapon is found with two clip loads,
// a big item has five clip loads
// int	maxammo[NUMAMMO] = {200, 50, 300, 50};
// int	clipammo[NUMAMMO] = {10, 4, 20, 1};

/// @brief 
/// @param v 
/// @param num 
/// @param sp 
/// @return 
bool	give_body(t_vars *v, int num, int sp)
{
	if (v->player.hp >= MAXHEALTH)
		return (false);
	v->player.hp += num;
	if (v->player.hp > MAXHEALTH)
		v->player.hp = MAXHEALTH;
	v->game.message = GOTSTIM;
	if (v->player.hp < 25 && sp)
		v->game.message = GOTMEDINEED;
	else if (sp)
		v->game.message = GOTMEDIKIT;
	v->hud.refreshhealth = 1;
	v->hud.refreshdh = 1;
	return (true);
}

/// @brief 
/// @param v 
/// @param armortype 
/// @return 
bool	give_armor(t_vars *v, t_actor *a)
{
	int		hits;
	int		armortype;

	if (a->img_i != EPARMOR && a->img_i != EPARMOR1)
		return (true);
	armortype = 1;
	if (a->img_i == EPARMOR1)
		armortype = 2;
	hits = armortype * 100;
	if (v->player.armor >= hits)
		return (false);
	v->player.armortype = armortype;
	v->player.armor = hits;
	v->game.message = GOTARMOR;
	if (armortype == 2)
		v->game.message = GOTMEGA;
	v->hud.refresharmor = 1;
	return (true);
}

/// @brief 
/// @param v 
/// @param weapon 
/// @param mess 
/// @return 
bool	give_weapon(t_vars *v, t_weapons weapon, char *mess)
{
	bool	gaveammo;
	bool	gaveweapon;

	gaveammo = true;
	if (v->player.weapon[weapon].typeammo > -1)
		gaveammo = give_ammo(v, 0, 2, v->player.weapon[weapon].typeammo);
	if (v->player.weapons[weapon])
		gaveweapon = false;
	else
	{
		gaveweapon = true;
		v->player.weapons[weapon] = true;
	}
	v->hud.refreshammo = 1;
	v->hud.refreshammun = 1;
	v->hud.refreshweapon = 1;
	v->game.message = mess;
	return (gaveweapon || gaveammo);
}
