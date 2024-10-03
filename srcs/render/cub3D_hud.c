/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_hud.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 20:43:05 by pmagnero          #+#    #+#             */
/*   Updated: 2024/10/03 23:23:01 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/// @brief 
/// @param v 
/// @param nb 
void	number_to_digits(t_vars *v, int n, int res[4], int *i)
{
	if (n > 9)
		number_to_digits(v, n / 10, res, i);
	res[*i] = n % 10;
	(*i)++;
}

/// @brief 
/// @param v 
/// @param res 
/// @param i 
/// @param j 
/// @param xoff {xoff, i, j}
void	renderdigit(t_vars *v, int res[4], t_point g)
{
	t_point	p;
	int		w;
	int		h;
	int		delta;
	int		d;

	d = 0;
	if (v->tmp[1].id == v->img[EBUFF].id)
		d = v->screen.gameh;
	delta = (g.x / v->img[EHUDTMP].ratiox)
		- v->tmp[0].animx * res[g.z] - ((g.y + 1) - g.z) * v->tmp[0].animx;
	p.x = res[g.z] * v->tmp[0].animx - 1;
	w = p.x + v->tmp[0].animx;
	h = v->tmp[0].height;
	p.color = 0;
	while (++p.x < w)
	{
		p.y = -1;
		while (++p.y < h)
		{
			p.z = (p.y * v->tmp[0].len) + (p.x * 4);
			add_pix(v, (t_point){p.x + delta, p.y + d, p.z, p.color},
				(t_point2){0}, (t_point){0});
		}
	}
}

/// @brief 
/// @param v 
/// @param res 
/// @param i 
/// @param j 
/// @param xoff {xoff, i, j}
void	rendersmalldigit(t_vars *v, int res[4], t_point g, int yoff)
{
	t_point	p;
	int		w;
	int		delta;
	int		d;

	d = yoff - v->tmp[0].animy + (12 / v->img[EHUDTMP].ratioy);
	if (v->tmp[1].id == v->img[EBUFF].id)
		d = v->screen.gameh + yoff - v->tmp[0].animy
			+ (12 / v->img[EHUDTMP].ratioy);
	delta = (g.x / v->img[EHUDTMP].ratiox)
		- v->tmp[0].animx * res[g.z] - ((g.y + 1) - g.z) * v->tmp[0].animx
		+ (3 / v->img[EHUDTMP].ratiox) * ((g.y - 1) - g.z);
	p.x = res[g.z] * (v->tmp[0].animx) - 1;
	w = p.x + v->tmp[0].animx;
	p.color = 0;
	while (++p.x < w)
	{
		p.y = v->tmp[0].animy + 1;
		while (++p.y < g.color)
		{
			p.z = (p.y * v->tmp[0].len) + (p.x * 4);
			add_pix(v, (t_point){p.x + delta, p.y + d, p.z, p.color},
				(t_point2){0}, (t_point){0});
		}
	}
}

/// @brief 
/// @param v 
void	renderemptyzone(t_vars *v, t_imga zone, int xoff)
{
	t_point	p;
	int		w;
	int		h;
	int		delta;

	delta = 0;
	if (v->tmp[1].id == v->img[EBUFF].id)
		delta = v->screen.gameh;
	p.x = -1;
	v->tmp[0] = zone;
	w = v->tmp[0].width;
	h = v->tmp[0].height;
	p.color = 0;
	while (++p.x < w)
	{
		p.y = -1;
		while (++p.y < h)
		{
			p.z = (p.y * v->tmp[0].len) + (p.x * 4);
			add_pix(v, (t_point){p.x + ceil(xoff / v->img[EHUDTMP].ratiox),
				p.y + delta, p.z, p.color},
				(t_point2){0}, (t_point){0});
		}
	}
}

/// @brief 
/// @param v 
void	renderelement(t_vars *v, int xoff, int nb, int percent)
{
	int	res[4];
	int	i;
	int	j;

	i = 0;
	number_to_digits(v, nb, res, &i);
	j = i;
	res[j] = -1;
	if (percent)
		res[j] = 10;
	while (++j <= 3)
		res[j] = -1;
	i -= !percent;
	j = 4;
	v->tmp[0] = v->img[EBIGNUMBERS];
	while (--j > -1)
	{
		if (res[j] == -1)
			continue ;
		renderdigit(v, res, (t_point){xoff, i, j, 0});
	}
}

/// @brief 
/// @param v 
void	renderammun(t_vars *v, int xoff, int arr[4])
{
	int	res[4];
	int	i;
	int	j;
	int	t;

	t = -1;
	v->tmp[0] = v->img[ESMALLNUMBERS];
	while (++t < 4)
	{
		i = 0;
		number_to_digits(v, arr[t], res, &i);
		j = i;
		res[j] = -1;
		while (++j <= 3)
			res[j] = -1;
		i--;
		j = 4;
		while (--j > -1)
		{
			if (res[j] == -1)
				continue ;
			rendersmalldigit(v, res, (t_point){xoff, i, j, v->tmp[0].height},
				(v->tmp[0].animy - 4) * t);
		}
	}
}

/// @brief 
/// @param v 
/// @param delta 
/// @param i 
/// @param xoff 
void	renderarmdigit(t_vars *v, int delta, int i, int xoff)
{
	t_point	p;
	int		w;
	int		h;
	int		d;

	d = (xoff / v->img[EHUDTMP].ratiox) - (i % 4 + i / 4) * (v->tmp[0].animx)
		+ ((i % 4 - i / 4) - 1) * (25 / v->img[EHUDTMP].ratiox)
		- ((10 - 5 * (i / 4 == 1)) / v->img[EHUDTMP].ratiox);
	p.x = i * v->tmp[0].animx + v->tmp[0].animx + 1;
	w = p.x + v->tmp[0].animx;
	h = v->tmp[0].height;
	p.color = 0;
	while (++p.x < w)
	{
		p.y = v->tmp[0].animy + 1;
		while (++p.y < h)
		{
			p.z = (p.y * v->tmp[0].len) + (p.x * 4);
			add_pix(v, (t_point){p.x + d,
				p.y + delta, p.z, p.color},
				(t_point2){0}, (t_point){0});
		}
	}
}

/// @brief Render the HUD
/// @param v Vars
void	renderarmsdigits(t_vars *v, int xoff)
{
	int		delta;
	int		i;

	v->tmp[0] = v->img[ESMALLNUMBERS];
	i = 0;
	delta = -v->tmp[0].animy + ceil(9 / v->img[EHUDTMP].ratioy);
	if (v->tmp[1].id == v->img[EBUFF].id)
		delta = v->screen.gameh - v->tmp[0].animy
			+ ceil(9 / v->img[EHUDTMP].ratioy);
	while (++i < 7)
	{
		if (i == 4)
			delta += (26 / v->img[EHUDTMP].ratioy);
		if (!v->player.weapons[i])
			continue ;
		renderarmdigit(v, delta, i, xoff);
	}
}

/// @brief Render the HUD
/// @param v Vars
void	renderdoomhead(t_vars *v)
{
	t_point	p;
	int		w;
	int		h;
	int		delta;

	delta = 0;
	if (v->tmp[1].id == v->img[EBUFF].id)
		delta = v->screen.gameh;
	p.x = v->hud.animoff - 1;
	v->tmp[0] = v->img[EDOOMHTMP];
	w = v->hud.animoff + v->tmp[0].animx;
	h = v->tmp[0].height;
	p.color = 0;
	while (++p.x < w)
	{
		p.y = -1;
		while (++p.y < h)
		{
			p.z = (p.y * v->tmp[0].len) + (p.x * 4);
			add_pix(v, (t_point){p.x - v->hud.animoff + v->tmp[0].animx
				+ (v->screen.hudw / 2) - (v->tmp[0].width / 2),
				p.y + delta, p.z, p.color},
				(t_point2){0}, (t_point){0});
		}
	}
}

/// @brief Render the crosshair
/// @param v Vars
void	rendercrosshair(t_vars *v, t_point p, int w, int h)
{
	while (++p.x < w)
	{
		p.y = v->tmp[0].height / 2 - 2;
		while (++p.y < h)
		{
			p.color = v->infos.floor;
			if (v->game.canhit)
				p.color = v->infos.ceil;
			add_pix(v, p, (t_point2){0}, (t_point){0, 1, 0, 0});
		}
	}
	p.x = v->tmp[0].width / 2 - 2;
	w = v->tmp[0].width / 2 + 2;
	h = v->tmp[0].height / 2 + 10;
	while (++p.x < w)
	{
		p.y = v->tmp[0].height / 2 - 10;
		while (++p.y < h)
		{
			p.color = v->infos.floor;
			if (v->game.canhit)
				p.color = v->infos.ceil;
			add_pix(v, p, (t_point2){0}, (t_point){0, 1, 0, 0});
		}
	}
}

/// @brief Render the HUD
/// @param v Vars
void	renderhud(t_vars *v, t_imga dest)
{
	v->tmp[0] = v->img[EMAP];
	v->tmp[1] = v->img[EBUFF];
	rendercrosshair(v, (t_point){v->tmp[0].width / 2 - 10, 0, 0, 0},
		v->tmp[0].width / 2 + 10, v->tmp[0].height / 2 + 2);
	v->tmp[1] = dest;
	if (v->hud.refresh)
		save_screen_to_buffer(v->img[EHUD], v->img[EHUDTMP], 0);
	if (v->hud.refreshdh)
		renderdoomhead((v->hud.refreshdh = 0, v));
	if (v->hud.refreshhealth)
	{
		renderemptyzone(v, v->img[EHEALTH], 105);
		renderelement((v->hud.refreshhealth = 0, v),
			105 + v->img[EHEALTHTMP].width - 4, v->player.hp, 1);
	}
	if (v->hud.refresharmor)
	{
		renderemptyzone(v, v->img[EARMOR], 392);
		renderelement((v->hud.refresharmor = 0, v),
			392 + v->img[EARMORTMP].width - 2, v->player.armor, 1);
	}
	if (v->hud.refreshammo)
	{
		renderemptyzone(v, v->img[EAMMO], 0);
		renderelement((v->hud.refreshammo = 0, v),
			0 + v->img[EAMMOTMP].width - 4, v->player.ammo[0], 0);
	}
	if (v->hud.refreshweapon)
	{
		renderemptyzone(v, v->img[EWEAPON], 234);
		renderarmsdigits((v->hud.refreshweapon = 0, v), 234);
	}
	if (v->hud.refreshammun)
	{
		renderemptyzone(v, v->img[EAMMUN], 546);
		renderammun(v, 640, v->player.ammo);
		renderammun((v->hud.refreshammun = 0, v), 690, v->player.maxammo);
	}
	if (v->hud.refresh)
	{
		save_screen_to_buffer(v->img[EBUFF], v->img[EHUD], (v->img[EMAP].width
				* v->img[EMAP].height * (v->img[EMAP].bpp / 8)));
		v->hud.refresh = 0;
	}
}
