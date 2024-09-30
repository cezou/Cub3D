/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_render_player.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 21:30:54 by pmagnero          #+#    #+#             */
/*   Updated: 2024/09/30 16:53:41 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/// @brief Render the player sprites/animations. Put those pixels in the buff.
/// @param v Vars
void	render_player(t_vars *v)
{
	t_point	p;
	int		w;
	int		h;

	v->tmp[0] = v->player.img;
	v->tmp[1] = v->img[EMAP];
	w = v->player.animoff + v->player.img.animx;
	h = v->tmp[0].height;
	p.x = v->player.animoff - 1;
	p.color = 0;
	while (++p.x < w)
	{
		p.y = -1;
		while (++p.y < h)
		{
			p.z = (p.y * v->tmp[0].len) + (p.x * 4);
			add_pix(v, (t_point){p.x - v->player.animoff + v->screen.gamew / 2
				- v->player.img.animx / 2, p.y + v->screen.gameh
				- h, p.z, p.color}, (t_point2){0}, (t_point){0});
		}
	}
}
