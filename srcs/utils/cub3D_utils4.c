/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:13:00 by pmagnero          #+#    #+#             */
/*   Updated: 2024/04/05 12:19:12 by pmagnero         ###   ########.fr       */
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
			dest->addr[p.z] = src->addr[p.color];
		}
	}
	dest->ratiox = (double)(src->width) / (double)(dest->width);
	dest->ratioy = (double)(src->height) / (double)(dest->height);
}
