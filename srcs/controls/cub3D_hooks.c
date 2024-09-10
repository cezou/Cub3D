/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_hooks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 18:24:52 by pmagnero          #+#    #+#             */
/*   Updated: 2024/04/05 17:25:04 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	tooglegod(t_vars *v)
{
	if (v->god == 0)
		v->god = 1;
	else if (v->god == 1)
		v->god = 0;
}

int	returnkey(t_vars *v)
{
	if ((v->menu.menu == 1 && v->menu.menui == 3)
		|| (v->menu.menu == 2 && v->menu.menui == 3))
		exit((cleardata(v, 1), 0));
	if ((v->menu.menu == 2 && v->menu.menui == 0))
		menuoptions(v);
	v->game.start++;
	if (v->game.start > 3)
		v->game.start = 3;
	if (v->game.start == 2)
	{
		if (ACTIVATE_SOUND)
		{
			ma_sound_stop(&v->sound.sound[0]);
			ma_sound_set_looping(&v->sound.sound[2], MA_TRUE);
			ma_sound_set_fade_start_in_milliseconds(&v->sound.sound[2],
				0.0f, 0.8f, 3000, 3000);
			ma_sound_start(&v->sound.sound[2]);
		}
		mlx_loop_end(v->mlx);
	}
	return (0);
}

int	keys(int keycode, t_vars *v)
{
	if (keycode == XK_Escape)
		menuexit(v);
	else if (!v->game.pause && v->game.start > 1 && v->god && keycode == XK_r)
		resetpos((v->mouse.renderrate = 0, v), 1);
	else if (!v->game.won && v->game.start > 1 && keycode == XK_w)
		arrows(v, v->player.player->up, NORTH);
	else if (!v->game.won && v->game.start > 1 && keycode == XK_s)
		arrows(v, v->player.player->down, SOUTH);
	else if (!v->game.won && v->game.start > 1 && keycode == XK_a)
		arrows(v, v->player.player->left, WEST);
	else if (!v->game.won && v->game.start > 1 && keycode == XK_d)
		arrows(v, v->player.player->right, EAST);
	else if (!v->game.won && v->game.start > 1 && keycode == XK_Left)
		arrows(v, v->player.player->right, 4);
	else if (!v->game.won && v->game.start > 1 && keycode == XK_Right)
		arrows(v, v->player.player->left, 5);
	else if (v->game.start > 1 && v->god && keycode == XK_m)
		hotreload(v);
	else if (((v->game.start > 1 && v->god) || v->game.won) && keycode == XK_F5)
		hotreload(v);
	else if (!v->game.pause && !v->game.won && v->game.start > 1
		&& keycode == XK_F1)
		tooglegod(v);
	else if (keycode == XK_Return)
		returnkey(v);
	// else if (!v->game.pause && v->game.start > 1 && keycode == XK_space)
	// 	attack(v);
	return (0);
}

int	closecross(t_vars *v)
{
	exit((cleardata(v, 1), 0));
	return (0);
}

void	hooks(t_vars *v)
{
	if (mlx_hook(v->screen.win, 4, 1L << 2, mouse_down, v) < 0)
		exit((prterr(v, "Error hooks mouse down\n", 1, 1), 1));
	if (mlx_hook(v->screen.win, 5, 1L << 3, mouse_up, v) < 0)
		exit((prterr(v, "Error hooks up\n", 1, 2), 1));
	if (mlx_hook(v->screen.win, 6, 1L << 6, mouse_move, v) < 0)
		exit((prterr(v, "Error hooks mouse move\n", 1, 1), 1));
	if (mlx_hook(v->screen.win, 2, 1L << 0, keys, v) < 0)
		exit((prterr(v, "Error hooks keys\n", 1, 1), 1));
	if (mlx_hook(v->screen.win, 3, 1L << 1, keys_release, v) < 0)
		exit((prterr(v, "Error hooks keys Release\n", 1, 1), 1));
	if (mlx_hook(v->screen.win, 17, 1L << 17, closecross, v) < 0)
		exit((prterr(v, "Error hooks cross\n", 1, 1), 1));
}
