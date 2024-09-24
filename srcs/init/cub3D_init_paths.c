/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_init_paths.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:09:56 by pmagnero          #+#    #+#             */
/*   Updated: 2024/09/24 05:47:43 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	initwallspath(t_vars *v)
{
	// (void)v;
	v->img[EWALL].filename = "resources/textures/Wall.xpm";
	// v->img[EWALL2].filename = "resources/textures/Wall2.xpm";
	// v->img[EWALL3].filename = "resources/textures/Wall3.xpm";
	// v->img[EWALL4].filename = "resources/textures/Wall4.xpm";
	// v->img[EWALLD].filename = "resources/textures/WallD.xpm";
	// v->img[EWALLD2].filename = "resources/textures/WallD2.xpm";
	// v->img[EWALLD3].filename = "resources/textures/WallD3.xpm";
	// v->img[EWALLD4].filename = "resources/textures/WallD4.xpm";
	// v->img[EWALLL].filename = "resources/textures/WallL.xpm";
	// v->img[EWALLL2].filename = "resources/textures/WallL2.xpm";
	// v->img[EWALLL3].filename = "resources/textures/WallL3.xpm";
	// v->img[EWALLL4].filename = "resources/textures/WallL4.xpm";
	// v->img[EWALLR].filename = "resources/textures/WallR.xpm";
	// v->img[EWALLR2].filename = "resources/textures/WallR2.xpm";
	// v->img[EWALLR3].filename = "resources/textures/WallR3.xpm";
	// v->img[EWALLR4].filename = "resources/textures/WallR4.xpm";
	// v->img[EWALLCUL].filename = "resources/textures/WallCUL.xpm";
	// v->img[EWALLCUR].filename = "resources/textures/WallCUR.xpm";
	// v->img[EWALLCDR].filename = "resources/textures/WallCDR.xpm";
	// v->img[EWALLCDL].filename = "resources/textures/WallCDL.xpm";
}

void	initpathtext(t_vars *v)
{
	initwallspath(v);
	// v->img[EOBST1V1].filename = "resources/textures/Boxes.xpm";
	// v->img[EOBST1V1W].filename = "resources/textures/Armoire.xpm";
	// v->img[EOBST1V2].filename = "resources/textures/CoffinEmpty.xpm";
	// v->img[EOBST2V2].filename = "resources/textures/CoffinClosed.xpm";
	v->img[ESPACE].filename = "resources/textures/Ground.xpm";
	v->img[ESPACE].id = ESPACE;
	v->img[EDOOR].filename = "resources/textures/Door.xpm";
	v->img[EDOOR].id = EDOOR;
	v->img[EWEAPON].filename = "resources/textures/knife.xpm";
	v->img[EGUARD].filename = "resources/textures/general.xpm";
	v->img[ESKYBOX].filename = "resources/textures/skybox.xpm";
	v->img[EHUDIMG].filename = "resources/textures/HUD.xpm";
	// v->img[ESPACE2].filename = "resources/textures/Ground2.xpm";
	// v->img[ESPACE3].filename = "resources/textures/Ground3.xpm";
	// v->img[ECOLLECT].filename = "resources/textures/Star2.xpm";
	// v->img[ESPAWN].filename = "resources/textures/antihero/Walk/Right.xpm";
	// 	v->img[EEXIT].filename = "resources/textures/Exit.xpm";
	// 	v->img[EGUARD].filename = "resources/textures/CthululuWalk.xpm";
	v->img[ETITLE].filename = "resources/textures/title.xpm";
	v->img[EMENUSELECT].filename = "resources/textures/menus/select.xpm";
	v->img[EMENU].filename = "resources/textures/menus/menu_start.xpm";
	v->img[EMENUIG].filename = "resources/textures/menus/menu_ingame.xpm";
	v->img[EMENUOPT].filename = "resources/textures/menus/menu_options.xpm";
	// 	v->img[EPROJ].filename = "resources/textures/attacks/iceball
	// /hadokenRIGHT.xpm";
}

void	initplayerpathanim(t_vars *v)
{
	(void)v;
	// 	v->img[ESPAWN].anim[NORTH].filename = "resources/textures
	// /antihero/Walk/Up.xpm";
	// 	v->img[ESPAWN].anim[SOUTH].filename = "resources/textures
	// /antihero/Walk/Down.xpm";
	// 	v->img[ESPAWN].anim[EAST].filename = "resources/textures
	// /antihero/Walk/Right.xpm";
	// 	v->img[ESPAWN].anim[WEST].filename = "resources/textures
	// /antihero/Walk/Left.xpm";
	// 	v->img[ESPAWN].anim[NORTH + DIR_N].filename = "resources/textures
	// /antihero/Attack/Up.xpm";
	// 	v->img[ESPAWN].anim[SOUTH + DIR_N].filename = "resources/textures
	// /antihero/Attack/Down.xpm";
	// 	v->img[ESPAWN].anim[EAST + DIR_N].filename = "resources/textures
	// /antihero/Attack/Right.xpm";
	// 	v->img[ESPAWN].anim[WEST + DIR_N].filename = "resources/textures
	// /antihero/Attack/Left.xpm";
}

void	initprojectilepathanim(t_vars *v)
{
	(void)v;
	// 	v->img[EPROJ].anim[NORTH].filename = "resources/textures
	// /attacks/iceball/hadokenUP.xpm";
	// 	v->img[EPROJ].anim[SOUTH].filename = "resources/textures
	// /attacks/iceball/hadokenDOWN.xpm";
	// 	v->img[EPROJ].anim[EAST].filename = "resources/textures
	// /attacks/iceball/hadokenRIGHT.xpm";
	// 	v->img[EPROJ].anim[WEST].filename = "resources/textures
	// /attacks/iceball/hadokenLEFT.xpm";
}
