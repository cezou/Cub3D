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

/// @brief Attack action. Change animations offset in the sprite sheet.
/// @param v Vars
void	attack(t_vars *v)
{
	if (!v->player.pattack)
		v->player.pattack = 1;
	else if (v->player.pattack && v->player.animoff > v->player.img.width)
	{
		v->player.pattack = 0;
	}
	v->player.animoff = v->player.img.animx;
}

/// @brief Movement switch case
/// @param v Vars
void	handle_movement(t_vars *v)
{
	if (is_pressed(XK_w, v))
		move(v, NORTH);
	if (is_pressed(XK_s, v))
		move(v, SOUTH);
	if (is_pressed(XK_a, v))
		move(v, WEST);
	if (is_pressed(XK_d, v))
		move(v, EAST);
	if (is_pressed(XK_Left, v))
		move(v, RIGHT);
	if (is_pressed(XK_Right, v))
		move(v, LEFT);
	if (is_pressed(XK_Up, v))
		move(v, UP);
	if (is_pressed(XK_Down, v))
		move(v, DOWN);
	if (is_pressed(XK_space, v))
		move(v, 8);
	if (is_pressed(XK_Page_Down, v))
	{
		v->player.hp -= 1;
		v->hud.refreshhealth = 1;
	}
	if (is_pressed(XK_Page_Up, v))
	{
		v->player.armor += 1;
		v->hud.refresharmor = 1;
		v->player.ammo[0] += 1;
		v->hud.refreshammo = 1;
	}
}

/// @brief Toggle god/debug mode
/// @param v Vars
void	tooglegod(t_vars *v)
{
	if (v->game.god == 0)
		v->game.god = 1;
	else if (v->game.god == 1)
		v->game.god = 0;
}

/// @brief Hooks function when a key is pressed.
/// @param kd Keyboard key pressed
/// @param v Vars
/// @return 0
int	keys(int kd, t_vars *v)
{
	v->keys[kd] = true;
	if (v->game.won < 4 && kd == XK_x)
		attack(v);
	if (v->game.won < 4 && kd == XK_Shift_L && !v->player.injump)
		v->player.jumping = 1;
	if (v->game.won < 4 && kd == 38 && v->player.animoff == 0)
		(v->player.img = v->img[EFIST]);
	if (v->game.won < 4 && kd == 233 && v->player.animoff == 0)
		(v->player.img = v->img[EGUN]);
	// if (v->game.won < 4 && kd == 34)
		// (v->player.img = v->img[EGUN]);// OTHER WEAPONS
	// if (v->game.won < 4 && kd == 39)
		// (v->player.img = v->img[EGUN]);// OTHER WEAPONS
	// if (v->game.won < 4 && kd == 40)
		// (v->player.img = v->img[EGUN]);// OTHER WEAPONS
	// if (v->game.won < 4 && kd == 45)
		// (v->player.img = v->img[EGUN]);// OTHER WEAPONS
	if (kd == XK_Escape)
		menuexit(v);
	if (v->game.won < 4 && kd == XK_Return)
		returnkey(v);
	if (v->game.pause)
		menuarrow(v, kd);
	if (!v->game.pause && !v->game.won && v->game.start > 1
		&& is_pressed(XK_F1, v))
		tooglegod(v);
	if (((v->game.start > 1 && v->game.god && v->game.won < 4))
		&& is_pressed(XK_F5, v))
		hotreload(v);
	return (0);
}

/// @brief Hooks function to catch events like mouse move, key pressed/released.
/// @param v Vars
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
