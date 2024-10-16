/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_mouse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 18:18:37 by pmagnero          #+#    #+#             */
/*   Updated: 2024/04/05 12:19:12 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	zoom(int button, t_vars *vars)
{
	if (button == 4)
		vars->mouse.zoom *= 1.1;
	else if (button == 5)
		vars->mouse.zoom *= 0.9;
}

int	mouse_down(int button, int x, int y, t_vars *p)
{
	if (button == SCROLL_UP && p->hud.map_zoom != 4)
		p->hud.map_zoom -= 2;
	if (button == SCROLL_DOWN && p->hud.map_zoom != 100)
		p->hud.map_zoom += 2;
	if (p->game.start > 1 && p->game.god && (button == 4 || button == 5))
	{
		p->mouse.button = button;
		zoom(button, p);
		p->mouse.prevx = x;
		p->mouse.prevy = y;
		p->game.start = 2;
		render(p);
	}
	else if (p->game.start > 1 && p->game.god && (button == 1 || button == 3))
	{
		attack(p, XK_x);
		p->mouse.button = button;
		p->mouse.prevx = x;
		p->mouse.prevy = y;
		p->game.start = 2;
	}
	return (0);
}

int	mouse_up(int button, int x, int y, t_vars *p)
{
	(void)x;
	(void)y;
	p->mouses[button] = false;
	if (p->game.start > 1 && p->game.god && (button == 1 || button == 3))
	{
		p->game.start = 2;
		p->mouse.button = 0;
	}
	return (0);
}

int	mouse_move(int x, int y, t_vars *p)
{
	t_point2	f;

	if (p->game.pause || p->game.start < 2 || !p->game.god)
		return (0);
	f.z = p->screen.gamew / 2;
	f.t = p->screen.gameh / 2;
	if (x == f.z && y == f.t)
		return (0);
	p->game.canhit = 0;
	p->mouse.prevx = x - f.z;
	p->mouse.prevy = y - f.t;
	f.x = (double)p->mouse.prevx / (double)p->screen.gamew * p->mouse.sensx;
	f.y = (double)p->mouse.prevy / (double)p->screen.gameh * p->mouse.sensy;
	if (x < p->mouse.prevx)
		rotatecamx(p, RIGHT, f.x * p->player.mouserotspeed);
	else if (x > p->mouse.prevx)
		rotatecamx(p, LEFT, f.x * p->player.mouserotspeed);
	if (y < p->mouse.prevy)
		rotatecamy(p, UP, f.y * p->player.mouserotspeed, 400);
	else if (y > p->mouse.prevy)
		rotatecamy(p, DOWN, f.y * p->player.mouserotspeed, 400);
	mlx_mouse_move(p->mlx, p->screen.win, f.z, f.t);
	return (0);
}
