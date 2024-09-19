/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_raycasting_skybox.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 21:30:54 by pmagnero          #+#    #+#             */
/*   Updated: 2024/09/18 12:25:20 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

#define SKYBOX_REPEATS 1

void	set_skybox(t_vars *v)
{
	v->ray.dir_x = v->player.dir_x - v->player.plane_x;
	v->ray.dir_y = v->player.dir_y - v->player.plane_y;
	v->ray.dir_x1 = v->player.dir_x + v->player.plane_x;
	v->ray.dir_y1 = v->player.dir_y + v->player.plane_y;
	v->ray.tx0 = (int)(-atan2(v->ray.dir_x, v->ray.dir_y)
			* (double)v->img[ESKYBOX].width / (2 * M_PI) * SKYBOX_REPEATS);
	v->ray.tx1 = (int)(-atan2(v->ray.dir_x1, v->ray.dir_y1)
			* (double)v->img[ESKYBOX].width / (2 * M_PI) * SKYBOX_REPEATS);
	while (v->ray.tx1 < v->ray.tx0)
		v->ray.tx1 += v->img[ESKYBOX].width;
	while (v->ray.tx0 < 0)
	{
		v->ray.tx0 += v->img[ESKYBOX].width;
		v->ray.tx1 += v->img[ESKYBOX].width;
	}
	v->ray.dtx = v->ray.tx1 - v->ray.tx0;
	v->ray.dy = v->screen.resh / 2 + v->ray.pitch;
	v->ray.dty = v->img[ESKYBOX].height * (v->screen.resh / 2 + v->ray.pitch)
		/ (v->screen.resh / 2 + LOOKUP_MAX) - 1;
	v->ray.ty0 = v->img[ESKYBOX].height - 1 - v->ray.dty;
}

void	draw_skybox(t_vars *v, t_point p, int tx, int ty)
{
	int		cx;
	int		cy;

	set_skybox(v);
	cx = 0;
	while (++p.x < v->screen.resw)
	{
		if (v->ray.tx0 >= v->img[ESKYBOX].width)
			tx = v->ray.tx0 - v->img[ESKYBOX].width;
		else
			tx = v->ray.tx0;
		p.y = -1;
		cy = 0;
		ty = v->ray.ty0;
		while (++p.y < v->ray.dy)
		{
			p.color = getcolorpix(v, v->img[ESKYBOX].addr,
					(ty * v->img[ESKYBOX].len) + (tx * 4));
			img_pix_put(&v->img[EMAP], p, v);
			cy += v->ray.dty;
			while (cy > v->ray.dy)
			{
				ty += 1;
				cy -= v->ray.dy;
			}
		}
		cx += v->ray.dtx;
		while (cx > v->screen.resw)
		{
			v->ray.tx0 += 1;
			cx -= v->screen.resw;
		}
	}
}
