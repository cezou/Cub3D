/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:14:07 by pmagnero          #+#    #+#             */
/*   Updated: 2024/04/05 12:19:12 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	getindex2(t_vars *v, t_map *tmp)
{
	(void)v;
	// if (tmp->val == WALL && tmp->y == 0 && tmp->x != 0
	// 	&& tmp->x != v->mapv.mapw - 1)
	// 	return (EWALL + myrand(4));
	// else if (tmp->val == WALL && tmp->y == v->mapv.maph - 1
	// 	&& tmp->x != 0 && tmp->x != v->mapv.mapw - 1)
	// 	return (EWALLD + myrand(4));
	// else if (tmp->val == WALL && tmp->x == 0
	// 	&& tmp->y != 0 && tmp->y != v->mapv.maph - 1)
	// 	return (EWALLL + myrand(4));
	// else if (tmp->val == WALL && tmp->x == v->mapv.mapw - 1
	// 	&& tmp->y != 0 && tmp->y != v->mapv.maph - 1)
	// 	return (EWALLR + myrand(4));
	// else if (tmp->val == WALL && tmp->x == 0 && tmp->y == 0)
	// 	return (EWALLCUL);
	// else if (tmp->val == WALL && tmp->x == v->mapv.mapw - 1 && tmp->y == 0)
	// 	return (EWALLCUR);
	// else if (tmp->val == WALL && tmp->x == 0 && tmp->y == v->mapv.maph - 1)
	// 	return (EWALLCDL);
	// else if (tmp->val == WALL && tmp->x == v->mapv.mapw - 1
	// 	&& tmp->y == v->mapv.maph - 1)
	// 	return (EWALLCDR);
	if (tmp->val == SPACE || tmp->val == COLLECT || tmp->val == EXIT
		|| tmp->val == SPAWN || tmp->val == GUARD)
		return (ESPACE + myrand(3));
	return (-1);
}

int	getindex(t_vars *v, int *i, t_map *tmp)
{
	(void)v;
	(void)tmp;
	// *i = getindex2(v, tmp);
	// if (*i >= 0)
	// 	return (1);
	// else if (tmp->val == WALL && tmp->x != 0 && tmp->x != v->mapv.mapw - 1
	// 	&& tmp->y != 0 && tmp->y != v->mapv.maph - 1 && tmp->left->val != WALL
	// 	&& tmp->right->val != WALL && tmp->down->val != WALL
	// 	&& tmp->up->val != WALL)
	// 	*i = EOBST1V1;
	// else if (tmp->val == WALL && tmp->x != 0 && tmp->x != v->mapv.mapw - 1
	// 	&& tmp->y != 0 && tmp->y != v->mapv.maph - 1 && tmp->left->val != WALL
	// 	&& tmp->right->val != WALL && tmp->down->val == WALL
	// 	&& tmp->down->down->val != WALL)
	// 	*i = EOBST1V2 + myrand(2);
	// else if (tmp->val == WALL && tmp->x != 0 && tmp->x != v->mapv.mapw - 1
	// 	&& tmp->y != 0 && tmp->y != v->mapv.maph - 1 && tmp->left->val != WALL
	// 	&& tmp->right->val != WALL && tmp->up->val == WALL && tmp->up->y != 0)
	// 	*i = -1;
	// else if (tmp->val == WALL && tmp->x != 0 && tmp->x != v->mapv.mapw - 1
	// 	&& tmp->y != 0 && tmp->y != v->mapv.maph - 1 && tmp->left->val != WALL
	// 	&& tmp->right->val != WALL && tmp->up->val == WALL && tmp->up->y == 0)
	// 	*i = EOBST1V1W;
	// else
	*i = EWALL;
	return (1);
}

void	displaytext(t_vars *v, char *str, char *str2)
{
	str = (char *)malloc(sizeof(char) * (20));
	if (!str)
		exit((cleardata(v, 1), showparams(v), 1));
	ft_bzero(str, 20);
	str2 = ft_itoa(v->player.pocket);
	ft_strlcat(str, str2, 20);
	free(str2);
	ft_strlcat(str, " / ", 20);
	str2 = ft_itoa(v->objs.collect);
	ft_strlcat(str, str2, 20);
	if (v->god)
	{
		mlx_string_put(v->mlx, v->screen.win, 50, 50, W_P, "[ESC] Exit");
		mlx_string_put(v->mlx, v->screen.win, 50, 70, W_P, "Zoom: Mouse wheel");
		mlx_string_put(v->mlx, v->screen.win, 50, 90, W_P, "Drag: Mouse");
		mlx_string_put(v->mlx, v->screen.win, 50, 110, W_P, "[r] Reset view");
		mlx_string_put(v->mlx, v->screen.win, 50, 170, W_P, "[F5] Hotreload");
		mlx_string_put(v->mlx, v->screen.win, 50, 190, W_P, "[F1] GOD mode");
	}
	mlx_string_put(v->mlx, v->screen.win, v->screen.resw * 0.90, 110, W_P, str);
	free(str2);
	str2 = ft_itoa(v->player.nbmove);
	mlx_string_put(v->mlx, v->screen.win, v->screen.resw * 0.80, 110, W_P,
		str2);
	free((free(str2), str));
}

void	guardmovements(t_vars *v)
{
	if (!MANDATORY && !v->game.pause && !v->game.won && v->guard.guard
		&& !v->guard.guardhit && !v->guard.guarddeath && timestamp_in_ms(v)
		- v->guard.timerguarddir >= (uint64_t)(50000 / v->game.fps))
	{
		v->guard.timerguarddir = timestamp_in_ms(v);
		v->guard.guarddir = NORTH + myrand(4);
		// if (v->guard.guarddir == NORTH)
		// 	movesvert((v->img[EGUARD].ydelta -= v->guard.movspeedguard,
		// 			v->guard.movingguard = 1, v), v->guard.guard->up,
		// 		(t_point){v->guard.movspeedguard, 0, 40, NORTH}, EGUARD);
		// if (v->guard.guarddir == SOUTH)
		// 	movesvert((v->img[EGUARD].ydelta += v->guard.movspeedguard,
		// 			v->guard.movingguard = 1, v), v->guard.guard->down,
		// 		(t_point){-v->guard.movspeedguard, 0, 40, SOUTH}, EGUARD);
		// if (v->guard.guarddir == WEST)
		// 	moveshor((v->img[EGUARD].xdelta -= v->guard.movspeedguard,
		// 			v->guard.movingguard = 1, v), v->guard.guard->left,
		// 		(t_point){v->guard.movspeedguard, 1, 80, WEST}, EGUARD);
		// if (v->guard.guarddir == EAST)
		// 	moveshor((v->img[EGUARD].xdelta += v->guard.movspeedguard,
		// 			v->guard.movingguard = 1, v), v->guard.guard->right,
		// 		(t_point){-v->guard.movspeedguard, 1, 40, EAST}, EGUARD);
		if (v->guard.guarddir == DIR_N)
			v->guard.movingguard = 0;
	}
}

int	render(t_vars *v)
{
	if (!v->screen.win || v->game.won > 0 || !v->game.start
		|| timestamp_in_ms(v) - v->game.updated_at < (uint64_t)(1000
			/ v->game.fps))
		return (1);
	v->game.updated_at = timestamp_in_ms(v);
	if (v->game.start == 2 && ACTIVATE_SOUND
		&& !ma_sound_is_playing(&v->sound.sound[2]))
	{
		ma_sound_stop(&v->sound.sound[0]);
		ma_sound_set_looping(&v->sound.sound[2], MA_TRUE);
		ma_sound_set_fade_start_in_milliseconds(&v->sound.sound[2], 0.0f, 0.8f,
			3000, 3000);
		ma_sound_start(&v->sound.sound[2]);
		mlx_loop_end(v->mlx);
	}
	if (v->game.start > 2)
		v->game.refreshmap = 0;
	if (v->game.refreshmap)
		ft_bzero((mlx_clear_window(v->mlx, v->screen.win), v->img[COMP_N].addr),
			v->screen.resw * v->screen.resh * (v->img[COMP_N].bpp / 8));
	raycasting(v);
	// displaytopdown((topdown((guardmovements(v), v), v->mapv.map, 7, 7), v));
	displaytopdown(v);
	mlx_put_image_to_window(v->mlx, v->screen.win, v->img[EMAP].img, 0, 0);
	return (displaytext(v, NULL, NULL), v->game.start++, 0);
}
// ft_bzero(v->img[EMAP].addr, v->resw * v->resh * (v->img[EMAP].bpp / 8));
