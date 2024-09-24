/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_hud.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 20:43:05 by pmagnero          #+#    #+#             */
/*   Updated: 2024/09/24 05:56:07 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/// @brief Add pixels of the sprite to the buffer
/// @param v Vars
/// @param sp Sprite struct containing calcul datas 
/// @param p The actual sprite to draw
void	scale_img(t_vars *v, t_point p, t_imga *src, t_imga *dest)
{
	int		tx;
	int		ty;

	p.y = -1;
	while (++p.y < v->screen.hudh)
	{
		p.x = -1;
		while (++p.x < v->screen.hudw)
		{
			tx = p.x * src->width / v->screen.hudw;
			ty = p.y * src->height / v->screen.hudh;
			p.z = (p.y * dest->len) + (p.x * 4);
			p.color = (ty * src->len) + (tx * 4);
			dest->addr[p.z + 4]
				= src->addr[p.color + 4];
			dest->addr[p.z + 3] = src->addr[p.color + 3];
			dest->addr[p.z + 2] = src->addr[p.color + 2];
			dest->addr[p.z + 1] = src->addr[p.color + 1];
		}
	}
}

void	renderhud(t_vars *v)
{
	scale_img(v, (t_point){0}, &v->img[EHUDIMG], &v->img[EHUD]);
	mlx_put_image_to_window(v->mlx, v->screen.win,
		v->img[EHUD].img, 0, v->screen.gameh);
}
