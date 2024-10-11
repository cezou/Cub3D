/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_animations_sprites.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:12:42 by pmagnero          #+#    #+#             */
/*   Updated: 2024/10/11 16:28:42 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3D.h"

/// @brief Update sprite animations attack range
/// @param v Vars
/// @param sp Sprite to update
inline void	update_sprite_anim_attackr(t_vars *v, t_sprite *sp)
{
	int	d;

	if (sp->animoff >= v->img[sp->img_i].width)
	{
		sp->justattack = 1;
		sp->animoff = 0;
		sp->state = ECHASE;
		sp->img_i = EGUARDW;
		sp->timestate = 0;
	}
	else if (sp->animoff == v->img[sp->img_i].animx)
	{
		d = sp->dmg / (p_random(v) % 5 + 1);
		v->player.hit += d;
		v->game.pain = d * 5;
	}
}

/// @brief Update sprite animation pain
/// @param v Vars
/// @param sp Sprite to update
inline void	update_sprite_anim_pain(t_vars *v, t_sprite *sp)
{
	sp->animoff = 0;
	if (timestamp_in_ms(v) - sp->timestate > 500)
	{
		sp->state = ECHASE;
		sp->img_i = EGUARDW;
		sp->timestate = 0;
	}
}

/// @brief Update sprite animation death
/// @param v Vars
/// @param sp Sprite to update
inline void	update_sprite_anim_death(t_vars *v, t_sprite *sp)
{
	if (sp->animoff >= v->img[sp->img_i].width - v->img[sp->img_i].animx)
	{
		sp->state = EDEAD;
		sp->hashitbox = 0;
		sp->stop = 1;
		sp->animoff = v->img[sp->img_i].width - v->img[sp->img_i].animx;
	}
}

/// @brief Update sprite animation chase
/// @param v Vars
/// @param sp Sprite to update
inline void	update_sprite_anim_chase(t_vars *v, t_sprite *sp)
{
	if (sp->animoff >= v->img[sp->img_i].width)
	{
		sp->justattack = 0;
		sp->animoff = 0;
	}
}

// if (v->sprites[i].state != EIDLE && v->sprites[i].state != EDEAD
// 	&& v->sprites[i].state != ECHASE && v->sprites[i].state != EATTACKR
// 	&& v->sprites[i].animoff >= v->img[v->sprites[i].img_i].width)
// 	v->sprites[i].animoff = 0;

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
			>= (uint64_t)(5000 / v->game.fps))
		{
			if (v->sprites[i].state != EIDLE && !v->sprites[i].stop)
				v->sprites[i].animoff += v->img[v->sprites[i].img_i].animx;
			v->sprites[i].time = timestamp_in_ms(v);
			if (v->sprites[i].state == EDEAD)
				update_sprite_anim_death(v, &v->sprites[i]);
			else if (v->sprites[i].state == EPAIN)
				update_sprite_anim_pain(v, &v->sprites[i]);
			else if (v->sprites[i].state == EATTACKR)
				update_sprite_anim_attackr(v, &v->sprites[i]);
			if (v->sprites[i].state == ECHASE)
				update_sprite_anim_chase(v, &v->sprites[i]);
		}
	}
}
