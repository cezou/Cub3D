/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_init_anim.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:09:56 by pmagnero          #+#    #+#             */
/*   Updated: 2024/09/11 15:33:09 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	initanim(t_vars *v, int ent, int d)
{
	v->img[ent].anim[d].xdelta = 0;
	v->img[ent].anim[d].ydelta = 0;
	v->img[ent].anim[d].posx = 0;
	v->img[ent].anim[d].posy = 0;
	v->img[ent].anim[d].animx = 0;
	v->img[ent].anim[d].animy = 0;
}

void	initprojectile(t_vars *v, int d)
{
	(void)v;
	d++;
	// v->img[EPROJ].animnb = DIR_N;
	// v->img[EPROJ].anim = (t_imga *)malloc(sizeof(t_imga) * (DIR_N));
	// if (!v->img[EPROJ].anim)
	// 	exit((prterr(v, ERRMALL, 1, 1), 1));
	// initprojectilepathanim(v);
	// while (++d < v->img[EPROJ].animnb)
	// {
	// 	v->img[EPROJ].anim[d].img = mlx_xpm_file_to_image(v->mlx,
	// 			v->img[EPROJ].anim[d].filename,
	// 			&v->img[EPROJ].anim[d].width,
	// 			&v->img[EPROJ].anim[d].height);
	// 	if (!v->img[EPROJ].anim[d].img)
	// 		exit((prterr(v, "Error mlx texture proj anim image\n", 1, 1), 1));
	// 	v->img[EPROJ].anim[d].addr
	// 		= mlx_get_data_addr(v->img[EPROJ].anim[d].img,
	// 			&v->img[EPROJ].anim[d].bpp,
	// 			&v->img[EPROJ].anim[d].len,
	// 			&v->img[EPROJ].anim[d].endian);
	// 	if (!v->img[EPROJ].anim[d].addr)
	// 		exit((prterr(v, "Error mlx text anim proj img addr\n", 1, 1), 1));
	// 	initanim(v, EPROJ, d);
	// }
}

void	initplayeranim(t_vars *v, int d)
{
	(void)v;
	d++;
	// v->img[ESPAWN].animnb = DIR_N * ANIM_N;
	// v->img[ESPAWN].anim = (t_imga *)malloc(sizeof(t_imga) * (DIR_N * ANIM_N));
	// if (!v->img[ESPAWN].anim)
	// 	exit((prterr(v, ERRMALL, 1, 1), 1));
	// initplayerpathanim(v);
	// initprojectile(v, -1);
	// while (++d < v->img[ESPAWN].animnb)
	// {
	// 	v->img[ESPAWN].anim[d].img = mlx_xpm_file_to_image(v->mlx,
	// 			v->img[ESPAWN].anim[d].filename,
	// 			&v->img[ESPAWN].anim[d].width,
	// 			&v->img[ESPAWN].anim[d].height);
	// 	if (!v->img[ESPAWN].anim[d].img)
	// 		exit((prterr(v, "Error mlx texture anim image\n", 1, 1), 1));
	// 	v->img[ESPAWN].anim[d].addr
	// 		= mlx_get_data_addr(v->img[ESPAWN].anim[d].img,
	// 			&v->img[ESPAWN].anim[d].bpp, &v->img[ESPAWN].anim[d].len,
	// 			&v->img[ESPAWN].anim[d].endian);
	// 	if (!v->img[ESPAWN].anim[d].addr)
	// 		exit((prterr(v, "Error mlx text anim img addr\n", 1, 1), 1));
	// 	initanim(v, ESPAWN, d);
	// }
}

void	initguardanim(t_vars *v, int d)
{
	(void)v;
	d++;
	// v->img[EGUARD].anim = (t_imga *)malloc(sizeof(t_imga) * (6));
	// if (!v->img[EGUARD].anim)
	// 	exit((prterr(v, ERRMALL, 1, 1), 1));
	// v->img[EGUARD].animnb = 6;
	// v->img[EGUARD].anim[0].filename = "resources/textures/CthululuWalk.xpm";
	// v->img[EGUARD].anim[1].filename = "resources/textures/CthululuWalkLeft.xpm";
	// v->img[EGUARD].anim[2].filename = "resources/textures/CthululuHitRight.xpm";
	// v->img[EGUARD].anim[3].filename = "resources/textures/CthululuHitLeft.xpm";
	// v->img[EGUARD].anim[4].filename = "resources/textures/CthululuDeathR.xpm";
	// v->img[EGUARD].anim[5].filename = "resources/textures/CthululuDeathL.xpm";
	// while (++d < 6)
	// {
	// 	v->img[EGUARD].anim[d].img = mlx_xpm_file_to_image(v->mlx,
	// 			v->img[EGUARD].anim[d].filename, &v->img[EGUARD].anim[d].width,
	// 			&v->img[EGUARD].anim[d].height);
	// 	if (!v->img[EGUARD].anim[d].img)
	// 		exit((prterr(v, "Error mlx texture anim image\n", 1, 1), 1));
	// 	v->img[EGUARD].anim[d].addr
	// 		= mlx_get_data_addr(v->img[EGUARD].anim[d].img,
	// 			&v->img[EGUARD].anim[d].bpp, &v->img[EGUARD].anim[d].len,
	// 			&v->img[EGUARD].anim[d].endian);
	// 	if (!v->img[EGUARD].anim[d].addr)
	// 		exit((prterr(v, "Error mlx texture anim image address\n", 1, 1), 1));
	// 	initanim(v, EGUARD, d);
	// }
}

void	initobjectsanim(t_vars *v, int d, int obj)
{
	v->img[obj].anim = (t_imga *)malloc(sizeof(t_imga) * (1));
	if (!v->img[obj].anim)
		exit((prterr(v, ERRMALL, 1, 1), 1));
	v->img[obj].animnb = 1;
	v->img[obj].anim[NORTH].filename = "resources/textures/Star2.xpm";
	v->img[obj].anim[d].img = mlx_xpm_file_to_image(v->mlx,
			v->img[obj].anim[d].filename, &v->img[obj].anim[d].width,
			&v->img[obj].anim[d].height);
	if (!v->img[obj].anim[d].img)
		exit((prterr(v, "Error mlx texture anim image\n", 1, 1), 1));
	v->img[obj].anim[d].addr = mlx_get_data_addr(v->img[obj].anim[d].img,
			&v->img[obj].anim[d].bpp, &v->img[obj].anim[d].len,
			&v->img[obj].anim[d].endian);
	if (!v->img[obj].anim[d].addr)
		exit((prterr(v, "Error mlx texture anim image address\n", 1, 1), 1));
	initanim(v, obj, d);
}
