/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_init_window.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:09:56 by pmagnero          #+#    #+#             */
/*   Updated: 2024/10/30 14:36:14 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void	initmainimage(t_vars *v)
{
	v->screen.gamew = v->screen.resw;
	v->screen.gameh = v->screen.resh - v->screen.resh / 5;
	v->screen.hudw = v->screen.resw;
	v->screen.hudh = v->screen.resh / 5;
	v->screen.ratio = v->screen.resw / v->screen.resh;
	v->img[EMAP].width = v->screen.gamew;
	v->img[EMAP].height = v->screen.gameh;
	v->img[EBUFF].height = v->screen.resw;
	v->img[EBUFF].height = v->screen.resh;
	v->img[COMP_N].width = v->screen.resw;
	v->img[COMP_N].height = v->screen.resh;
	v->img[COMP_N].anim = NULL;
	v->img[EMAP].anim = NULL;
	v->img[EMAP].animnb = 0;
	v->img[COMP_N].animnb = 0;
}

static bool	is_bad_res(t_vars *v)
{
	return (v->screen.resw > INT_MAX || v->screen.resw < INT_MIN
		|| v->screen.resh > INT_MAX || v->screen.resh < INT_MIN
		|| v->screen.resw <= 0 || v->screen.resh <= 0);
}

void	initwindow(t_vars *v, int argc, char **argv)
{
	mlx_get_screen_size(v->mlx, &v->screen.screenw, &v->screen.screenh);
	v->screen.screenw--;
	v->screen.screenh -= TOOLBAR_LINUX_H;
	v->screen.resw = v->screen.screenw;
	v->screen.resh = v->screen.screenh;
	if (argc == 4 || argc == 5)
	{
		v->screen.resw = ft_atol(argv[argc - 2]);
		v->screen.resh = ft_atol(argv[argc - 1]);
		if (is_bad_res(v))
			exit((prterr(v, ERRRES, 1, 1), 1));
		if (!WSL && (v->screen.resw > v->screen.screenw
				|| v->screen.resh > v->screen.screenh
				|| v->screen.resw < 320 || v->screen.resh < 320))
			exit((prterr(v, "Resolution is bigger than your screen", 1, 1), 1));
	}
	initmainimage(v);
	v->screen.win = mlx_new_window(v->mlx, (int)v->screen.resw,
			(int)v->screen.resh, "CUB3D");
	if (!v->screen.win)
		exit((prterr(v, ERRMALL, 1, 1), 1));
	mouse_hide(v);
}
