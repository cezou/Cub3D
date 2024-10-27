/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_animations_actors.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:12:42 by pmagnero          #+#    #+#             */
/*   Updated: 2024/10/27 19:59:39 by pmagnero         ###   ########.fr       */
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
	tmp = v->actors;
	while (++i < v->game.nb_actors)
	{
		if (!tmp->active)
		{
			tmp = tmp->next;
			continue ;
		}
		if (timestamp_in_ms(v) - tmp->time
			< (uint64_t)(100))
			return ;
		tmp->time = timestamp_in_ms(v);
		if (!tmp->isguard && !tmp->isguard)
		{
			tmp->animoffx += v->img[tmp->img_i].animx;
			if (tmp->animoffx >= v->img[tmp->img_i].width)
				tmp->animoffx = 0;
		}
		update_guards(v, &tmp);
		tmp = update_projectiles(v, &tmp, &i);
	}
}
