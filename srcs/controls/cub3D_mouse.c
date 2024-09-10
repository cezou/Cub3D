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
	if (p->game.start > 1 && p->god && (button == 4 || button == 5))
	{
		p->mouse.button = button;
		zoom(button, p);
		p->mouse.prevx = x;
		p->mouse.prevy = y;
		p->game.refreshmap = 1;
		p->game.start = 2;
		render(p);
	}
	else if (p->game.start > 1 && p->god && (button == 1 || button == 3))
	{
		p->mouse.button = button;
		p->mouse.prevx = x;
		p->mouse.prevy = y;
		p->game.refreshmap = 1;
		p->game.start = 2;
	}
	return (0);
}

int	mouse_up(int button, int x, int y, t_vars *p)
{
	(void)x;
	(void)y;
	if (p->game.start > 1 && p->god && (button == 1 || button == 3))
	{
		p->game.refreshmap = 1;
		p->game.start = 2;
		p->mouse.button = 0;
	}
	return (0);
}

int	mouse_move(int x, int y, t_vars *p)
{
	p->mouse.renderrate = 0;
	if (ft_abs(p->mouse.prevy - y) == 3 || ft_abs(p->mouse.prevx - x) == 3)
		p->mouse.renderrate = 1;
	if (p->game.start > 1 && p->god && p->mouse.button == 1)
	{
		p->mouse.xoff += (x - p->mouse.prevx);
		p->mouse.yoff += (y - p->mouse.prevy);
		p->mouse.prevx = x;
		p->mouse.prevy = y;
		if (p->mouse.renderrate == 1)
			render(p);
	}
	return (0);
}