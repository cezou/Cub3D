/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_interactions3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 09:51:53 by pmagnero          #+#    #+#             */
/*   Updated: 2024/10/29 19:11:04 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

/// @brief Calculate projectile target
/// @param v Vars
/// @param actor Actor
void	calc_target(t_vars *v, t_actor **actor)
{
	t_actor		*a;
	double		hitx;
	double		hity;
	double		norm;

	a = *actor;
	hitx = 0;
	hity = 0;
	if (!v->ray.hitside)
		hity = v->ray.hitx;
	else
		hitx = v->ray.hitx;
	a->vectorx = (double)(v->ray.centerhit->x) + hitx - a->x;
	a->vectory = (double)(v->ray.centerhit->y) + hity - a->y;
	norm = sqrt((a->vectorx * a->vectorx) + (a->vectory * a->vectory));
	a->vectorx /= norm;
	a->vectory /= norm;
	a->target = v->ray.centerhit;
	a->targetdist = v->ray.centerdist;
	a->norm = sqrt(pow((a->ms * a->vectorx), 2) + pow((a->ms * a->vectory), 2));
}

/// @brief Init a new projectile actor
/// @param v Vars
void	fire_projectile(t_vars *v)
{
	t_actor		*a;

	a = new_actor(v);
	a->active = 1;
	a->x = v->player.x;
	a->y = v->player.y;
	a->udiv = 2.0;
	a->vdiv = 2.0;
	a->vmove = 32.0;
	a->isprojectile = 1;
	a->state = ETRAVEL;
	a->img_i = EPLASMABOLT;
	a->ms = 0.5;
	calc_target(v, &a);
	add_actor(v, &v->actors, &a);
}
	// printf("FIRE PLASMA !!x: %f, y: %d, rayhitx: %f, norm: %f,
	// targetdist: %f\n", (double)(a->target->x) + v->ray.hitx, a->target->y,
	// v->ray.hitx, norm, a->targetdist);

/// @brief Apply damages to the actor
/// @param v Vars
/// @param g Actor
void	apply_damage(t_vars *v, t_actor *g)
{
	g->hp -= v->player.currweapon.dmg / (p_random(v) % 5 + 1);
	g->animoffy = 0;
	g->img_i = EGUARDDEATH;
	if (ACTIVATE_SOUND)
	{
		if (ma_sound_is_playing(&v->sound.sound[EGUARDI]))
			ma_sound_seek_to_pcm_frame((ma_sound_stop(
						&v->sound.sound[EGUARDI]),
					&v->sound.sound[EGUARDI]), 0);
		ma_sound_start(&v->sound.sound[EGUARDI]);
	}
	if (p_random(v) >= g->painchance)
		g->timestate = timestamp_in_ms((g->state = EPAIN, v));
	if (g->hp <= 0)
	{
		if (ACTIVATE_SOUND)
		{
			ma_sound_start(&v->sound.sound[EGUARDD]);
			ma_sound_stop(&v->sound.sound[EGUARDI]);
		}
		g->hp = 0;
		g->state = EDEAD;
	}
}
