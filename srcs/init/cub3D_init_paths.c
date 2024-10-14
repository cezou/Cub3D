/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_init_paths.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:09:56 by pmagnero          #+#    #+#             */
/*   Updated: 2024/10/14 18:09:40 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	initpath2(t_vars *v)
{
	v->img[ESPACE].filename = "resources/textures/Ground.xpm";
	v->img[EDOOR].filename = "resources/textures/Door.xpm";
	v->img[EPARMOR].filename = "resources/textures/armor.xpm";
	v->img[EPARMOR1].filename = "resources/textures/armor1.xpm";
	v->img[ESTIM].filename = "resources/textures/stimpack.xpm";
	v->img[EMEDI].filename = "resources/textures/medikit.xpm";
	v->img[EPCLIP].filename = "resources/textures/clip.xpm";
	v->img[EPSHELL].filename = "resources/textures/shells.xpm";
	v->img[EPROCK].filename = "resources/textures/rocket.xpm";
	v->img[EPCELL].filename = "resources/textures/cells.xpm";
	v->img[EBKEY].filename = "resources/textures/bluekey.xpm";
	v->img[EBSKEY].filename = "resources/textures/blueskull.xpm";
	v->img[EYKEY].filename = "resources/textures/yellowkey.xpm";
	v->img[EYSKEY].filename = "resources/textures/yellowskull.xpm";
	v->img[ERKEY].filename = "resources/textures/redkey.xpm";
	v->img[ERSKEY].filename = "resources/textures/redskull.xpm";
	v->img[EGUARDW].filename = "resources/textures/general.xpm";
	v->img[EGUARDDEATH].filename = "resources/textures/generaldeath.xpm";
	v->img[EGUARDATTR].filename = "resources/textures/generalattackrange.xpm";
	v->img[ESKYBOX].filename = "resources/textures/skybox.xpm";
	v->img[EHUDIMG].filename = "resources/textures/HUDempty.xpm";
	v->img[EMAPBORDER].filename = "resources/textures/MapBorder.xpm";
	v->img[EMAPHEAD].filename = "resources/textures/MapHead.xpm";
	v->img[ETITLE].filename = "resources/textures/title.xpm";
}

void	initpathtext(t_vars *v)
{
	initpath2(v);
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
	v->img[EPBFG].filename = "resources/textures/pbfg.xpm";
	v->img[EPSHOTGUN].filename = "resources/textures/pshotgun.xpm";
	v->img[EPGATLIN].filename = "resources/textures/pgatlin.xpm";
	v->img[EPROCKETL].filename = "resources/textures/procketl.xpm";
	v->img[EPPLASMA].filename = "resources/textures/pplasma.xpm";
	v->img[EPCHAINSAW].filename = "resources/textures/pchainsaw.xpm";
	v->img[EPSUPERSHOTGUN].filename = "resources/textures/psupershotgun.xpm";
	v->img[EPLASMABOLT].filename = "resources/textures/plasmabolt.xpm";
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
	v->img[EIFIST].filename = "resources/textures/fist.xpm";
	initanim(v, EIFIST, 1, 7);
	v->player.currweapon.img = v->img[EIFIST];
	v->img[EIGUN].filename = "resources/textures/gun.xpm";
	initanim(v, EIGUN, 1, 7);
	v->img[EISHOTGUN].filename = "resources/textures/shotgun.xpm";
	initanim(v, EISHOTGUN, 1, 8);
	v->img[EIGATLIN].filename = "resources/textures/gatlin.xpm";
	initanim(v, EIGATLIN, 1, 3);
	v->img[EIROCKl].filename = "resources/textures/rocketl.xpm";
	initanim(v, EIROCKl, 1, 6);
	v->img[EIPLASMA].filename = "resources/textures/plasma.xpm";
	initanim(v, EIPLASMA, 1, 4);
	v->img[EICHAINSAW].filename = "resources/textures/chainsaw.xpm";
	initanim(v, EICHAINSAW, 1, 4);
	v->img[EISUPERSHOTGUN].filename = "resources/textures/supershotgun.xpm";
	initanim(v, EISUPERSHOTGUN, 1, 10);
	v->img[EIBFG].filename = "resources/textures/bfg.xpm";
	initanim(v, EIBFG, 0, 4);
}

void	initguardpathanim(t_vars *v)
{
	v->img[EGUARDW].animx = v->img[EGUARDW].width / 4;
	v->img[EGUARDDEATH].animx = v->img[EGUARDDEATH].width / 4;
	v->img[EGUARDATTR].animx = v->img[EGUARDATTR].width / 4;
}

// void	initprojectilepathanim(t_vars *v)
// {
// 	(void)v;
// }
