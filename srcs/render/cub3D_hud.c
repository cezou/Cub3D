/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_hud.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 20:43:05 by pmagnero          #+#    #+#             */
/*   Updated: 2024/10/02 16:27:03 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/// @brief Scale a src image to the dimension of the dest image
/// @param p {x, y, z, color} => {0}
/// @param src Source image to scale
/// @param dest Destination image
void	scale_img(t_point p, t_imga *src, t_imga *dest)
{
	int		tx;
	int		ty;

	p.y = -1;
	while (++p.y < dest->height)
	{
		p.x = -1;
		while (++p.x < dest->width)
		{
			tx = p.x * src->width / dest->width;
			ty = p.y * src->height / dest->height;
			p.z = (p.y * dest->len) + (p.x * 4);
			p.color = (ty * src->len) + (tx * 4);
			dest->addr[p.z + 4] = src->addr[p.color + 4];
			dest->addr[p.z + 3] = src->addr[p.color + 3];
			dest->addr[p.z + 2] = src->addr[p.color + 2];
			dest->addr[p.z + 1] = src->addr[p.color + 1];
			dest->addr[p.z] = src->addr[p.color];
		}
	}
	dest->ratiox = (double)(src->width) / (double)(dest->width);
	dest->ratioy = (double)(src->height) / (double)(dest->height);
}

/// @brief Render the HUD
/// @param v Vars
void	renderdoomhead(t_vars *v)
{
	t_point	p;
	int		w;
	int		h;

	p.x = v->hud.animoff - 1;
	v->tmp[0] = v->img[EDOOMHTMP];
	v->tmp[1] = v->img[EBUFF];
	w = v->hud.animoff + v->tmp[0].animx;
	h = v->tmp[0].height;
	p.color = 0;
	while (++p.x < w)
	{
		p.y = -1;
		while (++p.y < h)
		{
			p.z = (p.y * v->tmp[0].len) + (p.x * 4);
			add_pix(v, (t_point){p.x - v->hud.animoff + v->tmp[0].animx
				+ (v->screen.hudw / 2) - (v->tmp[0].width / 2),
				p.y + v->screen.gameh, p.z, p.color},
				(t_point2){0}, (t_point){0});
		}
	}
}

/// @brief Render the crosshair
/// @param v Vars
void	rendercrosshair(t_vars *v, t_point p, int w, int h)
{
	while (++p.x < w)
	{
		p.y = v->tmp[0].height / 2 - 2;
		while (++p.y < h)
		{
			p.color = v->infos.floor;
			if (v->game.canhit)
				p.color = v->infos.ceil;
			add_pix(v, p, (t_point2){0}, (t_point){0, 1, 0, 0});
		}
	}
	p.x = v->tmp[0].width / 2 - 2;
	w = v->tmp[0].width / 2 + 2;
	h = v->tmp[0].height / 2 + 10;
	while (++p.x < w)
	{
		p.y = v->tmp[0].height / 2 - 10;
		while (++p.y < h)
		{
			p.color = v->infos.floor;
			if (v->game.canhit)
				p.color = v->infos.ceil;
			add_pix(v, p, (t_point2){0}, (t_point){0, 1, 0, 0});
		}
	}
}

/// @brief Render the HUD
/// @param v Vars
void	renderhud(t_vars *v)
{
	v->tmp[0] = v->img[EMAP];
	v->tmp[1] = v->img[EBUFF];
	rendercrosshair(v, (t_point){v->tmp[0].width / 2 - 10, 0, 0, 0},
		v->tmp[0].width / 2 + 10, v->tmp[0].height / 2 + 2);
	if (v->hud.refreshdh)
		renderdoomhead(v);
	v->hud.refreshdh = 0;
	if (!v->hud.refresh)
		return ;
	save_screen_to_buffer(v->img[EHUD], v->img[EHUDTMP], 0);
	save_screen_to_buffer(v->img[EBUFF], v->img[EHUD], (v->img[EMAP].width
			* v->img[EMAP].height * (v->img[EMAP].bpp / 8)));
	v->hud.refresh = 0;
}
