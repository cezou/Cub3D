/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_hud.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 20:43:05 by pmagnero          #+#    #+#             */
/*   Updated: 2024/09/25 19:21:40 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/// @brief Scale a src image to the dimension of the dest image
/// @param p {x, y, z, color} => {0}
/// @param src Source image to scale
/// @param dest Destination image
void	scale_img(t_point p, t_imga *src, t_imga *dest)
{
	int		tx;
	int		ty;

	p.y = -1;
	while (++p.y < dest->height)
	{
		p.x = -1;
		while (++p.x < dest->width)
		{
			tx = p.x * src->width / dest->width;
			ty = p.y * src->height / dest->height;
			p.z = (p.y * dest->len) + (p.x * 4);
			p.color = (ty * src->len) + (tx * 4);
			dest->addr[p.z + 4] = src->addr[p.color + 4];
			dest->addr[p.z + 3] = src->addr[p.color + 3];
			dest->addr[p.z + 2] = src->addr[p.color + 2];
			dest->addr[p.z + 1] = src->addr[p.color + 1];
		}
	}
}

/// @brief Render the HUD
/// @param v Vars
void	renderhud(t_vars *v)
{
	t_point	p;
	t_imga	img[2];

	if (!v->game.refresh_hud)
		return ;
	p.x = -1;
	img[0] = v->img[EHUD];
	img[1] = v->img[EBUFF];
	p.color = 0;
	while (++p.x < v->img[EHUD].width)
	{
		p.y = -1;
		while (++p.y < v->img[EHUD].height)
		{
			p.z = (p.y * img[0].len) + (p.x * 4);
			add_pix(v, img, (t_point){p.x, p.y + v->screen.gameh, p.z,
				p.color}, (t_point2){0});
		}
	}
	v->game.refresh_hud = 0;
}
