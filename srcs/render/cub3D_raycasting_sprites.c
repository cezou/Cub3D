/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_raycasting_sprites.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 21:30:54 by pmagnero          #+#    #+#             */
/*   Updated: 2024/09/19 16:24:40 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"



// static void	update_texture_pixels(t_vars *v, t_point p, int texx, int texy)
// {
// 	double		step;
// 	double		pos;

// 	texx = (int)(v->ray.wall_x * v->img[1].width);
// 	if ((v->ray.side == 0 && v->ray.dir_x > 0)
// 		|| (v->ray.side == 1 && v->ray.dir_y < 0))
// 		texx = v->img[1].width - texx - 1;
// 	step = 1.0 * v->img[1].width / v->ray.line_height;
// 	pos = (v->ray.draw_start - v->ray.pitch - (v->player.z / v->ray.wall_dist)
// 			- v->screen.resh / 2 + v->ray.line_height / 2) * step;
// 	p.y = v->ray.draw_start;
// 	while (p.y < v->ray.draw_end)
// 	{
// 		texy = (int)pos & (v->img[1].width - 1);
// 		pos += step;
// 		p.color = getcolorpix(v->img[1].addr, (texy * v->img[1].len)
// 				+ (texx * 4), 0);
// 		if (v->ray.side == 1)
// 			p.color = (p.color >> 1) & 8355711;
// 		if (p.color > 0)
// 			img_pix_put(&v->img[EMAP], p, v->screen.resw, v->screen.resh);
// 		p.y++;
// 	}
// }

// void	calculate_sprite_dimension(t_vars *v, )
// {
	
// }

void	animations(t_vars *v)
{
	if (timestamp_in_ms(v) - v->guard.timerguard
		>= (uint64_t)(10000 / v->game.fps))
	{
		v->img[EGUARD].anim[0].animx += v->img[EGUARD].height;  // g
		v->guard.timerguard = timestamp_in_ms(v);
	}
	if (v->img[EGUARD].anim[0].animx > v->img[EGUARD].anim[0].width)
		v->img[EGUARD].anim[0].animx = 0;
}

static void	transform_sprite(t_vars *v, t_sprite *sp)
{
	double		invdet;
	double		spritex;
	double		spritey;
	double		transformx;
	double		vdiv;
	double		vmove;

	vdiv = 1.0;
	vmove = 0;
	spritex = v->img[EGUARD].posx - v->player.x;
	spritey = v->img[EGUARD].posy - v->player.y;
	invdet = 1.0 / (v->player.plane_x * v->player.dir_y
			- v->player.plane_y * v->player.dir_x);
	transformx = invdet * (v->player.dir_y * spritex
			- v->player.dir_x * spritey);
	sp->transformy = invdet * (v->player.plane_x * spritey
			- v->player.plane_y * spritex);
	sp->spritescreenx = (int)((v->screen.resw / 2)
			* (1 + transformx / sp->transformy));
	sp->vmovescreen = (int)(vmove / sp->transformy)
		+ v->ray.pitch + v->player.z / sp->transformy;
	sp->spriteheight = abs((int)(v->screen.resh / sp->transformy)) / vdiv;//using 'transformY' instead of the real distance prevents fisheye
}

static void	set_sprite_boundaries(t_vars *v, t_sprite *sp)
{
	double		udiv;

	udiv = 1.0;
	sp->drawstarty = -sp->spriteheight / 2
		+ v->screen.resh / 2 + sp->vmovescreen;
	if (sp->drawstarty < 0)
		sp->drawstarty = 0;
	sp->drawendy = sp->spriteheight / 2 + v->screen.resh / 2 + sp->vmovescreen;
	if (sp->drawendy >= v->screen.resh)
		sp->drawendy = v->screen.resh - 1;
	sp->spritewidth = abs((int)(v->screen.resh / sp->transformy)) / udiv;
	sp->drawstartx = -sp->spritewidth / 2 + sp->spritescreenx;
	if (sp->drawstartx < 0)
		sp->drawstartx = 0;
	sp->drawendx = sp->spritewidth / 2 + sp->spritescreenx;
	if (sp->drawendx >= v->screen.resw)
		sp->drawendx = v->screen.resw - 1;
}

	// double		vmove;
	// double		udiv;
	// double		vdiv;
	// int	i;

	// i = -1;
	// sort sprites from far to close
	// while (x < v->img[EMAP].width)
	// {

	// }
	// vmove = 0.0;
	// udiv = 1.0;
	// vdiv = 1.0;
	// v->img[EGUARD].posx = 15.0;
	// v->img[EGUARD].posy = 3.0;
void	draw_sprites(t_vars *v, t_sprite *sp, t_point p)
{
	int			tx;
	int			ty;

	transform_sprite(v, sp);
	set_sprite_boundaries(v, sp);
	p.x = sp->drawstartx - 1;
	while (++p.x < sp->drawendx)
	{
		tx = (int)(256 * (p.x - (sp->spritescreenx - sp->spritewidth / 2))
				* 64 / sp->spritewidth) / 256 + v->img[EGUARD].anim[0].animx;
		p.y = sp->drawstarty - 1;
		if (sp->transformy > 0 && p.x > 0 && p.x < v->screen.resw
			&& sp->transformy < v->ray.zbuffer[p.x])
		{
			while (++p.y < sp->drawendy)
			{
				p.z = (p.y - sp->vmovescreen) * 256 - v->screen.resh * 128
					+ sp->spriteheight * 128;
				ty = ((p.z * v->img[EGUARD].height) / sp->spriteheight) / 256;
				p.z = (ty * v->img[EGUARD].len) + (tx * 4);
				if (v->img[EGUARD].addr[p.z + 3] == 0)
				{
					p.color = getcolorpix(v, v->img[EGUARD].addr, p.z);
					img_pix_put(&v->img[EMAP], p, v);
				}
			}
		}
	}
}
