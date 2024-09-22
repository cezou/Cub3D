/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_hud.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 20:43:05 by pmagnero          #+#    #+#             */
/*   Updated: 2024/10/04 12:32:48 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3D.h"

/// @brief 
/// @param v 
/// @param nb 
void	number_to_digits(t_vars *v, int n, int res[4], int *i)
{
	if (n > 9)
		number_to_digits(v, n / 10, res, i);
	res[*i] = n % 10;
	(*i)++;
}

/// @brief 
/// @param v 
void	renderemptyzone(t_vars *v, t_imga zone, int xoff)
{
	t_point	p;
	int		w;
	int		h;
	int		delta;

	delta = 0;
	if (v->tmp[1].id == v->img[EBUFF].id)
		delta = v->screen.gameh;
	p.x = -1;
	v->tmp[0] = zone;
	w = v->tmp[0].width;
	h = v->tmp[0].height;
	p.color = 0;
	while (++p.x < w)
	{
		p.y = -1;
		while (++p.y < h)
		{
			p.z = (p.y * v->tmp[0].len) + (p.x * 4);
			add_pix(v, (t_point){p.x + ceil(xoff / v->hud.img.ratiox),
				p.y + delta, p.z, p.color},
				(t_point2){0}, (t_point){0});
		}
	}
}

/// @brief Render the HUD
/// @param v Vars
void	renderdoomhead(t_vars *v)
{
	t_point	p;
	int		w;
	int		h;
	int		delta;

	delta = 0;
	if (v->tmp[1].id == v->img[EBUFF].id)
		delta = v->screen.gameh;
	p.x = v->hud.animoff - 1;
	v->tmp[0] = v->img[EDOOMHTMP];
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
				p.y + delta, p.z, p.color},
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
void	renderhud(t_vars *v, t_imga dest)
{
	v->tmp[0] = v->img[EMAP];
	v->tmp[1] = v->img[EBUFF];
	rendercrosshair(v, (t_point){v->tmp[0].width / 2 - 10, 0, 0, 0},
		v->tmp[0].width / 2 + 10, v->tmp[0].height / 2 + 2);
	v->tmp[1] = dest;
	if (v->hud.refresh)
		save_screen_to_buffer(v->img[EHUD], v->hud.img, 0);
	if (v->hud.refreshdh)
		renderdoomhead((v->hud.refreshdh = 0, v));
	if (v->hud.refreshhealth)
	{
		renderemptyzone(v, v->img[EHEALTH], 105);
		renderelement((v->hud.refreshhealth = 0, v),
			105 + v->img[EHEALTHTMP].width - 4, v->player.hp, 1);
	}
	if (v->hud.refresharmor)
	{
		renderemptyzone(v, v->img[EARMOR], 392);
		renderelement((v->hud.refresharmor = 0, v),
			392 + v->img[EARMORTMP].width - 2, v->player.armor, 1);
	}
	if (v->hud.refreshammo)
	{
		renderemptyzone(v, v->img[EAMMO], 0);
		renderelement((v->hud.refreshammo = 0, v),
			0 + v->img[EAMMOTMP].width - 4, v->player.ammo[0], 0);
	}
	if (v->hud.refreshweapon)
	{
		renderemptyzone(v, v->img[EWEAPON], 234);
		renderarmsdigits((v->hud.refreshweapon = 0, v), 234);
	}
	if (v->hud.refreshammun)
	{
		renderemptyzone(v, v->img[EAMMUN], 546);
		renderammun(v, 640, v->player.ammo);
		renderammun((v->hud.refreshammun = 0, v), 690, v->player.maxammo);
	}
	if (v->hud.refreshcards)
	{
		renderemptyzone(v, v->img[ECARDSLOT], 517);
		rendercards((v->hud.refreshcards = 0, v), 517, 0, v->player.cards);
	}
	if (v->hud.refresh)
	{
		save_screen_to_buffer(v->img[EBUFF], v->img[EHUD], (v->img[EMAP].width
				* v->img[EMAP].height * (v->img[EMAP].bpp / 8)));
		v->hud.refresh = 0;
	}
}
