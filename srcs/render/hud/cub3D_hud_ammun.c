/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_hud_ammun.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 20:43:05 by pmagnero          #+#    #+#             */
/*   Updated: 2024/10/04 12:33:01 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3D.h"

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

	d = yoff - v->tmp[0].animy + (12 / v->hud.img.ratioy);
	if (v->tmp[1].id == v->img[EBUFF].id)
		d = v->screen.gameh + yoff - v->tmp[0].animy
			+ (12 / v->hud.img.ratioy);
	delta = (g.x / v->hud.img.ratiox)
		- v->tmp[0].animx * res[g.z] - ((g.y + 1) - g.z) * v->tmp[0].animx
		+ (3 / v->hud.img.ratiox) * ((g.y - 1) - g.z);
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
