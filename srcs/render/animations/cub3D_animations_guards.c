/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_animations_guards.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:12:42 by pmagnero          #+#    #+#             */
/*   Updated: 2024/10/15 19:36:36 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3D.h"

/// @brief Update sprite animations attack range
/// @param v Vars
/// @param a Sprite to update
inline void	update_sprite_anim_attackr(t_vars *v, t_actor *a)
{
	int	d;

	if (a->animoff >= v->img[a->img_i].width)
	{
		a->justattack = 1;
		a->animoff = 0;
		a->state = ECHASE;
		a->img_i = EGUARDW;
		a->timestate = 0;
	}
	else if (a->animoff == v->img[a->img_i].animx)
	{
		d = a->dmg / (p_random(v) % 5 + 1);
		v->player.hit += d;
		v->game.pain = d * 5;
	}
}

/// @brief Update sprite animation pain
/// @param v Vars
/// @param a Sprite to update
inline void	update_sprite_anim_pain(t_vars *v, t_actor *a)
{
	a->animoff = 0;
	if (timestamp_in_ms(v) - a->timestate > 500)
	{
		a->state = ECHASE;
		a->img_i = EGUARDW;
		a->timestate = 0;
	}
}

/// @brief Update sprite animation death
/// @param v Vars
/// @param a Sprite to update
inline void	update_sprite_anim_death(t_vars *v, t_actor *a)
{
	if (a->animoff >= v->img[a->img_i].width - v->img[a->img_i].animx)
	{
		a->state = EDEAD;
		a->hashitbox = 0;
		a->stop = 1;
		a->animoff = v->img[a->img_i].width - v->img[a->img_i].animx;
	}
}

/// @brief Update sprite animation chase
/// @param v Vars
/// @param a Sprite to update
inline void	update_sprite_anim_chase(t_vars *v, t_actor *a)
{
	if (a->animoff >= v->img[a->img_i].width)
	{
		a->justattack = 0;
		a->animoff = 0;
	}
}

// if (v->sprites[i].state != EIDLE && v->sprites[i].state != EDEAD
// 	&& v->sprites[i].state != ECHASE && v->sprites[i].state != EATTACKR
// 	&& v->sprites[i].animoff >= v->img[v->sprites[i].img_i].width)
// 	v->sprites[i].animoff = 0;

/// @brief Update guards movement/animations
/// @param v Vars
///	@param actor Actor guard
void	update_guards(t_vars *v, t_actor **actor)
{
	t_actor	*tmp;

	tmp = *actor;
	if (!tmp->isguard)
		return ;
	if (tmp->state != EIDLE && !tmp->stop)
		tmp->animoff += v->img[tmp->img_i].animx;
	tmp->time = timestamp_in_ms(v);
	if (tmp->state == EDEAD)
		update_sprite_anim_death(v, tmp);
	else if (tmp->state == EPAIN)
		update_sprite_anim_pain(v, tmp);
	else if (tmp->state == EATTACKR)
		update_sprite_anim_attackr(v, tmp);
	if (tmp->state == ECHASE)
		update_sprite_anim_chase(v, tmp);
	if (tmp->state == ECHASE)
	{
		tmp->x += tmp->ms * v->game.frametime
			* (v->player.x + 0.5 - tmp->x);
		tmp->y += tmp->ms * v->game.frametime
			* (v->player.y + 0.5 - tmp->y);
	}
}
