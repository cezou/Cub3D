/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_hud_health_armor.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 20:43:05 by pmagnero          #+#    #+#             */
/*   Updated: 2024/10/04 12:32:47 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3D.h"

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
	delta = (g.x / v->hud.img.ratiox)
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
