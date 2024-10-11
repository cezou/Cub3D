/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_animations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:12:42 by pmagnero          #+#    #+#             */
/*   Updated: 2024/10/11 16:28:46 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3D.h"

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
// printf("%lu | %lu | %lu\n", v->sprites[i].time, v->sprites[i].timestate,
// 	timestamp_in_ms(v));
// printf("Guard: %d, x: %f, y: %f\n", i, v->sprites[i].x, v->sprites[i].y);

/// @brief 
/// @param v 
void	update_guard_movement(t_vars *v)
{
	int	i;

	i = -1;
	while (++i < v->game.nb_sprites)
	{
		if (!v->sprites[i].isguard)
			continue ;
		if (timestamp_in_ms(v) - v->sprites[i].timem
			>= (uint64_t)(5000 / v->game.fps))
		{
			v->sprites[i].timem = timestamp_in_ms(v);
			if (v->sprites[i].state == ECHASE)
			{
				v->sprites[i].x = v->sprites[i].x + v->sprites[i].ms
					* v->game.frametime * (v->player.x + 0.5 - v->sprites[i].x);
				v->sprites[i].y = v->sprites[i].y + v->sprites[i].ms
					* v->game.frametime * (v->player.y + 0.5 - v->sprites[i].y);
			}
		}
	}
}

/// @brief Update animations
/// @param v Vars
void	update_animations(t_vars *v)
{
	if (v->game.pause)
		return ;
	update_sprites_animations(v);
	update_door_animations(v, -1);
	update_player(v);
	update_guard_movement(v);
}
