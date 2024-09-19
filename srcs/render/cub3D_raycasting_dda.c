/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_raycasting_dda.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:58:10 by pmagnero          #+#    #+#             */
/*   Updated: 2024/09/19 16:57:10 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

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

int	hashit(t_vars *v, int x, int y, int d)
{
	t_map	*tmp;

	tmp = v->mapv.map;
	while (tmp)
	{
		// if (tmp->x == x && tmp->y == y && (tmp->val == 'D'))
		// {
		// 	v->ray.hit = tmp;
		// 	return (1);
		// }
		if (tmp->x == x && tmp->y == y && (tmp->val == '1' || (d && tmp->val == 'D')))
		{
			v->ray.hit = tmp;
			return (1);
		}
		tmp = tmp->right;
	}
	return (0);
}

void	perform_dda(t_vars *v, int d)
{
	int		hit;
	double	dist;

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
	if (v->ray.hit->val == 'D')
		v->ray.img = v->img[EDOOR];
	else
		v->ray.img = v->img[ESPACE];
	// v->ray.img = loadtexture(v);
	// if(texNum == 8)
	// 	door = findDoor(mapX, mapY); /* Door encountered */
	if (v->ray.img.id == EDOOR)
	{
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
	else
	{
		if (v->ray.side == 0)
			v->ray.wall_dist = (v->ray.sidedist_x - v->ray.deltadist_x);
		else
			v->ray.wall_dist = (v->ray.sidedist_y - v->ray.deltadist_y);
	}
}

// int	hashit(t_vars *v, int x, int y)
// {
// 	t_map	*tmp;

// 	tmp = v->mapv.map;
// 	while (tmp)
// 	{
// 		if (tmp->x == x && tmp->y == y && tmp->val == '1')
// 		{
// 			// v->player.x = x;
// 			// v->player.y = y;
// 			// v->player.player = tmp;
// 			// break ;
// 			return (1);
// 		}
// 		tmp = tmp->right;
// 	}
// 	return (0);
// }

// void	perform_dda(t_vars *v)
// {
// 	int		hit;
// 	// t_map	*tmp;

// 	// tmp = v->player.player;
// 	hit = 0;
// 	while (hit == 0)
// 	{
// 		if (v->ray.sidedist_x < v->ray.sidedist_y)
// 		{
// 			v->ray.sidedist_x += v->ray.deltadist_x;
// 			// if (v->ray.step_x > 0)
// 			// 	tmp = tmp->right;
// 			// else
// 			// 	tmp = tmp->left;
// 			v->ray.map_x += v->ray.step_x;
// 			v->ray.side = 0;
// 		}
// 		else
// 		{
// 			v->ray.sidedist_y += v->ray.deltadist_y;
// 			// if (v->ray.step_y > 0)
// 			// 	tmp = tmp->down;
// 			// else
// 			// 	tmp = tmp->up;
// 			v->ray.map_y += v->ray.step_y;
// 			v->ray.side = 1;
// 		}
// 		// if (tmp->val == '1')
// 			// hit = 1;
// 		hit = hashit(v, v->ray.map_x, v->ray.map_y);
// 	}
// }
