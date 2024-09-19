/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_movements2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 18:24:52 by pmagnero          #+#    #+#             */
/*   Updated: 2024/09/18 16:11:20 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

// Helper function to check if a given map position is valid
static bool	is_valid_pos(t_vars *v, t_map *pos, t_point p)
{
	int	i;
	int	o;

	o = 0;
	if (pos->val == 'D')
	{
		i = v->door.nb;
		while (--i >= 0)
		{
			if (v->door.d[i].x == pos->x && v->door.d[i].y == pos->y
				&& v->door.d[i].color == EOPEN)
			{
				o = 1;
				break ;
			}
		}
	}
	else if (pos->val != '1')
		o = 1;
	return (o && pos->x == p.z && pos->y == p.color
		&& pos->x >= 0 && pos->y >= 0 && pos->x < p.x && pos->y < p.y);
}

// Function to update the player's position
static void	update_player_position(t_vars *v, t_map *pos, t_point2 k)
{
	v->player.x = k.x;
	v->player.y = k.y;
	v->player.player = pos;
}

// Function to set the current player position in the map
void	set_pos(t_vars *v, t_point2 k)
{
	t_map	*m;
	t_point	p;

	m = v->player.player;
	p = (t_point){v->mapv.mapw, v->mapv.maph, k.z, k.t};
	if (is_valid_pos(v, m, p))
		update_player_position(v, m, k);
	else if (is_valid_pos(v, m->up, p))
		update_player_position(v, m->up, k);
	else if (is_valid_pos(v, m->up->left, p))
		update_player_position(v, m->up->left, k);
	else if (is_valid_pos(v, m->up->right, p))
		update_player_position(v, m->up->right, k);
	else if (is_valid_pos(v, m->down, p))
		update_player_position(v, m->down, k);
	else if (is_valid_pos(v, m->down->left, p))
		update_player_position(v, m->down->left, k);
	else if (is_valid_pos(v, m->down->right, p))
		update_player_position(v, m->down->right, k);
	else if (is_valid_pos(v, m->left, p))
		update_player_position(v, m->left, k);
	else if (is_valid_pos(v, m->right, p))
		update_player_position(v, m->right, k);
}
