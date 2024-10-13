/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_hud_cards.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 20:43:05 by pmagnero          #+#    #+#             */
/*   Updated: 2024/10/13 18:40:27 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3D.h"

/// @brief 
/// @param v Vars
/// @param g 
/// @param t 
/// @param off Offset x,y from the hud element
void	rendercard(t_vars *v, t_point g, int t, int *off)
{
	t_point	p;
	int		delta;

	g.y = off[1] - g.x * v->tmp[0].animy + (11 / v->hud.img.ratioy);
	if (v->tmp[1].id == v->img[EBUFF].id)
		g.y = v->screen.gameh + off[1] - g.x * v->tmp[0].animy
			+ (11 / v->hud.img.ratioy);
	delta = (off[0] / v->hud.img.ratiox) + (9 / v->hud.img.ratiox)
		- t * (v->tmp[0].animx);
	p.x = t * (v->tmp[0].animx) - 1;
	g.z = p.x + v->tmp[0].animx;
	g.color = v->tmp[0].animy * (g.x + 1);
	p.color = 0;
	while (++p.x < g.z)
	{
		p.y = g.x * v->tmp[0].animy + 2;
		while (++p.y < g.color)
		{
			p.z = (p.y * v->tmp[0].len) + (p.x * 4);
			add_pix(v, (t_point){p.x + delta, p.y + g.y, p.z, p.color},
				(t_point3){0}, (t_point){0});
		}
	}
}

/// @brief 
/// @param v 
/// @param xoff 
/// @param yoff 
/// @param arr 
void	rendercards(t_vars *v, int xoff, int yoff, int *arr)
{
	int		t;
	t_point	g;
	int		off[2];

	t = -1;
	v->tmp[0] = v->img[ECARDS];
	off[0] = xoff;
	while (++t < 6)
	{
		g.x = 0;
		if (!arr[t])
		{
			yoff += 27 / v->hud.img.ratioy;
			continue ;
		}
		if (arr[t] == 2)
		{
			g.x = 1;
			yoff -= 2 / v->hud.img.ratioy;
		}
		off[1] = yoff;
		rendercard(v, g, t, off);
		yoff += 27 / v->hud.img.ratioy;
	}
}
