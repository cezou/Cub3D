/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:37:59 by pmagnero          #+#    #+#             */
/*   Updated: 2024/04/05 23:35:47 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	freeall(char **tab)
{
	int	i;

	i = -1;
	if (!tab)
		return ;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

int	map_clear(t_map *lst)
{
	t_map	*temp;

	if (!lst)
		return (1);
	while (lst)
	{
		temp = (lst)->right;
		free(lst);
		lst = temp;
	}
	return (1);
}

int	clearimgs(t_vars *v)
{
	int	i;
	int	j;

	i = -1;
	while (v->img && ++i <= COMP_N)
	{
		j = -1;
		if (v->img[EMAP].img && v->img[i].img)
		{
			while (v->img[i].anim && ++j < v->img[i].animnb)
			{
				if (v->img[i].anim[j].img && mlx_destroy_image(v->mlx,
						v->img[i].anim[j].img) < 0)
					return (ft_printf(2, "ERROR Destroy Anim Image\n"), -1);
			}
			free(v->img[i].anim);
			if (mlx_destroy_image(v->mlx, v->img[i].img) < 0)
				return (ft_printf(2, "ERROR Destroy Image\n"), -1);
		}
	}
	return (1);
}

int	clear_sounds(t_vars *v)
{
	int	i;

	i = -1;
	if (!ACTIVATE_SOUND || !v->sound.init)
		return (0);
	while (++i < SOUND_NB)
	{
		v->sound.result = ma_sound_stop_with_fade_in_pcm_frames(&v->sound.sound[i],
				2);
		if (v->sound.result != MA_SUCCESS)
			exit((prterr(v, "Clear stop fade sound failed\n", 1, 1), 1));
		ma_sound_uninit(&v->sound.sound[i]);
	}
	v->sound.result = ma_engine_stop(&v->sound.engine);
	if (v->sound.result != MA_SUCCESS)
		exit((prterr(v, "Engine stop failed\n", 1, 1), 1));
	ma_engine_uninit(&v->sound.engine);
	return (1);
}

int	cleardata(t_vars *v, int b)
{
	clear_sounds(v);
	if (b && v->mlx && (clearimgs(v) < 0 || (v->screen.win
				&& mlx_destroy_window(v->mlx, v->screen.win) < 0)
			|| mlx_destroy_display(v->mlx) < 0))
		return (ft_printf(2, "ERROR Destroy Imgs/Win/Disp\n"), 1);
	if (v->mapv.map && map_clear(v->mapv.map) < 0)
		return (ft_printf(2, "ERROR Destroy Map\n"));
	if (b && v->mlx)
	{
		free(v->mlx);
	}
	if (v->img)
		free(v->img);
	if (v->objs.objs)
		free(v->objs.objs);
	return (0);
}
