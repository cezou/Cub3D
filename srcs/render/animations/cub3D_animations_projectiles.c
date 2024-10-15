/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_animations_projectiles.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:12:42 by pmagnero          #+#    #+#             */
/*   Updated: 2024/10/15 20:11:49 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3D.h"

/// @brief Update projectiles movement/animations
/// @param v Vars
///	@param actor Actor projectile
/// @param i Actor id
// printf("Projectile x: %f, y: %f, targetdist: %f, norm: %f\n", tmp->x, tmp->y,
// tmp->targetdist, tmp->norm);
int	update_projectiles(t_vars *v, t_actor **actor, int i)
{
	t_actor	*tmp;
	t_actor	*del;

	tmp = *actor;
	if (!tmp->isprojectile)
		return (i);
	tmp->animoff += v->img[tmp->img_i].animx;
	if (tmp->state == ETRAVEL)
	{
		if (tmp->animoff >= v->img[tmp->img_i].animx * 2)
			tmp->animoff = 0;
		tmp->x += tmp->ms * v->game.frametime * tmp->vectorx;
		tmp->y += tmp->ms * v->game.frametime * tmp->vectory;
		tmp->targetdist -= tmp->norm;
		if (tmp->targetdist <= 1.5)
			tmp->state = EHIT;
	}
	else if (tmp->state == EHIT && tmp->animoff >= v->img[tmp->img_i].width)
	{
		tmp->next->prev = tmp->prev;
		tmp->prev->next = tmp->next;
		if (tmp && tmp != v->actors)
			free((tmp->active = 0, del = tmp, i--, v->game.nb_actors--, del));
	}
	return (i);
}
