/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_animations_projectiles.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:12:42 by pmagnero          #+#    #+#             */
/*   Updated: 2024/10/29 17:55:36 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3D.h"

void	update_travel(t_vars *v, t_actor *tmp)
{
	if (tmp->animoffx >= v->img[tmp->img_i].animx * 2)
		tmp->animoffx = 0;
	tmp->x += tmp->ms * tmp->vectorx;
	tmp->y += tmp->ms * tmp->vectory;
	tmp->targetdist -= tmp->norm;
	if (tmp->targetdist <= 1.0f || tmp->dist > 200 - 1
		|| !can_move(v, (t_point2){tmp->x, tmp->y, -1, 0}, NULL, tmp))
		tmp->state = EHIT;
}

/// @brief Update projectiles movement/animations
/// @param v Vars
///	@param actor Actor projectile
/// @param i Actor id
// printf("Projectile x: %f, y: %f, targetdist: %f, norm: %f\n", tmp->x, tmp->y,
// tmp->targetdist, tmp->norm);
t_actor	*update_projectiles(t_vars *v, t_actor **actor, int *i)
{
	t_actor	*tmp;
	t_actor	*del;
	t_actor	*next;

	tmp = *actor;
	next = tmp->next;
	if (!tmp->isprojectile)
		return (next);
	tmp->animoffx += v->img[tmp->img_i].animx;
	if (tmp->state == ETRAVEL)
		update_travel(v, tmp);
	else if (tmp->state == EHIT && tmp->animoffx >= v->img[tmp->img_i].width)
	{
		del = tmp;
		if (!v->actors || !del)
			return (next);
		del->active = 0;
		if (v->actors == del)
			v->actors = del->next;
		del->next->prev = del->prev;
		del->prev->next = del->next;
		free(((*i)--, v->game.nb_actors--, del));
	}
	return (next);
}
