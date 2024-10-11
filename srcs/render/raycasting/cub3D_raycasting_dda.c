/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_raycasting_dda.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:58:10 by pmagnero          #+#    #+#             */
/*   Updated: 2024/10/11 16:29:52 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3D.h"

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
int	hashit(t_vars *v, t_map *tmp, int i)
{
	if ((tmp->val == '1' || (tmp->val == 'D')))
	{
		if (tmp->val == 'D')
		{
			i = find_door(v, tmp->x, tmp->y);
			if (i < 0)
			{
				v->ray.img = v->img[ESPACE];
				return (0);
			}
			v->ray.img = v->img[v->door[i].img_i];
			v->ray.door = v->door[i];
		}
		else
			v->ray.img = v->img[ESPACE];
		v->ray.hit = tmp;
		return (1);
	}
	return (0);
}

/// @brief If the ray hit a door then we need to extend the ray until it hit
///	a wall so if the door is open or opening we can render what is behind it
/// @param v Vars
void	check_door(t_vars *v)
{
	double	dist;

	if (v->ray.side == 0)
	{
		dist = v->ray.sidedist_x - v->ray.deltadist_x * 0.5;
		if (v->ray.sidedist_y < dist)
		{
			perform_dda(v, v->ray.hit, 0);
			return ;
		}
		v->ray.wall_dist = dist;
	}
	else
	{
		dist = v->ray.sidedist_y - v->ray.deltadist_y * 0.5;
		if (v->ray.sidedist_x < dist)
		{
			perform_dda(v, v->ray.hit, 0);
			return ;
		}
		v->ray.wall_dist = dist;
	}
}

/// @brief Extend ray to hit what it is behind the door
/// @param v Vars
/// @param p Pixels informations
/// @param texx Texture x coordinate
/// @return Texture x coordinate
int	door_extend_ray(t_vars *v, t_point p, int *t)
{
	v->tmp[0] = v->ray.img;
	v->ray.lim = ((v->tmp[0].height - 1) * v->tmp[0].len) + ((v->tmp[0].width
				- 1) * 4);
	if (v->ray.hit->val == 'D')
	{
		t[0] -= v->ray.img.width - v->ray.door.xdelta;
		if (t[0] < 0)
		{
			perform_dda(v, v->ray.hit, 0);
			calculate_line_height(v);
			update_texture_pixels(v, p, t);
			return (-1);
		}
	}
	return (t[0]);
}

/// @brief Perform the DDA (Digital Differential Analysis) to get
///	the square position in the map from the coordinates of the line
/// @param v Vars
/// @param tmp Start position from where to begin the raycasting
/// @param hit Boolean to end the loop =0
void	perform_dda(t_vars *v, t_map *tmp, int hit)
{
	while (hit == 0)
	{
		if (v->ray.sidedist_x < v->ray.sidedist_y)
		{
			v->ray.sidedist_x += v->ray.deltadist_x;
			if (v->ray.step_x > 0)
				tmp = tmp->right;
			else
				tmp = tmp->left;
			v->ray.side = 0;
		}
		else
		{
			v->ray.sidedist_y += v->ray.deltadist_y;
			if (v->ray.step_y > 0)
				tmp = tmp->down;
			else
				tmp = tmp->up;
			v->ray.side = 1;
		}
		hit = hashit(v, tmp, -1);
	}
	dda_utils(v);
}
