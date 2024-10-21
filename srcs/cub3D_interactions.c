/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_interactions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 09:51:53 by pmagnero          #+#    #+#             */
/*   Updated: 2024/10/21 15:47:40 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

/// @brief Should be a switch case but you know this fcking norm
/// @param v Vars
/// @param img Image id
/// @param ammo Ammot type id
/// @return Ammot type
t_ammo	give_ammo_switch(t_vars *v, int img, t_ammo ammo)
{
	if (img == EPCLIP)
	{
		ammo = EBULL;
		v->game.message = GOTCLIP;
	}
	else if (img == EPSHELL)
	{
		ammo = ESHELL;
		v->game.message = GOTSHELLS;
	}
	else if (img == EPROCK)
	{
		ammo = EROCK;
		v->game.message = GOTROCKET;
	}
	else if (img == EPCELL)
	{
		ammo = ECELL;
		v->game.message = GOTCELL;
	}
	return (ammo);
}

/// @brief Give ammo
/// @param v Vars
/// @param img Image id
/// @param num Number of clip load
/// @param ammo Ammo type id
/// @return Boolean true if can give ammo
// Num is the number of clip loads,
// not the individual count (0= 1/2 clip).
// Returns false if the ammo can't be picked up at all
bool	give_ammo(t_vars *v, int img, int num, t_ammo ammo)
{
	if (img != 0)
		ammo = NOAMMO;
	if (img != 0 && img != EPCLIP && img != EPSHELL && img != EPROCK
		&& img != EPCELL)
		return (true);
	ammo = give_ammo_switch(v, img, ammo);
	if (v->player.ammo[ammo] == v->player.maxammo[ammo] || ammo == NOAMMO)
		return (false);
	if (num)
		num *= v->player.clipammo[ammo];
	else
		num = v->player.clipammo[ammo] / 2;
	v->player.ammo[ammo] += num;
	if (v->player.ammo[ammo] > v->player.maxammo[ammo])
		v->player.ammo[ammo] = v->player.maxammo[ammo];
	return (v->hud.refreshammo = 1, v->hud.refreshammun = 1, true);
}

/// @brief Interaction with things/items pickup
/// @param v Vars
/// @param a Thing touched
void	touch_thing(t_vars *v, t_actor *a)
{
	if (a->img_i == ESTIM && !give_body(v, 10, 0))
		return ;
	else if (a->img_i == EMEDI && !give_body(v, 25, 1))
		return ;
	else if (a->img_i == EPBFG && !give_weapon(v, EBFG, GOTBFG9000))
		return ;
	else if (a->img_i == EPSHOTGUN && !give_weapon(v, ESHOTGUN, GOTSHOTGUN))
		return ;
	else if (a->img_i == EPGATLIN && !give_weapon(v, EGATLIN, GOTCHAINGUN))
		return ;
	else if (a->img_i == EPROCKETL && !give_weapon(v, EROCKETL, GOTLAUNCHER))
		return ;
	else if (a->img_i == EPPLASMA && !give_weapon(v, EPLASMA, GOTPLASMA))
		return ;
	else if (a->img_i == EPCHAINSAW && !give_weapon(v, ECHAINSAW, GOTCHAINSAW))
		return ;
	else if (a->img_i == EPSUPERSHOTGUN
		&& !give_weapon(v, ESUPERSHOTGUN, GOTSHOTGUN2))
		return ;
	if (!give_armor(v, a) || !give_ammo(v, a->img_i, 1, 0)
		|| !give_cards(v, a))
		return ;
	ft_printf(1, "%s\n", v->game.message);
}
// sound = sfx_wpnup;
// S_StartSound (NULL, sound);
