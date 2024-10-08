/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_init_sounds.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:09:56 by pmagnero          #+#    #+#             */
/*   Updated: 2024/10/08 19:34:12 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void	initsounds2(t_vars *v)
{
	v->sound.result = ma_sound_init_from_file(&v->sound.engine, SOUND_GENERIC,
			MA_SOUND_FLAG_STREAM, NULL, NULL, &v->sound.sound[EGENERIC]);
	if (v->sound.result != MA_SUCCESS)
		exit((prterr(v, "KEKAUDIO2\n", 1, 1), 1));
	v->sound.result = ma_sound_init_from_file(&v->sound.engine,
			SOUND_FOOTSTEPWALK, MA_SOUND_FLAG_DECODE, NULL, NULL,
			&v->sound.sound[EFOOTWALK]);
	if (v->sound.result != MA_SUCCESS)
		exit((prterr(v, "KEKAUDIO3\n", 1, 1), 1));
	v->sound.result = ma_sound_init_from_file(&v->sound.engine, SOUND_AMBIENT,
			MA_SOUND_FLAG_STREAM, NULL, NULL, &v->sound.sound[EAMBIENT]);
	if (v->sound.result != MA_SUCCESS)
		exit((prterr(v, "KEKAUDIO4\n", 1, 1), 1));
	v->sound.result = ma_sound_init_from_file(&v->sound.engine,
			SOUND_BABYLAUGH1, MA_SOUND_FLAG_DECODE, NULL, NULL,
			&v->sound.sound[EBABY1]);
	if (v->sound.result != MA_SUCCESS)
		exit((prterr(v, "KEKAUDIO5\n", 1, 1), 1));
	v->sound.result = ma_sound_init_from_file(&v->sound.engine,
			SOUND_BABYLAUGH2, MA_SOUND_FLAG_DECODE, NULL, NULL,
			&v->sound.sound[EBABY2]);
	if (v->sound.result != MA_SUCCESS)
		exit((prterr(v, "KEKAUDIO6\n", 1, 1), 1));
}

static void	initsounds3(t_vars *v)
{
	v->sound.result = ma_sound_init_from_file(&v->sound.engine,
			SOUND_GUARDINJURED, MA_SOUND_FLAG_DECODE, NULL, NULL,
			&v->sound.sound[EGUARDI]);
	if (v->sound.result != MA_SUCCESS)
		exit((prterr(v, "KEKAUDIO7\n", 1, 1), 1));
	v->sound.result = ma_sound_init_from_file(&v->sound.engine,
			SOUND_GUARDDEATH, MA_SOUND_FLAG_DECODE, NULL, NULL,
			&v->sound.sound[EGUARDD]);
	if (v->sound.result != MA_SUCCESS)
		exit((prterr(v, "KEKAUDIO7\n", 1, 1), 1));
	v->sound.result = ma_sound_init_from_file(&v->sound.engine,
			SOUND_ATTACK, MA_SOUND_FLAG_DECODE, NULL, NULL,
			&v->sound.sound[EATT]);
	if (v->sound.result != MA_SUCCESS)
		exit((prterr(v, "KEKAUDIO7\n", 1, 1), 1));
	v->sound.result = ma_sound_init_from_file(&v->sound.engine,
			SOUND_CREDITS, MA_SOUND_FLAG_STREAM, NULL, NULL,
			&v->sound.sound[ECRED]);
	if (v->sound.result != MA_SUCCESS)
		exit((prterr(v, "ECRED\n", 1, 1), 1));
	v->sound.result = ma_sound_init_from_file(&v->sound.engine,
			SOUND_GAMEOVER, MA_SOUND_FLAG_STREAM, NULL, NULL,
			&v->sound.sound[ELOSE]);
	if (v->sound.result != MA_SUCCESS)
		exit((prterr(v, "ELOSE\n", 1, 1), 1));
}

static void	initsounds4(t_vars *v)
{
	v->sound.result = ma_sound_init_from_file(&v->sound.engine,
			SOUND_WIN, MA_SOUND_FLAG_DECODE, NULL, NULL,
			&v->sound.sound[EWIN]);
	if (v->sound.result != MA_SUCCESS)
		exit((prterr(v, "EWIN\n", 1, 1), 1));
}

void	initsounds(t_vars *v)
{
	if (!ACTIVATE_SOUND)
		return ;
	v->sound.result = ma_engine_init(NULL, &v->sound.engine);
	if (v->sound.result != MA_SUCCESS)
		exit((prterr(v, "KEKAUDIO1\n", 1, 1), 1));
	initsounds2(v);
	initsounds3(v);
	initsounds4(v);
	v->sound.result = ma_sound_init_from_file(&v->sound.engine,
			SOUND_BABYLAUGH3, MA_SOUND_FLAG_DECODE, NULL, NULL,
			&v->sound.sound[EBABY3]);
	if (v->sound.result != MA_SUCCESS)
		exit((prterr(v, "KEKAUDIO7\n", 1, 1), 1));
	v->sound.result = ma_sound_init_from_file(&v->sound.engine,
			SOUND_BUTTONCLICK1, MA_SOUND_FLAG_DECODE, NULL, NULL,
			&v->sound.sound[EBUTTC1]);
	if (v->sound.result != MA_SUCCESS)
		exit((prterr(v, "KEKAUDIO7\n", 1, 1), 1));
	v->sound.result = ma_sound_init_from_file(&v->sound.engine,
			SOUND_BUTTONCLICK2, MA_SOUND_FLAG_DECODE, NULL, NULL,
			&v->sound.sound[EBUTTC2]);
	if (v->sound.result != MA_SUCCESS)
		exit((prterr(v, "KEKAUDIO7\n", 1, 1), 1));
	v->sound.init = 1;
	v->sound.volume = 1.0f;
}
