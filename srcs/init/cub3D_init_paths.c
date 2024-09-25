/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_init_paths.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:09:56 by pmagnero          #+#    #+#             */
/*   Updated: 2024/09/25 16:45:51 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	initwallspath(t_vars *v)
{
	v->img[EWALL].filename = "resources/textures/Wall.xpm";
}

void	initpathtext(t_vars *v)
{
	initwallspath(v);
	v->img[ESPACE].filename = "resources/textures/Ground.xpm";
	v->img[ESPACE].id = ESPACE;
	v->img[EDOOR].filename = "resources/textures/Door.xpm";
	v->img[EDOOR].id = EDOOR;
	v->img[EWEAPON].filename = "resources/textures/knife.xpm";
	v->img[EGUARD].filename = "resources/textures/general.xpm";
	v->img[ESKYBOX].filename = "resources/textures/skybox.xpm";
	v->img[EHUDIMG].filename = "resources/textures/HUD.xpm";
	v->img[ETITLE].filename = "resources/textures/title.xpm";
	v->img[EMENUSELECT].filename = "resources/textures/menus/select.xpm";
	v->img[EMENU].filename = "resources/textures/menus/menu_start.xpm";
	v->img[EMENUIG].filename = "resources/textures/menus/menu_ingame.xpm";
	v->img[EMENUOPT].filename = "resources/textures/menus/menu_options.xpm";
	v->img[EKEK].filename = "resources/textures/DoomTitle.xpm";
}

void	initplayerpathanim(t_vars *v)
{
	(void)v;
}

void	initprojectilepathanim(t_vars *v)
{
	(void)v;
}
