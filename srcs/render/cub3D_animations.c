/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_animations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:12:42 by pmagnero          #+#    #+#             */
/*   Updated: 2024/09/22 22:26:33 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/// @brief Update doors animation
/// @param v Vars
/// @param i Incremental variable =-1
void	update_door_animations(t_vars *v, int i)
{
	while (++i < v->game.nb_door)
	{
		if (v->door[i].state == EOPENING
			&& timestamp_in_ms(v) - v->door[i].time
			>= (uint64_t)(5000 / v->game.fps))
		{
			v->door[i].xdelta -= 3;
			v->door[i].time = timestamp_in_ms(v);
		}
		else if (v->door[i].state == ECLOSING
			&& timestamp_in_ms(v) - v->door[i].time
			>= (uint64_t)(5000 / v->game.fps))
		{
			v->door[i].xdelta += 3;
			v->door[i].time = timestamp_in_ms(v);
		}
		if (v->door[i].state == EOPENING
			&& v->door[i].xdelta <= 0)
			v->door[i].state = EOPEN;
		else if (v->door[i].state == ECLOSING
			&& v->door[i].xdelta >= v->img[v->door[i].img_i].width)
			v->door[i].state = ECLOSE;
	}
}

void	update_sprites_animations(t_vars *v)
{
	int	i;

	i = -1;
	while (++i < v->game.nb_guard)
	{
		if (timestamp_in_ms(v) - v->guard[i].time
			>= (uint64_t)(10000 / v->game.fps))
		{
			v->guard[i].animoff += v->img[v->guard[i].img_i].height;
			v->guard[i].time = timestamp_in_ms(v);
		}
		if (v->guard[i].animoff > v->img[v->guard[i].img_i].width)
			v->guard[i].animoff = 0;
	}
}

void	update_animations(t_vars *v)
{
	update_sprites_animations(v);
	update_door_animations(v, -1);
}
