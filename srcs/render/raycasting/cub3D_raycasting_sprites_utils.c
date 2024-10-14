/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_raycasting_sprites_utils.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 21:30:54 by pmagnero          #+#    #+#             */
/*   Updated: 2024/10/14 15:24:18 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3D.h"

// /// @brief Find guard in the guard array with its coordinates
// /// @param v Vars
// /// @param tmp Grid coordinates/datas
// /// @return Index of the guard in the guard array
// int	find_guard(t_vars *v, t_map *tmp)
// {
// 	int		i;

// 	i = -1;
// 	(void)tmp;
// 	while (++i < v->game.nb_actors)
// 	{
// 		// if (!v->ray.hitguard && v->sprites[i].isguard
// 		// 	&& v->sprites[i].x == tmp->x && v->sprites[i].y == tmp->y)
// 		// {
// 		// 	v->sprites[i].hp -= v->player.currweapon.dmg
// 		// 		/ (p_random(v) % 3 + 1);
// 		// 	v->sprites[i].img_i = EGUARDDEATH;
// 		// 	v->sprites[i].state = EDEAD;
// 		// 	if (v->sprites[i].hp <= 0)
// 		// 	{
// 		// 		v->sprites[i].hp = 0;
// 		// 		tmp->val = '0';
// 		// 	}
// 		// 	return (v->sprites[i].animoff = 0, i);
// 		// }
// 		// else if (v->ray.hitguard && v->sprites[i].isguard
// 		// 	&& v->sprites[i].x == tmp->x && v->sprites[i].y == tmp->y)
// 		// 	return (i);
// 	}
// 	return (-1);
// }

/// @brief 
/// @param v 
/// @param sp 
/// @param g 
void	guardattack(t_vars *v, t_sprite_data *sp, t_actor *g)
{
	if (!g->isguard || g->hp <= 0
		|| sp->transformy <= 0
		|| sp->drawstartx <= 0 || sp->drawstartx >= v->screen.resw
		|| sp->transformy > v->ray.zbuffer[sp->drawstartx])
		return ;
	if (g->hasrange && !g->justattack && g->dist > 15 && g->state == ECHASE)
	{
		g->img_i = EGUARDATTR;
		g->state = EATTACKR;
	}
}

/// @brief Check if a guard is hit
/// @param v Vars
/// @param sp Sprite variables
/// @param g Guard
/// @param x X
// printf("HIT %d, x: %f, y: %f, dist: %f, state: %d\n", g->hp, g->x, g->y,
// 	g->dist, g->state);
void	hitguard(t_vars *v, t_sprite_data *sp, t_actor *g)
{
	if (!g->isguard || g->hp <= 0 || g->state == EDEAD || g->state == EPAIN
		|| sp->transformy <= 0)
		return ;
	if (sp->drawstartx > 0 && g->dist < 50 && sp->drawstartx < v->screen.resw
		&& sp->transformy < v->ray.zbuffer[sp->drawstartx])
	{
		g->img_i = EGUARDW;
		g->state = ECHASE;
	}
	if (v->screen.gamew / 2 < sp->drawstartx
		|| v->screen.gamew / 2 > sp->drawendx
		|| v->screen.gameh / 2 < sp->drawstarty
		|| v->screen.gameh / 2 > sp->drawendy
		|| sp->transformy > v->ray.zbuffer[v->screen.gamew / 2])
		return ;
	if (v->player.attack && g->dist <= v->player.currweapon.range
		&& g->state != EDEAD)
	{
		g->hp -= v->player.currweapon.dmg / (p_random(v) % 5 + 1);
		g->animoff = 0;
		g->img_i = EGUARDDEATH;
		if (p_random(v) >= g->painchance)
		{
			g->state = EPAIN;
			g->timestate = timestamp_in_ms(v);
		}
		if (g->hp <= 0)
		{
			g->hp = 0;
			g->state = EDEAD;
		}
	}
	else if (g->dist <= v->player.currweapon.range)
		v->game.canhit = 1;
}
