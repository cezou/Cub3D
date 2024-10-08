/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_render_player.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 21:30:54 by pmagnero          #+#    #+#             */
/*   Updated: 2024/10/08 19:44:11 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/// @brief Render the player sprites/animations. Put those pixels in the buff.
/// @param v Vars
void	render_player(t_vars *v, t_point c)
{
	t_point	p;

	v->tmp[0] = v->player.currweapon.img;
	c.z = v->player.animoff + v->player.currweapon.img.animx;
	c.color = v->tmp[0].height;
	p.x = v->player.animoff - 1;
	p.color = 0;
	while (++p.x < c.z)
	{
		p.y = -1;
		while (++p.y < c.color)
		{
			c.x = p.x - v->player.animoff + v->screen.gamew / 2
				- v->player.currweapon.img.animx / 2 - v->player.motionx;
			c.y = p.y + v->screen.gameh - c.color - v->player.motiony + 10;
			p.z = (p.y * v->tmp[0].len) + (p.x * 4);
			if (c.x >= 0 && c.x < v->screen.gamew
				&& c.y >= 0 && c.y < v->screen.gameh)
				add_pix(v, (t_point){c.x, c.y, p.z, p.color},
					(t_point2){0}, (t_point){0});
		}
	}
}
