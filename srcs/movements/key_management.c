/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:14:16 by cviegas           #+#    #+#             */
/*   Updated: 2024/09/25 19:19:35 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

bool	is_pressed(int key, t_vars *v)
{
	if (v->keys[key])
		return (1);
	return (0);
}

void	tooglegod(t_vars *v)
{
	if (v->game.god == 0)
		v->game.god = 1;
	else if (v->game.god == 1)
		v->game.god = 0;
}

void	save_screen_to_buffer(t_imga dest, t_imga src, size_t offset)
{
	ft_memcpy(dest.addr + offset, src.addr,
		src.width * src.height * (src.bpp / 8));
}

int	returnkey(t_vars *v)
{
	if ((v->menu.menu == 1 && v->menu.menui == 3) || (v->menu.menu == 2
			&& v->menu.menui == 3))
		exit((cleardata(v, 1), 0));
	if ((v->menu.menu == 2 && v->menu.menui == 0))
		menuoptions(v);
	v->game.start++;
	if (v->game.start > 3)
		v->game.start = 3;
	if (v->game.start == 2 && v->game.won == 0)
	{
		raycasting(v);
		renderhud(v);
		rendermenu(v);
		save_screen_to_buffer(v->img[EBUFF], v->img[EMAP], 0);
		save_screen_to_buffer(v->img[EBUFF], v->img[EHUD], (v->img[EHUD].width
				* v->img[EHUD].height * (v->img[EHUD].bpp / 8)));
		mlx_loop_end((v->game.won = 4, v->mlx));
	}
	return (0);
}

void	key_management(t_vars *v)
{
	if (!v->game.pause && v->game.start > 1 && v->game.god && is_pressed(XK_r,
			v))
		resetpos((v->mouse.renderrate = 0, v), 1);
	if (v->game.start > 1 && v->game.god && is_pressed(XK_m, v))
		hotreload(v);
	if (((v->game.start > 1 && v->game.god) || v->game.won) && is_pressed(XK_F5,
			v))
		hotreload(v);
	if (!v->game.pause && !v->game.won && v->game.start > 1 && is_pressed(XK_F1,
			v))
		tooglegod(v);
	if (!v->game.won && v->game.start > 1)
		handle_movement(v);
}
