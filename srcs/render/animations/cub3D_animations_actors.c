/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_animations_actors.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:12:42 by pmagnero          #+#    #+#             */
/*   Updated: 2024/10/15 19:36:32 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3D.h"

// if (v->sprites[i].state != EIDLE && v->sprites[i].state != EDEAD
// 	&& v->sprites[i].state != ECHASE && v->sprites[i].state != EATTACKR
// 	&& v->sprites[i].animoff >= v->img[v->sprites[i].img_i].width)
// 	v->sprites[i].animoff = 0;

/// @brief Update actors movement/animations
/// @param v Vars
void	update_actors(t_vars *v)
{
	t_actor	*tmp;
	int		i;

	i = -1;	
	tmp = v->actors->next;
	while (++i < v->game.nb_actors)
	{
		if (!tmp->active)//|| (!tmp->isguard && !tmp->isprojectile)
		{
			tmp = tmp->next;
			continue ;
		}
		if (timestamp_in_ms(v) - tmp->time
			< (uint64_t)(30000 / v->game.fps))
			return ;
		tmp->time = timestamp_in_ms(v);
		update_guards(v, &tmp);
		i = update_projectiles(v, &tmp, i);
		tmp = tmp->next;
	}
}
