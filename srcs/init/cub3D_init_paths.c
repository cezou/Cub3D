/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_init_paths.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:09:56 by pmagnero          #+#    #+#             */
/*   Updated: 2024/09/27 15:36:11 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

// void	initwallspath(t_vars *v)
// {
// 	// v->img[EWALL].filename = "resources/textures/Wall.xpm";
// }

void	initpathtext(t_vars *v)
{
	v->img[ESPACE].filename = "resources/textures/Ground.xpm";
	v->img[ESPACE].id = ESPACE;
	v->img[EDOOR].filename = "resources/textures/Door.xpm";
	v->img[EDOOR].id = EDOOR;
	v->img[EGUARD].filename = "resources/textures/general.xpm";
	v->img[EPLAYER].filename = "resources/textures/fist.xpm";
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

void	initplayerpathanim(t_vars *v)
{
	v->img[EFCK].width = v->img[EPLAYER].width / (v->screen.ratio) * 3;
	v->img[EFCK].height = v->img[EPLAYER].height / (v->screen.ratio) * 3;
	initimage(v, EFCK, v->img[EFCK].width, v->img[EFCK].height);
	scale_img((t_point){0}, &v->img[EPLAYER], &v->img[EFCK]);
	v->img[EPLAYER].anim[0].filename = "resources/textures/fist.xpm";
	v->img[EPLAYER].anim[0].animx = v->img[EPLAYER].width / 7
		* (1.0 / v->img[EFCK].ratiox);
}

void	initguardpathanim(t_vars *v)
{
	v->img[EGUARD].anim[0].filename = "resources/textures/general.xpm";
	v->img[EGUARD].anim[0].animx = v->img[EGUARD].height;
}

void	initprojectilepathanim(t_vars *v)
{
	(void)v;
}
