/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_raycasting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 21:30:54 by pmagnero          #+#    #+#             */
/*   Updated: 2024/09/10 11:04:55 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void	init_raycasting_info(int x, t_ray *ray, t_vars *v)
{
	// init_ray(ray);
	// printf("player pos: %f %f", v->player.dir_x, v->player.dir_y);
	ray->camera_x = 2 * x / (double)v->screen.resw - 1;
	ray->dir_x = v->player.dir_x + v->player.plane_x * ray->camera_x;
	ray->dir_y = v->player.dir_y + v->player.plane_y * ray->camera_x;
	ray->map_x = v->player.x + 0.5;
	ray->map_y = v->player.y + 0.5;
	ray->deltadist_x = fabs(1 / ray->dir_x);
	ray->deltadist_y = fabs(1 / ray->dir_y);
	ray->pitch = 100;
}

static void	set_dda(t_ray *ray, t_vars *v)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->sidedist_x = (v->player.x + 0.5 - ray->map_x) * ray->deltadist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedist_x = (ray->map_x + 1.0 - v->player.x + 0.5) * ray->deltadist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (v->player.y + 0.5 - ray->map_y) * ray->deltadist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y = (ray->map_y + 1.0 - v->player.y + 0.5) * ray->deltadist_y;
	}
}

static void	perform_dda(t_vars *v, t_ray *ray)
{
	int		hit;
	t_map	*tmp;

	tmp = v->player.player;
	hit = 0;
	while (hit == 0)
	{
		if (ray->sidedist_x < ray->sidedist_y)
		{
			ray->sidedist_x += ray->deltadist_x;
			if (ray->step_x > 0)
				tmp = tmp->right;
			else
				tmp = tmp->left;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->sidedist_y += ray->deltadist_y;
			if (ray->step_y > 0)
				tmp = tmp->up;
			else
				tmp = tmp->down;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (tmp->val == '1')
			hit = 1;
	}
}

static void	calculate_line_height(t_ray *ray, t_vars *v)
{
	if (ray->side == 0)
		ray->wall_dist = (ray->sidedist_x - ray->deltadist_x);
	else
		ray->wall_dist = (ray->sidedist_y - ray->deltadist_y);
	ray->line_height = (int)(v->screen.resh / ray->wall_dist);
	ray->draw_start = -(ray->line_height) / 2 + v->screen.resh / 2 + ray->pitch;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + v->screen.resh / 2 + ray->pitch;
	if (ray->draw_end > v->screen.resh)
		ray->draw_end = v->screen.resh - 1;
	if (ray->side == 0)
		ray->wall_x = v->player.y + ray->wall_dist * ray->dir_y;
	else
		ray->wall_x = v->player.x + ray->wall_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
}

// static void	get_texture_index(t_vars *v)
// {
// 	if (v->ray.side == 0)
// 	{
// 		if (v->ray.dir_x < 0)
// 			v->texinfo.index = WEST;
// 		else
// 			v->texinfo.index = EAST;
// 	}
// 	else
// 	{
// 		if (v->ray.dir_y > 0)
// 			v->texinfo.index = SOUTH;
// 		else
// 			v->texinfo.index = NORTH;
// 	}
// }


void	update_texture_pixels(t_vars *v, t_ray *ray, int x)
{
	int			y;
	uint32_t	color;
	int			texx;
	int			texy;
	double		step;
	double		pos;

	// get_texture_index(v);
	texx = (int)(ray->wall_x * 128.0);
	if ((ray->side == 0 && ray->dir_x > 0)
		|| (ray->side == 1 && ray->dir_y < 0))
		texx = 128 - texx - 1;
	step = 1.0 * 128 / ray->line_height;
	pos = (ray->draw_start - ray->pitch - v->screen.resh / 2
			+ ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		texy = (int)pos & (128 - 1);
		pos += step;
		color = getcolorpix(v->img[1].addr, (texy * v->img[1].len) + (texx * 4), 0);
		// color = v->tex[0][64 * texy + texx];
		// texy++;
		// if (tex->index == NORTH || tex->index == EAST)
		if (ray->side == 1)
			color = (color >> 1) & 8355711;
		if (color > 0)
		// if (v->img[1].addr[color + 3] == 0)
			// v->img[0].addr[y*x] = color;
			img_pix_put(&v->img[COMP_N], (t_point){x, y + v->mouse.yoff, 0, color},//  + v->mouse.yoff
				v->screen.resw, v->screen.resh);
		y++;
	}
}

int	raycasting(t_vars *v)
{
	t_ray	ray;
	int		x;

	x = 0;
	ray = v->ray;
	while (x < v->img[EMAP].width)
	{
		// if (x >= v->img[EMAP].width)
		// 	return (0);
		init_raycasting_info(x, &ray, v);
		set_dda(&ray, v);
		perform_dda(v, &ray);
		calculate_line_height(&ray, v);
		update_texture_pixels(v, &ray, x);
		x++;
	}
	return (1);
}