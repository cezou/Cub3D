/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_controls.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 18:24:52 by pmagnero          #+#    #+#             */
/*   Updated: 2024/04/05 18:13:58 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	free_shit(t_vars *v)
{
	if (v->mapv.map)
		map_clear(v->mapv.map);
	if (v->actors)
		actors_clear(v->actors);
	if (v->infos.map)
		freeall(v->infos.map);
	if (v->door)
		free(v->door);
	if (v->rand)
		free(v->rand);
}

void	hotreload_clear(t_vars *v, char *filename, char *ext)
{
	free_shit(v);
	v->player = (t_player){0};
	v->infos = (t_infos){0};
	v->mapv = (t_mapv){0};
	v->mapv.filename = filename;
	parsing(4, filename, v);
	parsing_csv(ext, v);
	v->door = NULL;
	v->last = NULL;
	v->rand = NULL;
	v->actors = NULL;
	v->hud = (t_hud){0};
	v->sp = (t_sprite_data){0};
	v->game = (t_game){0};
	v->game.start = 2;
	v->game.nb_actors = 0;
	v->game.ext = ext;
	v->player.animoff = 0;
	m_clearrandom(v);
	clearimgs(v);
}

void	hotreload(t_vars *v)
{
	char	*filename;
	char	*ext;

	filename = v->mapv.filename;
	ext = v->game.ext;
	hotreload_clear(v, filename, ext);
	initvars(v);
	initpathtext(v);
	inittextures(v, 4);
	v->game.skybox = v->img[ESKYBOX];
	inithud(v);
	initplayeranim(v);
	initweapon(v);
	initguardanim(v);
	check_map(v);
	init_player_dir(v);
	ma_sound_stop(&v->sound.sound[ECRED]);
	if (ACTIVATE_SOUND && !ma_sound_is_playing(&v->sound.sound[2]))
	{
		ma_sound_set_looping(&v->sound.sound[2], 1);
		ma_sound_start(&v->sound.sound[2]);
	}
	mlx_loop_end((ft_printf(1, "hotreload\n"), v->game.won = 0, v->mlx));
}
