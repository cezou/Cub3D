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

/// @brief Generate 64x64 textures
/// @param v Vars
/// @param c t_point {xorcolor=0, ycolor=0, xycolor=0, 0}
/// 
/// [0] flat red texture with black cross
/// [1] sloped greyscale
/// [2] sloped yellow gradient
/// [3] xor greyscale
/// [4] xor green
/// [5] red bricks
/// [6] red gradient
/// [7] flat grey texture
/// int xcolor = x * 256 / texWidth;
void	create_textures(t_vars *v, t_point c)
{
	int		x;
	int		y;

	x = -1;
	while (++x < 64)
	{
		y = -1;
		while (++y < 64)
		{
			c.x = (x * 256 / 64) ^ (y * 256 / 64);
			c.y = y * 256 / 64;
			c.z = y * 128 / 64 + x * 128 / 64;
			v->tex[0][64 * y + x] = 65536 * 254 * (x != y && x != 64 - y);
			v->tex[1][64 * y + x] = c.z + 256 * c.z + 65536 * c.z;
			v->tex[2][64 * y + x] = 256 * c.z + 65536 * c.z;
			v->tex[3][64 * y + x] = c.x + 256 * c.x + 65536 * c.x;
			v->tex[4][64 * y + x] = 256 * c.x;
			v->tex[5][64 * y + x] = 65536 * 192 * (x % 16 && y % 16);
			v->tex[6][64 * y + x] = 65536 * c.y;
			v->tex[7][64 * y + x] = 128 + 256 * 128 + 65536 * 128;
		}
	}
}

/// @brief Get the color from texture and add it the pixel to the buffer
/// @param v Vars
/// @param img Texture to add to the buffer
/// @param p 
void	add_pix_to_buffer(t_vars *v, t_imga img, t_point p)
{
	p.color = getcolorpix(v, img.addr, p.z);
	img_pix_put(&v->img[EMAP], p, v);
}

/// @brief Get the color of the pixel from the texture
/// if the game is paused apply a negative filter
/// @param v Vars
/// @param addr 
/// @param k 
/// @return Color of the pixel
int	getcolorpix(t_vars *v, char *addr, size_t k)
{
	if (v->game.pause)
		return ((addr[k] << 0) + (addr[k + 1] << 8)
			+ (0 << 16) + (addr[k + 3] << 24));
	else
		return ((addr[k] << 0) + (addr[k + 1] << 8) + (addr[k + 2] << 16)
			+ (addr[k + 3] << 24));
}

/// @brief Put the pixel from the texture into the MLX buffer
///	in order to be displayed with mlx_put_image_to_window()
/// @param img Buffer
/// @param p t_point {x, y, 0, color}
/// @param v Vars
void	img_pix_put(t_imga *img, t_point p, t_vars *v)
{
	char	*pixel;
	int		i;
	int		width;
	int		height;

	width = v->screen.resw;
	height = v->screen.resh;
	if (p.x >= 0 && p.x < width && p.y >= 0 && p.y < height)
	{
		i = img->bpp - 8;
		pixel = img->addr + (p.y * img->len + p.x * (img->bpp / 8));
		while (i >= 0)
		{
			if (img->endian != 0)
				*pixel++ = (p.color >> i) & 0xFF;
			else
				*pixel++ = (p.color >> (img->bpp - 8 - i)) & 0xFF;
			i -= 8;
		}
	}
}
