/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_movements_guards.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 18:24:52 by pmagnero          #+#    #+#             */
/*   Updated: 2024/10/22 15:56:11 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/// @brief Check if an actor can move to its next position
/// @param v Vars
/// @param p New position
/// @param tmp Actor list
/// @param actor Actor to to skip in the list
/// @return true/false
bool	can_move_guards(t_vars *v, t_point2 p, t_actor *tmp, t_actor *actor)
{
	double	d;

	tmp = v->actors;
	while (++p.z < v->game.nb_actors)
	{
		if (!tmp->hashitbox || !tmp->active || tmp->isprojectile
			|| tmp == actor)
		{
			tmp = tmp->next;
			continue ;
		}
		d = pow((p.x - tmp->x), 2) + pow((p.y - tmp->y), 2);
		if (d < 0.20)
		{
			// if (((actor && actor->isguard)) && tmp->pickable)
			// 	touch_thing((tmp->active = 0, v), tmp);
			// else if ((actor && actor->isprojectile)
			// 	&& v->player.currweapon.isprojectile && tmp->hp > 0
			// 	&& tmp->dist <= v->player.currweapon.range)
			// 	apply_damage(v, tmp);
			return (false);
		}
		tmp = tmp->next;
	}
	return (true);
}

/// @brief Helper function to check if a given map position is valid
/// @param v Vars
/// @param pos Map square position to check
/// @param p
/// @return 1 is valid, 0 not valid
//  && pos->x < p.x && pos->y < p.y
static bool	is_valid_pos(t_vars *v, t_map *pos, t_point2 p, t_actor *a)
{
	int	i;
	int	o;

	o = 0;
	// if (pos->val == 'D')
	// {
	// 	i = v->game.nb_door;
	// 	while (--i >= 0)
	// 	{
	// 		if (!d && v->door[i].x == pos->x && v->door[i].y == pos->y
	// 			&& v->door[i].state == EOPEN)
	// 		{
	// 			o = 1;
	// 			break ;
	// 		}
	// 		else if (d && v->door[i].state == ECLOSE && v->door[i].x == p.z
	// 			&& p.z == pos->x && v->door[i].y == p.t
	// 			&& p.t == pos->y)
	// 			return (1);
	// 	}
	// }
	// else if (pos->val != '1')
	if (pos->val != '1')
		o = 1;
	return (o && can_move_guards(v, (t_point2){p.x, p.y, -1, 0}, NULL, a)
		&& pos->x == p.z && pos->y == p.t && pos->x >= 0 && pos->y >= 0);
}

/// @brief Function to update the player's position
/// @param actor Vars
/// @param pos Map square position
/// @param k New position coordinates
static t_map	*update_guards_pos(t_vars *v, t_map *pos, t_point2 k, t_actor *a)
{
	// if (d)
	// 	return (pos);
	a->x = k.x;
	a->y = k.y;
	return (pos);
}

/// @brief Function to set the current player position in the map
/// @param v Vars
/// @param k New position coordinates to check
/// @param m Player position map
/// @param a Actor
// /// @param d door boolean, can only open doors if the door is in front
/// of the player
t_map	*set_pos_guards(t_vars *v, t_point2 k, t_map *m, t_actor *a)
{
	if (is_valid_pos(v, m, k, a))
		return (update_guards_pos(v, m, k, a));
	else if (is_valid_pos(v, m->up, k, a))
		return (update_guards_pos(v, m->up, k, a));
	else if (is_valid_pos(v, m->up->left, k, a) && m->up->val != '1'
		&& m->left->val != '1')
		return (update_guards_pos(v, m->up->left, k, a));
	else if (is_valid_pos(v, m->up->right, k, a) && m->up->val != '1'
		&& m->right->val != '1')
		return (update_guards_pos(v, m->up->right, k, a));
	else if (is_valid_pos(v, m->down, k, a))
		return (update_guards_pos(v, m->down, k, a));
	else if (is_valid_pos(v, m->down->left, k, a) && m->down->val != '1'
		&& m->left->val != '1')
		return (update_guards_pos(v, m->down->left, k, a));
	else if (is_valid_pos(v, m->down->right, k, a) && m->down->val != '1'
		&& m->right->val != '1')
		return (update_guards_pos(v, m->down->right, k, a));
	else if (is_valid_pos(v, m->left, k, a))
		return (update_guards_pos(v, m->left, k, a));
	else if (is_valid_pos(v, m->right, k, a))
		return (update_guards_pos(v, m->right, k, a));
	return (m);
}
