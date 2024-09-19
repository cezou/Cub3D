/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_raycasting_floor_ceiling.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:38:17 by pmagnero          #+#    #+#             */
/*   Updated: 2024/09/19 19:23:35 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/*HORIZONTAL METHOD*/

// static void	init_ray_floor(t_vars *v)
// {
// 	v->ray.dir_x = v->player.dir_x - v->player.plane_x;
// 	v->ray.dir_y = v->player.dir_y - v->player.plane_y;
// 	v->ray.dir_x1 = v->player.dir_x + v->player.plane_x;
// 	v->ray.dir_y1 = v->player.dir_y + v->player.plane_y;
// }

// static void	update_texture_pixels(t_vars *v, int y)
// {
// 	int			p;
// 	double		posz;
// 	double		rowdist;
// 	double		fstepx;
// 	double		fstepy;
// 	double		fx;
// 	double		fy;
// 	int			x;
// 	int			tx;
// 	int			ty;
// 	uint32_t	color;

// 	x = 0;
// 	p = y - v->screen.resh / 2;
// 	posz = 0.5 * v->screen.resh;
// 	rowdist = posz / p;
// 	fstepx = rowdist * (v->ray.dir_x1 - v->ray.dir_x) / v->screen.resw;
// 	fstepy = rowdist * (v->ray.dir_y1 - v->ray.dir_y) / v->screen.resw;
// 	fx = v->player.x + rowdist * v->ray.dir_x;
// 	fy = v->player.y + rowdist * v->ray.dir_y;
// 	while (x < v->screen.resw)
// 	{
// 		int cx = (int)(fx);
// 		int cy = (int)(fy);
// 		tx = (int)(64 * (fx - cx)) & (64 - 1);
// 		ty = (int)(64 * (fy - cy)) & (64 - 1);
// 		fx += fstepx;
// 		fy += fstepy;
// 		// FLOOR
// 		// color = getcolorpix(v->img[ESPACE].addr,
// 					(ty * v->img[ESPACE].len) + (tx * 4), 0);
// 		color = v->tex[4][64 * ty + tx];
// 		color = (color >> 1) & 8355711;
// 		img_pix_put(&v->img[COMP_N], (t_point){x,
// 				y + v->mouse.yoff, 0, color},//  + v->mouse.yoff
// 			v->screen.resw, v->screen.resh);
// 		// CEILING
// 		// color = getcolorpix(v->img[ESPACE].addr,
// 					(ty * v->img[ESPACE].len) + (tx * 4), 0);
// 		color = v->tex[5][64 * ty + tx];
// 		color = (color >> 1) & 8355711;
// 		img_pix_put(&v->img[COMP_N], (t_point){x,
// 			v->screen.resh - y / 2 - 1 + v->mouse.yoff, 0, color},
// 			v->screen.resw, v->screen.resh);
// 		x++;
// 	}
// }

// void	set_floor_ceiling_horiz(t_vars *v)
// {
// 	int		y;

// 	y = 0;
// 	while (y < v->img[COMP_N].height)
// 	{
// 		init_ray_floor(v);
// 		update_texture_pixels(v, y);
// 		y++;
// 	}
// }

/*VERTICAL METHOD*/

void	set_wall_dir(t_vars *v)
{
	if (v->ray.side == 0 && v->ray.dir_x > 0)
	{
		v->ray.dir_x1 = v->ray.map_x;
		v->ray.dir_y1 = v->ray.map_y + v->ray.wall_x;
	}
	else if (v->ray.side == 0 && v->ray.dir_x < 0)
	{
		v->ray.dir_x1 = v->ray.map_x + 1.0;
		v->ray.dir_y1 = v->ray.map_y + v->ray.wall_x;
	}
	else if (v->ray.side == 1 && v->ray.dir_y > 0)
	{
		v->ray.dir_x1 = v->ray.map_x + v->ray.wall_x;
		v->ray.dir_y1 = v->ray.map_y;
	}
	else
	{
		v->ray.dir_x1 = v->ray.map_x + v->ray.wall_x;
		v->ray.dir_y1 = v->ray.map_y + 1.0;
	}
}

// p.color = v->tex[5][64 * ty + tx];
void	draw_ceiling(t_vars *v, t_point p, int tx, int ty)
{
	double		currfx;
	double		currfy;
	double		weight;
	double		currdist;
	double		distplay;

	distplay = 0.0;
	while (p.y < v->ray.draw_start)
	{
		currdist = (v->screen.resh - (2.0 * v->player.z))
			/ (v->screen.resh - 2.0 * (p.y - v->ray.pitch));
		weight = (currdist - distplay) / (v->ray.wall_dist - distplay);
		currfx = weight * v->ray.dir_x1 + (1.0 - weight) * v->player.x;
		currfy = weight * v->ray.dir_y1 + (1.0 - weight) * v->player.y;
		if ((int)currfx > 10 && (int)currfx < 16)
		{
			p.y++;
			continue ;
		}
		tx = (int)(currfx * v->img[ESPACE].width) & (v->img[ESPACE].width - 1);
		ty = (int)(currfy * v->img[ESPACE].height) & (v->img[ESPACE].height - 1);
		p.color = getcolorpix(v, v->img[ESPACE].addr,
				(ty * v->img[ESPACE].len) + (tx * 4));
		p.color = (p.color >> 1) & 8355711;
		img_pix_put(&v->img[EMAP], p, v);
		p.y++;
	}
}

void	draw_floor(t_vars *v, t_point p, int tx, int ty)
{
	double		currfx;
	double		currfy;
	double		weight;
	double		currdist;
	double		distplay;

	distplay = 0.0;
	// if (v->ray.img.id == EDOOR && v->ray.side == 1)
	// 	v->ray.wall_dist -= v->ray.sidedist_y - v->ray.deltadist_y * 0.5;
	// else if (v->ray.img.id == EDOOR && v->ray.side == 0)
	// 	v->ray.wall_dist -= v->ray.sidedist_x - v->ray.deltadist_x * 0.5;
	while (p.y < v->screen.resh)
	{
		currdist = (v->screen.resh + (2.0 * v->player.z))
			/ (2.0 * (p.y - v->ray.pitch) - v->screen.resh);
		weight = (currdist - distplay) / (v->ray.wall_dist - distplay);
		if (v->ray.img.id == EDOOR)
		{
			weight = (currdist - distplay) / (v->ray.wall_dist - v->ray.deltadist_y * 0.5 - distplay);
		}
		currfx = weight * v->ray.dir_x1 + (1.0 - weight) * v->player.x;
		currfy = weight * v->ray.dir_y1 + (1.0 - weight) * v->player.y;
		tx = (int)(currfx * v->img[ESPACE].width) & (v->img[ESPACE].width - 1);
		ty = (int)(currfy * v->img[ESPACE].height) & (v->img[ESPACE].height - 1);
		p.color = getcolorpix(v, v->img[ESPACE].addr,
				(ty * v->img[ESPACE].len) + (tx * 4));
		p.color = (p.color >> 1) & 8355711;
		img_pix_put(&v->img[EMAP], p, v);
		p.y++;
	}
}

void	set_floor_ceiling_vert(t_vars *v, t_point p)
{
	set_wall_dir(v);
	if (v->ray.draw_end < 0)
		v->ray.draw_end = v->screen.resh;
	draw_ceiling(v, p, 0, 0);
	p.color = 0;
	p.z = 0;
	p.y = v->ray.draw_end;
	draw_floor(v, p, 0, 0);
}
