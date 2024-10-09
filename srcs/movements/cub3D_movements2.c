/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_movements2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 18:24:52 by pmagnero          #+#    #+#             */
/*   Updated: 2024/10/09 18:55:49 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/// @brief Helper function to check if a given map position is valid
/// @param v Vars
/// @param pos Map square position to check
/// @param p 
/// @return 1 is valid, 0 not valid
//  && pos->x < p.x && pos->y < p.y
static bool	is_valid_pos(t_vars *v, t_map *pos, t_point2 p, int d)
{
	int	i;
	int	o;

	o = 0;
	if (pos->val == 'D')
	{
		i = v->game.nb_door;
		while (--i >= 0)
		{
			if (!d && v->door[i].x == pos->x && v->door[i].y == pos->y
				&& v->door[i].state == EOPEN)
			{
				o = 1;
				break ;
			}
			else if (d && v->door[i].state == ECLOSE && v->door[i].x == p.z
				&& p.z == pos->x && v->door[i].y == p.t
				&& p.t == pos->y)
				return (1);
		}
	}
	else if (pos->val != '1')
		o = 1;
	return (o && pos->x == p.z && pos->y == p.t && pos->x >= 0 && pos->y >= 0);
}

/// @brief Function to update the player's position
/// @param v Vars
/// @param pos Map square position
/// @param k New position coordinates
static t_map	*update_player_pos(t_vars *v, t_map *pos, t_point2 k, int d)
{
	if (d)
		return (pos);
	v->player.x = k.x;
	v->player.y = k.y;
	return (pos);
}

/// @brief Function to set the current player position in the map
/// @param v Vars
/// @param k New position coordinates to check
/// @param m Player position map
/// @param d door boolean, can only open doors if the door is in front
/// of the player
t_map	*set_pos(t_vars *v, t_point2 k, t_map *m, int d)
{
	if (is_valid_pos(v, m, k, d))
		return (update_player_pos(v, m, k, d));
	else if (is_valid_pos(v, m->up, k, d))
		return (update_player_pos(v, m->up, k, d));
	else if (!d && is_valid_pos(v, m->up->left, k, d) && m->up->val != '1'
		&& m->left->val != '1')
		return (update_player_pos(v, m->up->left, k, d));
	else if (!d && is_valid_pos(v, m->up->right, k, d) && m->up->val != '1'
		&& m->right->val != '1')
		return (update_player_pos(v, m->up->right, k, d));
	else if (is_valid_pos(v, m->down, k, d))
		return (update_player_pos(v, m->down, k, d));
	else if (!d && is_valid_pos(v, m->down->left, k, d) && m->down->val != '1'
		&& m->left->val != '1')
		return (update_player_pos(v, m->down->left, k, d));
	else if (!d && is_valid_pos(v, m->down->right, k, d) && m->down->val != '1'
		&& m->right->val != '1')
		return (update_player_pos(v, m->down->right, k, d));
	else if (is_valid_pos(v, m->left, k, d))
		return (update_player_pos(v, m->left, k, d));
	else if (is_valid_pos(v, m->right, k, d))
		return (update_player_pos(v, m->right, k, d));
	return (v->player.player);
}

/// @brief Set the door state to opening of the door around the player
/// @param v Vars
void	open_door(t_vars *v)
{
	int		i;
	t_map	*pd;

	if (v->keys[XK_space])
	{
		pd = set_pos(v, (t_point2){0, 0,
				(int)(v->player.x + v->player.dir_x),
				(int)(v->player.y + v->player.dir_y)}, v->player.player, 1);
		i = find_door(v, pd->x, pd->y);
		if (i < 0)
			return ;
		if (v->door[i].state == ECLOSE)
			v->door[i].state = EOPENING;
	}
}
