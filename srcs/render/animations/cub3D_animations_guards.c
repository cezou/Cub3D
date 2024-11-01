/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_animations_guards.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:12:42 by pmagnero          #+#    #+#             */
/*   Updated: 2024/10/30 10:12:05 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3D.h"

/// @brief Update sprite animations attack range
/// @param v Vars
/// @param a Sprite to update
void	update_sprite_anim_attackr(t_vars *v, t_actor *a)
{
	int	d;

	if (a->animoffy >= v->img[a->img_i].height)
	{
		if (a->astar.open)
			clear_lst(&a->astar, &a->astar.open);
		a->justattack = 1;
		a->animoffy = 0;
		a->state = ECHASE;
		a->img_i = EGUARDW;
		a->timestate = 0;
	}
	else if (a->animoffy == v->img[a->img_i].animy)
	{
		d = a->dmg / (p_random(v) % 5 + 1);
		v->player.hit += d;
		v->game.pain = d * 5;
	}
}

/// @brief Update sprite animation pain
/// @param v Vars
/// @param a Sprite to update
void	update_sprite_anim_pain(t_vars *v, t_actor *a)
{
	a->animoffy = 0;
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
void	update_sprite_anim_death(t_vars *v, t_actor *a)
{
	if (a->animoffy >= v->img[a->img_i].height - v->img[a->img_i].animy)
	{
		a->state = EDEAD;
		a->hashitbox = 0;
		a->hp = 0;
		a->stop = 1;
		a->animoffy = v->img[a->img_i].height - v->img[a->img_i].animy;
	}
}

//	a->norm = sqrt(a->vectorx * a->vectorx + a->vectory * a->vectory);
// printf("x: %f, y: %f, x: %d, y: %d, norm: %f, vx: %f, vy: %f, pj: %d,
// pi: %d, nb_astar: %d\n", a->x, a->y, (int)round(a->x), (int)round(a->y),
// a->norm, a->vectorx, a->vectory, path->j, path->i, a->astar.nb_astar);
// printf("vx: %f, vy: %f, pj: %d, pi: %d, x: %f, y: %f\n", a->vectorx,
// a->vectory, path->j, path->i, a->x, a->y);

/// @brief Update sprite animation chase
/// @param v Vars
/// @param a Sprite to update
void	update_sprite_anim_chase(t_vars *v, t_actor *a, int i,
			t_pathfinding *path)
{
	if (a->animoffy >= v->img[a->img_i].height)
	{
		a->justattack = 0;
		a->animoffy = 0;
	}
	a->astar.target = v->player.player;
	a->astar.curr = a->map_pos;
	if (!a->astar.trace && !astar(v, &a->astar, a))
		return (a->state = EIDLE, (void)v);
	path = a->astar.trace->prev;
	if ((path->j != (int)round(a->x) || path->i != (int)round(a->y))
		&& a->dist >= 3.0)
	{
		a->angle = atan2(a->vectory, a->vectorx);
		a->x += a->ms * a->vectorx;
		a->y += a->ms * a->vectory;
	}
	if (!path || !a->astar.nb_astar
		|| (int)round(a->x) != path->j || (int)round(a->y) != path->i)
		return ;
	del_node((a->map_pos = path->curr, &a->astar), &i, &a->astar.trace, &path);
	a->vectorx = a->astar.trace->prev->j - a->x;
	a->vectory = a->astar.trace->prev->i - a->y;
	if (!a->astar.nb_astar)
		a->astar.trace = NULL;
}

// path = tmp->astar.trace->prev;
// while (++i < tmp->astar.nb_astar && tmp->astar.trace)
// {
// 	ft_printf(1, "-> (%d,%d)\n", path->i, path->j);
// 	path = path->prev;
// }
// tmp->angle = sqrt(((double)(path->j) - tmp->y) * ((double)(path->j) - tmp->y)
// 		+ ((double)(path->i) - tmp->x) * ((double)(path->i) - tmp->x));

/// @brief Update guards movement/animations
/// @param v Vars
///	@param actor Actor guard
void	update_guards(t_vars *v, t_actor **actor)
{
	t_actor (*tmp) = *actor;
	if (!tmp->isguard)
		return ;
	if (tmp->state != EIDLE && !tmp->stop)
		tmp->animoffy += v->img[tmp->img_i].animy;
	tmp->time = timestamp_in_ms(v);
	if (tmp->state == EDEAD)
		update_sprite_anim_death(v, tmp);
	else if (tmp->state == EPAIN)
		update_sprite_anim_pain(v, tmp);
	else if (tmp->state == EATTACKR)
		update_sprite_anim_attackr(v, tmp);
	else if (tmp->state == ECHASE)
		update_sprite_anim_chase(v, tmp, -1, NULL);
	calc_angle(v, tmp);
}
