/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_animations_player.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:12:42 by pmagnero          #+#    #+#             */
/*   Updated: 2024/10/30 11:23:00 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3D.h"

/// @brief Update player animations
/// @param v Vars
// v->ray.hitguard = 0; Shots per minute
void	update_player_animations(t_vars *v)
{
	if (!v->player.pattack)
		return ;
	if (timestamp_in_ms(v) - v->player.timerplayer
		>= (uint64_t)(60))
	{
		v->player.animoff += v->player.currweapon.img.animx;
		v->player.timerplayer = timestamp_in_ms(v);
	}
	if (v->player.animoff > v->player.currweapon.img.width)
	{
		v->player.animoff = 0;
		if (!v->player.attack)
		{
			v->player.pattack = 0;
			v->ray.hitguard = 0;
		}
	}
}

/// @brief Update player movement/bobbing
/// @param v Vars
void	update_player_movement(t_vars *v)
{
	if (v->player.moving)
	{
		v->game.cambobtime += 0.016 * v->player.movespeedy;
		v->game.playbobtime += v->game.frametime;
		if (v->player.movingy)
		{
			v->player.movespeedy += v->game.frametime * v->player.accy;
			if (v->player.movespeedy > v->game.frametime * v->player.maxspeedy)
				v->player.movespeedy = v->game.frametime * v->player.maxspeedy;
		}
	}
	else
	{
		v->game.cambobtime = 0;
		v->game.playbobtime = 0;
		if (!v->player.movingy)
		{
			v->player.movespeedy -= v->game.frametime * v->player.deccy;
			if (v->player.movespeedy < 0.0)
				v->player.movespeedy = 0.0;
			moveplayery(v, v->player.dir);
		}
	}
}

/// @brief Update player jump/bobbing
/// @param v Vars
// v->ray.pitch += sin((v->game.cambobtime) * 5.0f) * 0.5f;
void	update_player_motion(t_vars *v)
{
	v->player.motionx = sin((v->game.playbobtime) * 8.0f) * 2.0f;
	v->player.motiony = sin((v->game.playbobtime) * 8.0f) * 5.0f;
	if (v->player.jumping)
	{
		v->player.z += 1000.0 * v->game.frametime;
		if (v->player.z >= v->screen.gameh / 2)
			v->player.jumping = 0;
	}
	else
	{
		v->player.injump = 1;
		v->player.z -= 1000.0 * v->game.frametime;
		if (v->player.z < 0.0)
		{
			v->player.z = 0.0;
			v->player.injump = 0;
		}
	}
}

/// @brief Update player hp/damage calculations
/// @param v Vars
void	update_player_hp(t_vars *v)
{
	if (v->player.hit)
	{
		v->player.hp--;
		if (v->player.hp < 0)
		{
			v->player.hp = 0;
			v->game.won = 2;
			mlx_loop_end(v->mlx);
		}
		v->player.hit--;
	}
	if (v->game.pain > 0)
		v->game.pain--;
	v->hud.refreshhealth = 1;
	v->hud.refresharmor = 1;
	if (v->player.hp >= 60 && v->player.hp < 80)
	{
		v->hud.refreshdh = 1;
		v->hud.headid += v->hud.head.animx;
	}
}

/// @brief Update player
/// @param v Vars
void	update_player(t_vars *v)
{
	update_player_animations(v);
	update_player_movement(v);
	update_player_motion(v);
	update_player_hp(v);
}
