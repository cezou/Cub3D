/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_animations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:12:42 by pmagnero          #+#    #+#             */
/*   Updated: 2024/10/10 16:34:10 by pmagnero         ###   ########.fr       */
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
		if (!v->sprites[i].isguard)
			continue ;
		if (timestamp_in_ms(v) - v->sprites[i].time
			>= (uint64_t)(10000 / v->game.fps))
		{
			if (v->sprites[i].state != EIDLE && !v->sprites[i].stop)
				v->sprites[i].animoff += v->img[v->sprites[i].img_i].animx;
			v->sprites[i].time = timestamp_in_ms(v);
		}
		if (v->sprites[i].state != EIDLE && v->sprites[i].state != EDEAD
			&& v->sprites[i].animoff >= v->img[v->sprites[i].img_i].width)
			v->sprites[i].animoff = 0;
		else if (v->sprites[i].state == EDEAD
			&& v->sprites[i].animoff >= v->img[v->sprites[i].img_i].width
			- v->img[v->sprites[i].img_i].animx)
		{
			v->sprites[i].state = EDEAD;
			v->sprites[i].stop = 1;
			v->sprites[i].animoff = v->img[v->sprites[i].img_i].width
				- v->img[v->sprites[i].img_i].animx;
		}
		else if (v->sprites[i].state == EPAIN)
		{
			v->sprites[i].animoff = 0;
			v->sprites[i].hit = 0;
			if (timestamp_in_ms(v) - v->sprites[i].timestate > 250)//p_random(v) < v->sprites[i].painchance && 
			{
				v->sprites[i].state = ECHASE;
				v->sprites[i].img_i = EGUARDW;
				v->sprites[i].timestate = 0;
			}
		}
		else if (v->sprites[i].state == EATTACKR)
		{
			// v->sprites[i].animoff = 0;
			// v->sprites[i].hit = 0;
			if (timestamp_in_ms(v) - v->sprites[i].timestate > 250)
			{
				v->sprites[i].state = ECHASE;
				v->sprites[i].img_i = EGUARDW;
				v->sprites[i].timestate = 0;
			}
		}
	}
}
// printf("%lu | %lu | %lu\n", v->sprites[i].time, v->sprites[i].timestate, timestamp_in_ms(v));
// printf("Guard: %d, x: %f, y: %f\n", i, v->sprites[i].x, v->sprites[i].y);

/// @brief 
/// @param v 
void	update_guard_movement(t_vars *v)
{
	int	i;

	i = -1;
	if (v->game.pause)
		return ;
	while (++i < v->game.nb_sprites)
	{
		if (!v->sprites[i].isguard)
			continue ;
		if (timestamp_in_ms(v) - v->sprites[i].timem
			>= (uint64_t)(10000 / v->game.fps))
		{
			v->sprites[i].timem = timestamp_in_ms(v);
			if (v->sprites[i].state == ECHASE)
			{
				v->sprites[i].x = v->sprites[i].x + v->sprites[i].ms
					* v->game.frametime * (v->player.x - v->sprites[i].x);
				v->sprites[i].y = v->sprites[i].y + v->sprites[i].ms
					* v->game.frametime * (v->player.y - v->sprites[i].y);
			}
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
		v->player.animoff += v->player.currweapon.img.animx;
		v->player.timerplayer = timestamp_in_ms(v);
	}
	if (v->player.animoff > v->player.currweapon.img.width)
	{
		v->player.animoff = 0;
		v->player.pattack = 0;
		v->ray.hitguard = 0; // Shots per minute
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
	update_guard_movement(v);
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
