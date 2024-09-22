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

/// @brief Put the textures of the menus in the image buffer
/// @param v Vars
/// @param i Index of the texture
/// @param ph Offset positon x
/// @param pw Offset position y
static void	puttexturesmenu(t_vars *v, int i, int ph, int pw)
{
	size_t	k;
	t_point	p;

	p.y = -1;
	while (++(p.y) < v->img[i].height)
	{
		p.x = v->img[i].animx - 1;
		while (++(p.x) < v->img[i].width)
		{
			k = (p.y * v->img[i].len) + (p.x * 4);
			add_pix_to_buffer(v, v->img[i],
				(t_point){(p.x + pw), (p.y + ph), k, 0}, (t_point2){0});
		}
	}
}

/// @brief Render the menu on the screen
/// @param v Vars
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
