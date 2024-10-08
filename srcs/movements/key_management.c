/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:14:16 by cviegas           #+#    #+#             */
/*   Updated: 2024/10/08 18:00:38 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

bool	is_pressed(int key, t_vars *v)
{
	if (v->keys[key])
		return (1);
	return (0);
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
		raycasting(v, v->img[EMAP]);
		rendermenu(v);
		render_player(v, (t_point){0});
		renderhud(v, v->img[EHUD]);
		save_screen_to_buffer(v->img[EBUFF], v->img[EMAP], 0);
		mlx_loop_end((v->game.won = 4, v->mlx));
	}
	return (0);
}

void	key_management(t_vars *v)
{
	if (v->game.start > 1 && v->game.god && is_pressed(XK_m, v))
		hotreload(v);
	if (!v->game.won && v->game.won != 4 && v->game.start > 1)
		handle_movement(v);
}
