/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_init_paths.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:09:56 by pmagnero          #+#    #+#             */
/*   Updated: 2024/10/04 13:35:25 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	initpathtext(t_vars *v)
{
	v->img[ESPACE].filename = "resources/textures/Ground.xpm";
	v->img[EDOOR].filename = "resources/textures/Door.xpm";
	v->img[EPARMOR].filename = "resources/textures/armor.xpm";
	v->img[EGUARDW].filename = "resources/textures/general.xpm";
	v->img[EGUARDDEATH].filename = "resources/textures/generaldeath.xpm";
	v->img[ESKYBOX].filename = "resources/textures/skybox.xpm";
	v->img[EHUDIMG].filename = "resources/textures/HUDempty.xpm";
	v->img[EMAPBORDER].filename = "resources/textures/MapBorder.xpm";
	v->img[EMAPHEAD].filename = "resources/textures/MapHead.xpm";
	v->img[ETITLE].filename = "resources/textures/title.xpm";
	v->img[EMENUSELECT].filename = "resources/textures/menus/select.xpm";
	v->img[EMENU].filename = "resources/textures/menus/menu_start.xpm";
	v->img[EMENUIG].filename = "resources/textures/menus/menu_ingame.xpm";
	v->img[EMENUOPT].filename = "resources/textures/menus/menu_options.xpm";
	v->img[EKEK].filename = "resources/textures/DoomTitle.xpm";
	v->img[EDOOMH].filename = "resources/textures/Doomhead.xpm";
	v->img[EBIGNUMBERSTMP].filename = "resources/textures/BigRedNumbers.xpm";
	v->img[ESMALLNUMBERSTMP].filename = "resources/textures/SmallNumbers.xpm";
	v->img[EHEALTHTMP].filename = "resources/textures/Health.xpm";
	v->img[EARMORTMP].filename = "resources/textures/Armor.xpm";
	v->img[EAMMOTMP].filename = "resources/textures/Ammo.xpm";
	v->img[EWEAPONTMP].filename = "resources/textures/Arms.xpm";
	v->img[EAMMUNTMP].filename = "resources/textures/Ammunitions.xpm";
	v->img[ECARDSTMP].filename = "resources/textures/Cards.xpm";
	v->img[ECARDSLOTTMP].filename = "resources/textures/CardsSlot.xpm";
}

void	initanim(t_vars *v, int index, int b, int animnb)
{
	double	factorx;
	double	factory;
	double	scalefactor;

	factorx = (double)v->screen.gamew / 800;
	factory = (double)v->screen.gameh / 600;
	scalefactor = factorx;
	if (factorx >= factory)
		scalefactor = factory;
	v->img[ETMP].filename = v->img[index].filename;
	inittexture(v, &v->img[ETMP], ETMP);
	v->img[index].width = scalefactor * v->img[ETMP].width * 3;
	v->img[index].height = scalefactor * v->img[ETMP].height * 3;
	initimage(v, index, v->img[index].width, v->img[index].height);
	scale_img((t_point){0}, &v->img[ETMP], &v->img[index]);
	v->img[index].animx = v->img[ETMP].width / animnb * (1.0
			/ v->img[index].ratiox);
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
	v->img[EGUARDW].animx = v->img[EGUARDW].width / 4;
	v->img[EGUARDDEATH].animx = v->img[EGUARDDEATH].width / 4;
}

void	initprojectilepathanim(t_vars *v)
{
	(void)v;
}
