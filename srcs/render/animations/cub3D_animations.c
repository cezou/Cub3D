/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_animations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:12:42 by pmagnero          #+#    #+#             */
/*   Updated: 2024/10/14 15:59:54 by pmagnero         ###   ########.fr       */
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
	t_actor	*head;
	t_actor	*tmp;
	int		i;

	i = -1;
	head = v->actors;
	tmp = v->actors->next;
	while (++i < v->game.nb_actors)// TODO Fuse with update_sprites_animations() to optimize
	{
		if (!tmp->isguard)
		{
			tmp = tmp->next;
			continue ;
		}
		if (timestamp_in_ms(v) - tmp->timem
			>= (uint64_t)(5000 / v->game.fps))
		{
			tmp->timem = timestamp_in_ms(v);
			if (tmp->state == ECHASE)
			{
				tmp->x = tmp->x + tmp->ms
					* v->game.frametime * (v->player.x + 0.5 - tmp->x);
				tmp->y = tmp->y + tmp->ms
					* v->game.frametime * (v->player.y + 0.5 - tmp->y);
			}
		}
		tmp = tmp->next;
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
