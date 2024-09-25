/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_init_window.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:09:56 by pmagnero          #+#    #+#             */
/*   Updated: 2024/09/25 18:56:29 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	initmainimage(t_vars *v)
{
	v->img[EMAP].width = v->screen.gamew;
	v->img[EMAP].height = v->screen.gameh;
	v->img[EBUFF].height = v->screen.resw;
	v->img[EBUFF].height = v->screen.resh;
	v->img[COMP_N].width = v->screen.resw;
	v->img[COMP_N].height = v->screen.resh;
	v->img[EHUD].width = v->screen.hudw;
	v->img[EHUD].height = v->screen.hudh;
	v->img[EMAP].animx = 0;
	v->img[EMAP].animy = 0;
	v->img[COMP_N].animx = 0;
	v->img[COMP_N].animy = 0;
	v->img[COMP_N].anim = NULL;
	v->img[EMAP].anim = NULL;
	v->img[EMAP].animnb = 0;
	v->img[COMP_N].animnb = 0;
}

void	initwindow(t_vars *v, int argc, char **argv)
{
	mlx_get_screen_size(v->mlx, &v->screen.screenw, &v->screen.screenh);
	v->screen.screenw--;
	v->screen.screenh -= TOOLBAR_LINUX_H;
	v->screen.resw = v->screen.screenw;
	v->screen.resh = v->screen.screenh;
	if (argc > 3 && argc < 5)
	{
		v->screen.resw = ft_atol(argv[2]);
		v->screen.resh = ft_atol(argv[3]);
		if (v->screen.resw > INT_MAX || v->screen.resw < INT_MIN
			|| v->screen.resw > v->screen.screenw || v->screen.resw <= 0
			|| ft_strlen(argv[4]) > 10 || v->screen.resh > INT_MAX
			|| v->screen.resh < INT_MIN || v->screen.resh > v->screen.screenh
			|| v->screen.resh <= 0)
			exit((prterr(v, ERRRES, 1, 0), 1));
	}
	v->screen.gamew = v->screen.resw;
	v->screen.gameh = v->screen.resh - v->screen.resh / 5;
	v->screen.hudw = v->screen.resw;
	v->screen.hudh = v->screen.resh / 5;
	initmainimage(v);
	v->screen.win = mlx_new_window(v->mlx, (int)v->screen.resw,
			(int)v->screen.resh, "CUB3D");
	if (!v->screen.win)
		exit((prterr(v, ERRMALL, 1, 0), 1));
}
