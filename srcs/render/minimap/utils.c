/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:55:12 by cviegas           #+#    #+#             */
/*   Updated: 2024/10/07 14:55:13 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3D.h"

void	draw_scaled_img(t_imga *img, t_v2f pos, float size, t_vars *v)
{
	size_t	x;
	size_t	y;
	int		src_x;
	int		src_y;
	int		color;

	v->tmp[1] = v->img[EBUFF];
	x = 0;
	while (x < size)
	{
		y = 0;
		while (y < size)
		{
			src_x = (int)(x * (float)img->width / size);
			src_y = (int)(y * (float)img->height / size);
			color = getcolorpix(v, img->addr, (src_y * img->len + src_x
						* (img->bpp / 8)));
			if (color != 0x00FFFF)
				add_pix(v, (t_point){pos[0] + x, pos[1] + y, 0, color},
					(t_point2){0}, (t_point){1, 1, 1, 1});
			y++;
		}
		x++;
	}
}

/// @brief Draw a square on the minimap.
/// @param pos Position containing the starting coordinates.
/// @param size Size of the square.
/// @param color Color of the square.
void	draw_square(t_v2f pos, float size, int color, t_vars *v)
{
	size_t	x;
	int		y;

	v->tmp[1] = v->img[EBUFF];
	x = 0;
	if (v->game.pause)
		color = color & 0x00FFFF;
	while (x < size)
	{
		y = -1;
		while (++y < size)
			add_pix(v, (t_point){pos[0] + x, pos[1] + y, 0, color},
				(t_point2){0}, (t_point){1, 1, 1, 1});
		x++;
	}
}
