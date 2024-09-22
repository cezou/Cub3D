/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_animations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:12:42 by pmagnero          #+#    #+#             */
/*   Updated: 2024/10/02 16:45:34 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/// @brief Update doors animation
/// @param v Vars
/// @param i Incremental variable =-1
void	update_door_animations(t_vars *v, int i)
{
	v->game.doortime += v->game.frametime;
	if (v->game.doortime > (1.0 / v->img[EDOOR].width))
	{
		while (++i < v->game.nb_door)
		{
			if (v->door[i].state == EOPENING)
				v->door[i].xdelta -= 4;
			else if (v->door[i].state == ECLOSING)
				v->door[i].xdelta += 4;
			if (v->door[i].state == EOPENING
				&& v->door[i].xdelta <= 0)
				v->door[i].state = EOPEN;
			else if (v->door[i].state == ECLOSING
				&& v->door[i].xdelta >= v->img[EDOOR].width)
				v->door[i].state = ECLOSE;
		}
		v->game.doortime -= 1.0 / v->img[EDOOR].width;
	}
}

/// @brief Update sprites animations
/// @param v Vars
void	update_sprites_animations(t_vars *v)
{
	int	i;

	i = -1;
	while (++i < v->game.nb_sprites)
	{
		if (v->sprites[i].isguard && timestamp_in_ms(v) - v->sprites[i].time
			>= (uint64_t)(10000 / v->game.fps))
		{
			if (!v->sprites[i].stop)
				v->sprites[i].animoff += v->img[v->sprites[i].img_i].animx;
			v->sprites[i].time = timestamp_in_ms(v);
		}
		if (v->sprites[i].isguard && v->sprites[i].img_i != EGUARDDEATH
			&& v->sprites[i].animoff >= v->img[v->sprites[i].img_i].width)
			v->sprites[i].animoff = 0;
		else if (v->sprites[i].isguard && v->sprites[i].img_i == EGUARDDEATH
			&& v->sprites[i].animoff >= v->img[v->sprites[i].img_i].width
			- v->img[v->sprites[i].img_i].animx)
		{
			v->sprites[i].stop = 1;
			v->sprites[i].animoff = v->img[v->sprites[i].img_i].width
				- v->img[v->sprites[i].img_i].animx;
		}
	}
}

/// @brief Update player animations
/// @param v Vars
void	update_player_animations(t_vars *v)
{
	if (!v->player.pattack)
		return ;
	if (timestamp_in_ms(v) - v->player.timerplayer
		>= (uint64_t)(4000 / v->game.fps))
	{
		v->player.animoff += v->player.img.animx;
		v->player.timerplayer = timestamp_in_ms(v);
	}
	if (v->player.animoff > v->player.img.width)
	{
		v->player.animoff = 0;
		v->player.pattack = 0;
		v->ray.hitguard = 0;
	}
}

void	update_player_movement(t_vars *v)
{
	if (v->player.moving)
	{
		v->game.cambobtime += v->game.frametime;
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

/// @brief Update animations
/// @param v Vars
void	update_animations(t_vars *v)
{
	update_sprites_animations(v);
	update_door_animations(v, -1);
	update_player_animations(v);
	update_player_movement(v);
	v->ray.pitch += sin((v->game.cambobtime) * 5.0f) * 1.4f;
	v->player.motionx = sin((v->game.cambobtime) * 8.0f) * 2.0f;
	v->player.motiony = sin((v->game.cambobtime) * 8.0f) * 5.0f;
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
