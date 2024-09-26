/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_render_player.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 21:30:54 by pmagnero          #+#    #+#             */
/*   Updated: 2024/09/26 17:52:40 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	render_player(t_vars *v)
{
	t_point	p;
	int		w;
	int		h;

	v->tmp[0] = v->img[EFCK];
	v->tmp[1] = v->img[EMAP];
	w = v->player.animoff + v->img[EPLAYER].anim[0].animx;
	h = v->tmp[0].height;
	p.x = v->player.animoff - 1;
	p.color = 0;
	while (++p.x < w)
	{
		p.y = -1;
		while (++p.y < h)
		{
			p.z = (p.y * v->tmp[0].len) + (p.x * 4);
			add_pix(v, v->tmp,
				(t_point){p.x - v->player.animoff
				+ v->screen.gamew / 2 - v->img[EPLAYER].anim[0].animx / 2,
				p.y + v->screen.gameh - h, p.z, p.color}, (t_point2){0});
		}
	}
}
