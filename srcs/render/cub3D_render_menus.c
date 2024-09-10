/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_render_menus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:53:03 by pmagnero          #+#    #+#             */
/*   Updated: 2024/04/05 12:19:12 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void	puttexturesmenu(t_vars *v, int i, int ph, int pw)
{
	size_t	k;
	t_point	p;
	t_point	d;

	p.y = -1;
	while (++(p.y) < v->img[i].height)
	{
		p.x = v->img[i].animx - 1;
		while (++(p.x) < v->img[i].width)
		{
			k = (p.y * v->img[i].len) + (p.x * 4);
			if (v->img[i].addr[k + 3] == 0)
			{
				d.x = (p.x + pw) * v->mouse.zoom;
				d.y = (p.y + ph) * v->mouse.zoom;
				img_pix_put(&v->img[EMAP],
					(t_point){d.x - (v->mapv.mapw * v->mouse.zoom / 2)
					+ v->mouse.xoff,
					d.y - (v->mapv.maph * v->mouse.zoom / 2) + v->mouse.yoff, 0,
					getcolorpix(v->img[i].addr, k, v->game.pause)},
					v->screen.resw, v->screen.resh);
			}
		}
	}
}

void	rendermenu(t_vars *v)
{
	if (v->menu.menu == 1)
	{
		puttexturesmenu(v, EMENU, v->screen.resh * 0.25,
			v->screen.resw / 2 - v->img[EMENU].width / 2);
	}
	else if (v->menu.menu == 2)
	{
		puttexturesmenu(v, EMENUIG, v->screen.resh * 0.25,
			v->screen.resw / 2 - v->img[EMENUIG].width / 2);
		puttexturesmenu(v, EMENUSELECT,
			v->screen.resh * 0.25 + 1 + (v->menu.menui * 90),
			v->screen.resw / 2 - v->img[EMENUSELECT].width / 2);
	}
	else if (v->menu.menu == 3)
	{
		puttexturesmenu(v, EMENUOPT, v->screen.resh * 0.25,
			v->screen.resw / 2 - v->img[EMENUOPT].width / 2);
		puttexturesmenu(v, EMENUSELECT, v->screen.resh * 0.25 + 1 + (136),
			v->screen.resw / 2 - v->img[EMENUSELECT].width / 2);
	}
}
