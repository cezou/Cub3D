/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_raycasting_dda.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:58:10 by pmagnero          #+#    #+#             */
/*   Updated: 2024/09/22 22:31:55 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/// @brief Set DDA (Digital Differential Analysis) datas
/// @param v Vars
void	set_dda(t_vars *v)
{
	if (v->ray.dir_x < 0)
	{
		v->ray.step_x = -1;
		v->ray.sidedist_x = (v->player.x - v->ray.map_x) * v->ray.deltadist_x;
	}
	else
	{
		v->ray.step_x = 1;
		v->ray.sidedist_x = (v->ray.map_x + 1.0 - v->player.x)
			* v->ray.deltadist_x;
	}
	if (v->ray.dir_y < 0)
	{
		v->ray.step_y = -1;
		v->ray.sidedist_y = (v->player.y - v->ray.map_y) * v->ray.deltadist_y;
	}
	else
	{
		v->ray.step_y = 1;
		v->ray.sidedist_y = (v->ray.map_y + 1.0 - v->player.y)
			* v->ray.deltadist_y;
	}
}

/// @brief Check if the ray at x,y position hit a wall or a door
/// @param v Vars
/// @param x X coordinate
/// @param y Y coordinate
/// @param d 
/// @return 0 did not hit a wall/door, 1 hit a wall/door
int	hashit(t_vars *v, int x, int y, int d)
{
	t_map	*tmp;
	int		i;

	i = -1;
	tmp = v->mapv.map;
	while (tmp)
	{
		if (tmp->x == x && tmp->y == y
			&& (tmp->val == '1' || (d && tmp->val == 'D')))
		{
			if (tmp->val == 'D')
			{
				i = find_door(v, tmp->x, tmp->y);
				if (i < 0)
					return ((v->ray.img = v->img[ESPACE], 0));
				v->ray.img = v->img[v->door[i].img_i];
				v->ray.door = v->door[i];
			}
			else
				v->ray.img = v->img[ESPACE];
			return (v->ray.hit = tmp, 1);
		}
		tmp = tmp->right;
	}
	return (0);
}

/// @brief If the ray hit a door then we need to extend the ray until it hit
///	a wall so the if the door is open or opening we can render what is behind it
/// @param v Vars
static void	check_door(t_vars *v)
{
	double	dist;

	if (v->ray.side == 0)
	{
		dist = v->ray.sidedist_x - v->ray.deltadist_x * 0.5;
		if (v->ray.sidedist_y < dist)
		{
			v->ray.hit = NULL;
			perform_dda(v, 1);
			return ;
		}
		v->ray.wall_dist = dist;
	}
	else
	{
		dist = v->ray.sidedist_y - v->ray.deltadist_y * 0.5;
		if (v->ray.sidedist_x < dist)
		{
			v->ray.hit = NULL;
			perform_dda(v, 1);
			return ;
		}
		v->ray.wall_dist = dist;
	}
}

/// @brief Perform the DDA (Digital Differential Analysis) to get
///	the square position in the map from the coordinates of the line
/// @param v Vars
/// @param d 
void	perform_dda(t_vars *v, int d)
{
	int		hit;

	hit = 0;
	while (hit == 0)
	{
		if (v->ray.sidedist_x < v->ray.sidedist_y)
		{
			v->ray.sidedist_x += v->ray.deltadist_x;
			v->ray.map_x += v->ray.step_x;
			v->ray.side = 0;
		}
		else
		{
			v->ray.sidedist_y += v->ray.deltadist_y;
			v->ray.map_y += v->ray.step_y;
			v->ray.side = 1;
		}
		hit = hashit(v, v->ray.map_x, v->ray.map_y, d);
	}
	if (v->ray.side == 0)
		v->ray.wall_dist = (v->ray.sidedist_x - v->ray.deltadist_x);
	else
		v->ray.wall_dist = (v->ray.sidedist_y - v->ray.deltadist_y);
	if (v->ray.img.id == EDOOR)
		check_door(v);
}
