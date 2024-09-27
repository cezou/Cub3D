/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_init_anim.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:09:56 by pmagnero          #+#    #+#             */
/*   Updated: 2024/09/27 15:39:36 by pmagnero         ###   ########.fr       */
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

void	initplayeranim(t_vars *v, int d)
{
	v->img[EPLAYER].animnb = 1;
	v->img[EPLAYER].anim = (t_imga *)malloc(sizeof(t_imga) * 1);
	if (!v->img[EPLAYER].anim)
		exit((prterr(v, ERRMALL, 1, 1), 1));
	initplayerpathanim(v);
	while (++d < v->img[EPLAYER].animnb)
	{
		v->img[EPLAYER].anim[d].img = mlx_xpm_file_to_image(v->mlx,
				v->img[EPLAYER].anim[d].filename,
				&v->img[EPLAYER].anim[d].width,
				&v->img[EPLAYER].anim[d].height);
		if (!v->img[EPLAYER].anim[d].img)
			exit((prterr(v, "Error mlx texture anim image\n", 1, 1), 1));
		v->img[EPLAYER].anim[d].addr
			= mlx_get_data_addr(v->img[EPLAYER].anim[d].img,
				&v->img[EPLAYER].anim[d].bpp, &v->img[EPLAYER].anim[d].len,
				&v->img[EPLAYER].anim[d].endian);
		if (!v->img[EPLAYER].anim[d].addr)
			exit((prterr(v, "Error mlx text anim img addr\n", 1, 1), 1));
	}
}

void	initguardanim(t_vars *v, int d)
{
	v->img[EGUARD].animnb = 1;
	v->img[EGUARD].anim = (t_imga *)malloc(sizeof(t_imga) * (1));
	if (!v->img[EGUARD].anim)
		exit((prterr(v, ERRMALL, 1, 1), 1));
	initguardpathanim(v);
	while (++d < v->img[EGUARD].animnb)
	{
		v->img[EGUARD].anim[d].img = mlx_xpm_file_to_image(v->mlx,
				v->img[EGUARD].anim[d].filename, &v->img[EGUARD].anim[d].width,
				&v->img[EGUARD].anim[d].height);
		if (!v->img[EGUARD].anim[d].img)
			exit((prterr(v, "Error mlx texture anim image\n", 1, 1), 1));
		v->img[EGUARD].anim[d].addr
			= mlx_get_data_addr(v->img[EGUARD].anim[d].img,
				&v->img[EGUARD].anim[d].bpp, &v->img[EGUARD].anim[d].len,
				&v->img[EGUARD].anim[d].endian);
		if (!v->img[EGUARD].anim[d].addr)
			exit((prterr(v, "Error mlx texture anim image address\n", 1, 1), 1));
	}
}

void	inithud(t_vars *v)
{
	v->img[EHUD].width = v->screen.hudw;
	v->img[EHUD].height = v->screen.hudh;
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
}

// void	initobjectsanim(t_vars *v, int d, int obj)
// {
// 	v->img[obj].anim = (t_imga *)malloc(sizeof(t_imga) * (1));
// 	if (!v->img[obj].anim)
// 		exit((prterr(v, ERRMALL, 1, 1), 1));
// 	v->img[obj].animnb = 1;
// 	v->img[obj].anim[NORTH].filename = "resources/textures/Star2.xpm";
// 	v->img[obj].anim[d].img = mlx_xpm_file_to_image(v->mlx,
// 			v->img[obj].anim[d].filename, &v->img[obj].anim[d].width,
// 			&v->img[obj].anim[d].height);
// 	if (!v->img[obj].anim[d].img)
// 		exit((prterr(v, "Error mlx texture anim image\n", 1, 1), 1));
// 	v->img[obj].anim[d].addr = mlx_get_data_addr(v->img[obj].anim[d].img,
// 			&v->img[obj].anim[d].bpp, &v->img[obj].anim[d].len,
// 			&v->img[obj].anim[d].endian);
// 	if (!v->img[obj].anim[d].addr)
// 		exit((prterr(v, "Error mlx texture anim image address\n", 1, 1), 1));
// 	initanim(v, obj, d);
// }
