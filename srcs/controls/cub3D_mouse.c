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
	double	fx;
	double	fy;

	if (p->game.start > 1 && p->game.god)
	{
		p->game.canhit = 0;
		p->mouse.prevx = x - p->screen.gamew / 2;
		p->mouse.prevy = y - p->screen.gameh / 2;
		fx = (double)p->mouse.prevx / (double)p->screen.gamew * p->mouse.sensx;
		fy = (double)p->mouse.prevy / (double)p->screen.gameh * p->mouse.sensy;
		if (x < p->mouse.prevx)
			rotatecamx(p, RIGHT, fx * p->player.mouserotspeed);
		else if (x > p->mouse.prevx)
			rotatecamx(p, LEFT, fx * p->player.mouserotspeed);
		if (y < p->mouse.prevy)
			rotatecamy(p, UP, fy * p->player.mouserotspeed, 400);
		else if (y > p->mouse.prevy)
			rotatecamy(p, DOWN, fy * p->player.mouserotspeed, 400);
		mlx_mouse_move(p->mlx, p->screen.win, p->screen.gamew / 2,
			p->screen.gameh / 2);
	}
	return (0);
}
