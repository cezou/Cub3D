/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_hud_arms.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 20:43:05 by pmagnero          #+#    #+#             */
/*   Updated: 2024/10/11 11:13:43 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3D.h"

/// @brief 
/// @param v 
/// @param delta 
/// @param i 
/// @param xoff 
void	renderarmdigit(t_vars *v, int delta, int i, int xoff)
{
	t_point	p;
	int		w;
	int		h;
	int		d;

	d = (xoff / v->hud.img.ratiox) - (i % 4 + i / 4) * (v->tmp[0].animx)
		+ ((i % 4 - i / 4) - 1) * (25 / v->hud.img.ratiox)
		- ((10 - 5 * (i / 4 == 1)) / v->hud.img.ratiox);
	p.x = i * v->tmp[0].animx + v->tmp[0].animx + 1;
	w = p.x + v->tmp[0].animx;
	h = v->tmp[0].height;
	p.color = 0;
	while (++p.x < w)
	{
		p.y = v->tmp[0].animy + 1;
		while (++p.y < h)
		{
			p.z = (p.y * v->tmp[0].len) + (p.x * 4);
			add_pix(v, (t_point){p.x + d,
				p.y + delta, p.z, p.color},
				(t_point3){0}, (t_point){0});
		}
	}
}

/// @brief Render the HUD
/// @param v Vars
void	renderarmsdigits(t_vars *v, int xoff)
{
	int		delta;
	int		i;

	v->tmp[0] = v->img[ESMALLNUMBERS];
	i = 0;
	delta = -v->tmp[0].animy + ceil(9 / v->hud.img.ratioy);
	if (v->tmp[1].id == v->img[EBUFF].id)
		delta = v->screen.gameh - v->tmp[0].animy
			+ ceil(9 / v->hud.img.ratioy);
	while (++i < 7)
	{
		if (i == 4)
			delta += (26 / v->hud.img.ratioy);
		if (!v->player.weapons[i])
			continue ;
		renderarmdigit(v, delta, i, xoff);
	}
}
