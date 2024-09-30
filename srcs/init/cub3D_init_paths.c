/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_init_paths.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:09:56 by pmagnero          #+#    #+#             */
/*   Updated: 2024/09/30 17:52:06 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	initpathtext(t_vars *v)
{
	v->img[ESPACE].filename = "resources/textures/Ground.xpm";
	v->img[ESPACE].id = ESPACE;
	v->img[EDOOR].filename = "resources/textures/Door.xpm";
	v->img[EDOOR].id = EDOOR;
	v->img[EGUARDW].filename = "resources/textures/general.xpm";
	v->img[EGUARDDEATH].filename = "resources/textures/generaldeath.xpm";
	v->img[ESKYBOX].filename = "resources/textures/skybox.xpm";
	v->img[EHUDIMG].filename = "resources/textures/HUD.xpm";
	v->img[ETITLE].filename = "resources/textures/title.xpm";
	v->img[EMENUSELECT].filename = "resources/textures/menus/select.xpm";
	v->img[EMENU].filename = "resources/textures/menus/menu_start.xpm";
	v->img[EMENUIG].filename = "resources/textures/menus/menu_ingame.xpm";
	v->img[EMENUOPT].filename = "resources/textures/menus/menu_options.xpm";
	v->img[EKEK].filename = "resources/textures/DoomTitle.xpm";
	v->img[EDOOMH].filename = "resources/textures/Doomhead.xpm";
}

void	initanim(t_vars *v, int index, int b, int animnb)
{
	v->img[ETMP].filename = v->img[index].filename;
	inittexture(v, &v->img[ETMP]);
	v->img[index].width = v->img[ETMP].width / (v->screen.ratio) * 3;
	v->img[index].height = v->img[ETMP].height / (v->screen.ratio) * 3;
	initimage(v, index, v->img[index].width, v->img[index].height);
	scale_img((t_point){0}, &v->img[ETMP], &v->img[index]);
	v->img[index].animx = v->img[ETMP].width / animnb
		* (1.0 / v->img[index].ratiox);
	if (b)
		mlx_destroy_image(v->mlx, v->img[ETMP].img);
}

void	initplayerpathanim(t_vars *v)
{
	v->img[EFIST].filename = "resources/textures/fist.xpm";
	initanim(v, EFIST, 1, 7);
	v->player.img = v->img[EFIST];
	v->img[EGUN].filename = "resources/textures/gun.xpm";
	initanim(v, EGUN, 0, 7);
}

void	initguardpathanim(t_vars *v)
{
	v->img[EGUARDW].animx = v->img[EGUARDW].height;
	v->img[EGUARDDEATH].animx = v->img[EGUARDDEATH].height;
}

void	initprojectilepathanim(t_vars *v)
{
	(void)v;
}
