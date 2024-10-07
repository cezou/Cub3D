/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_init_anim.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:09:56 by pmagnero          #+#    #+#             */
/*   Updated: 2024/10/04 13:35:38 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	initplayeranim(t_vars *v)
{
	initplayerpathanim(v);
}

void	initguardanim(t_vars *v)
{
	initguardpathanim(v);
}

/// @brief
/// @param v Vars
/// @param p {img index, tmp img index, animx offset, animy offset}
void	init_elem(t_vars *v, t_point p)
{
	v->img[p.x].width = v->img[p.y].width / v->img[EHUDTMP].ratiox;
	v->img[p.x].height = v->img[p.y].height / v->img[EHUDTMP].ratioy;
	initimage(v, p.x, v->img[p.x].width, v->img[p.x].height);
	scale_img((t_point){0}, &v->img[p.y], &v->img[p.x]);
	if (p.z)
		v->img[p.x].animx = v->img[p.x].width / p.z;
	if (p.color)
		v->img[p.x].animy = v->img[p.x].height / p.color;
}

/// @brief
/// @param v Vars
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
	init_elem(v, (t_point){EDOOMHTMP, EDOOMH, 3, 0});
	v->hud.head = v->img[EDOOMHTMP];
	v->hud.headid = v->img[EDOOMHTMP].animx;
	v->hud.animoff = v->img[EDOOMHTMP].animx;
	init_elem(v, (t_point){EBIGNUMBERS, EBIGNUMBERSTMP, 12, 0});
	init_elem(v, (t_point){ESMALLNUMBERS, ESMALLNUMBERSTMP, 10, 2});
	init_elem(v, (t_point){EHEALTH, EHEALTHTMP, 0, 0});
	init_elem(v, (t_point){EARMOR, EARMORTMP, 0, 0});
	init_elem(v, (t_point){EAMMO, EAMMOTMP, 0, 0});
	init_elem(v, (t_point){EWEAPON, EWEAPONTMP, 0, 0});
	init_elem(v, (t_point){EAMMUN, EAMMUNTMP, 0, 0});
	init_elem(v, (t_point){ECARDS, ECARDSTMP, 3, 2});
	init_elem(v, (t_point){ECARDSLOT, ECARDSLOTTMP, 0, 0});
	v->hud.map_zoom = 10;
}
