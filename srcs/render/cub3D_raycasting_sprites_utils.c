/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_raycasting_sprites_utils.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 21:30:54 by pmagnero          #+#    #+#             */
/*   Updated: 2024/10/08 19:44:27 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/// @brief Find guard in the guard array with its coordinates
/// @param v Vars
/// @param tmp Grid coordinates/datas
/// @return Index of the guard in the guard array
int	find_guard(t_vars *v, t_map *tmp)
{
	int		i;

	i = -1;
	while (++i < v->game.nb_sprites)
	{
		if (!v->ray.hitguard && v->sprites[i].isguard
			&& v->sprites[i].x == tmp->x && v->sprites[i].y == tmp->y)
		{
			v->sprites[i].hp -= v->player.currweapon.dmg;
			v->sprites[i].hit = 1;
			v->sprites[i].img_i = EGUARDDEATH;
			if (v->sprites[i].hp <= 0)
			{
				v->sprites[i].hp = 0;
				tmp->val = '0';
			}
			return (v->sprites[i].animoff = 0, i);
		}
		else if (v->ray.hitguard && v->sprites[i].isguard
			&& v->sprites[i].x == tmp->x && v->sprites[i].y == tmp->y)
			return (i);
	}
	return (-1);
}

/// @brief Check if a guard is hit
/// @param v Vars
/// @param sp Sprite variables
/// @param g Guard
/// @param x X
//printf("HIT %d, x: %f, y: %f, dist: %f\n", g->hp, g->x, g->y, g->dist);
void	hitguard(t_vars *v, t_sprite_data *sp, t_sprite *g, int x)
{
	if (v->player.attack && g->isguard && !g->hit && g->hp > 0
		&& v->screen.gamew / 2 >= x + 1
		&& v->screen.gamew / 2 <= sp->drawendx
		&& sp->transformy < v->ray.zbuffer[v->screen.gamew / 2]
		&& g->dist <= v->player.currweapon.range)
	{
		g->hp -= v->player.currweapon.dmg;
		g->hit = 1;
		g->img_i = EGUARDDEATH;
		if (g->hp <= 0)
			g->hp = 0;
		g->animoff = 0;
	}
	else if (g->isguard && !g->hit && g->hp > 0
		&& v->screen.gamew / 2 >= x + 1
		&& v->screen.gamew / 2 <= sp->drawendx
		&& sp->transformy < v->ray.zbuffer[v->screen.gamew / 2]
		&& g->dist <= v->player.currweapon.range)
		v->game.canhit = 1;
}
