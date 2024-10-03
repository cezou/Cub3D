/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_init_anim.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:09:56 by pmagnero          #+#    #+#             */
/*   Updated: 2024/10/03 19:38:17 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

// void	initprojectile(t_vars *v, int d)
// {
// 	(void)v;
// 	d++;
// 	// v->img[EPROJ].animnb = DIR_N;
// 	// v->img[EPROJ].anim = (t_imga *)malloc(sizeof(t_imga) * (DIR_N));
// 	// if (!v->img[EPROJ].anim)
// 	// 	exit((prterr(v, ERRMALL, 1, 1), 1));
// 	// initprojectilepathanim(v);
// 	// while (++d < v->img[EPROJ].animnb)
// 	// {
// 	// 	v->img[EPROJ].anim[d].img = mlx_xpm_file_to_image(v->mlx,
// 	// 			v->img[EPROJ].anim[d].filename,
// 	// 			&v->img[EPROJ].anim[d].width,
// 	// 			&v->img[EPROJ].anim[d].height);
// 	// 	if (!v->img[EPROJ].anim[d].img)
// 	// 		exit((prterr(v, "Error mlx texture proj anim image\n", 1, 1), 1));
// 	// 	v->img[EPROJ].anim[d].addr
// 	// 		= mlx_get_data_addr(v->img[EPROJ].anim[d].img,
// 	// 			&v->img[EPROJ].anim[d].bpp,
// 	// 			&v->img[EPROJ].anim[d].len,
// 	// 			&v->img[EPROJ].anim[d].endian);
// 	// 	if (!v->img[EPROJ].anim[d].addr)
// 	// 		exit((prterr(v, "Error mlx text anim proj img addr\n", 1, 1), 1));
// 	// 	initanim(v, EPROJ, d);
// 	// }
// }

void	initplayeranim(t_vars *v)
{
	initplayerpathanim(v);
}

void	initguardanim(t_vars *v)
{
	initguardpathanim(v);
}

void	inithud(t_vars *v)
{
	v->img[EHUD].width = v->screen.hudw;
	v->img[EHUD].height = v->screen.hudh;
	v->img[EHUD].id = EHUD;
	v->img[EHUDTMP].width = v->screen.hudw;
	v->img[EHUDTMP].height = v->screen.hudh;
	initimage(v, EHUD, v->screen.hudw, v->screen.hudh);
	initimage(v, EHUDTMP, v->screen.hudw, v->screen.hudh);
	scale_img((t_point){0}, &v->img[EHUDIMG], &v->img[EHUDTMP]);
	v->hud.img = v->img[EHUDTMP];
	v->img[EDOOMHTMP].width = v->img[EDOOMH].width / v->img[EHUDTMP].ratiox;
	v->img[EDOOMHTMP].height = v->img[EDOOMH].height / v->img[EHUDTMP].ratioy;
	initimage(v, EDOOMHTMP, v->img[EDOOMHTMP].width, v->img[EDOOMHTMP].height);
	scale_img((t_point){0}, &v->img[EDOOMH], &v->img[EDOOMHTMP]);
	v->img[EDOOMHTMP].animx = v->img[EDOOMHTMP].width / 3;
	v->hud.head = v->img[EDOOMHTMP];
	v->hud.headid = v->img[EDOOMHTMP].animx;
	v->hud.animoff = v->img[EDOOMHTMP].animx;
	v->img[EBIGNUMBERS].width = v->img[EBIGNUMBERSTMP].width / v->img[EHUDTMP].ratiox;
	v->img[EBIGNUMBERS].height = v->img[EBIGNUMBERSTMP].height / v->img[EHUDTMP].ratioy;
	initimage(v, EBIGNUMBERS, v->img[EBIGNUMBERS].width, v->img[EBIGNUMBERS].height);
	scale_img((t_point){0}, &v->img[EBIGNUMBERSTMP], &v->img[EBIGNUMBERS]);
	v->img[EBIGNUMBERS].animx = v->img[EBIGNUMBERS].width / 12;
	v->img[ESMALLNUMBERS].width = v->img[ESMALLNUMBERSTMP].width / v->img[EHUDTMP].ratiox;
	v->img[ESMALLNUMBERS].height = v->img[ESMALLNUMBERSTMP].height / v->img[EHUDTMP].ratioy;
	initimage(v, ESMALLNUMBERS, v->img[ESMALLNUMBERS].width, v->img[ESMALLNUMBERS].height);
	scale_img((t_point){0}, &v->img[ESMALLNUMBERSTMP], &v->img[ESMALLNUMBERS]);
	v->img[ESMALLNUMBERS].animx = v->img[ESMALLNUMBERS].width / 10;
	v->img[ESMALLNUMBERS].animy = v->img[ESMALLNUMBERS].height / 2;
	v->img[EHEALTH].width = v->img[EHEALTHTMP].width / v->img[EHUDTMP].ratiox;
	v->img[EHEALTH].height = v->img[EHEALTHTMP].height / v->img[EHUDTMP].ratioy;
	initimage(v, EHEALTH, v->img[EHEALTH].width, v->img[EHEALTH].height);
	scale_img((t_point){0}, &v->img[EHEALTHTMP], &v->img[EHEALTH]);
	v->img[EHEALTH].animx = 0;
	v->img[EARMOR].width = v->img[EARMORTMP].width / v->img[EHUDTMP].ratiox;
	v->img[EARMOR].height = v->img[EARMORTMP].height / v->img[EHUDTMP].ratioy;
	initimage(v, EARMOR, v->img[EARMOR].width, v->img[EARMOR].height);
	scale_img((t_point){0}, &v->img[EARMORTMP], &v->img[EARMOR]);
	v->img[EARMOR].animx = 0;
	v->img[EAMMO].width = v->img[EAMMOTMP].width / v->img[EHUDTMP].ratiox;
	v->img[EAMMO].height = v->img[EAMMOTMP].height / v->img[EHUDTMP].ratioy;
	initimage(v, EAMMO, v->img[EAMMO].width, v->img[EAMMO].height);
	scale_img((t_point){0}, &v->img[EAMMOTMP], &v->img[EAMMO]);
	v->img[EAMMO].animx = 0;
	v->img[EWEAPON].width = v->img[EWEAPONTMP].width / v->img[EHUDTMP].ratiox;
	v->img[EWEAPON].height = v->img[EWEAPONTMP].height / v->img[EHUDTMP].ratioy;
	initimage(v, EWEAPON, v->img[EWEAPON].width, v->img[EWEAPON].height);
	scale_img((t_point){0}, &v->img[EWEAPONTMP], &v->img[EWEAPON]);
	v->img[EWEAPON].animx = 0;
	v->img[EAMMUN].width = v->img[EAMMUNTMP].width / v->img[EHUDTMP].ratiox;
	v->img[EAMMUN].height = v->img[EAMMUNTMP].height / v->img[EHUDTMP].ratioy;
	initimage(v, EAMMUN, v->img[EAMMUN].width, v->img[EAMMUN].height);
	scale_img((t_point){0}, &v->img[EAMMUNTMP], &v->img[EAMMUN]);
	v->img[EAMMUN].animx = 0;
}
