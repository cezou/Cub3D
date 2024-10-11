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
/// @param p Pixel datas {x, y, k, color}
///	@param fog Fog datas {bool, dist, fog color, fog level}
///	@param dark Darken the pixel
///	@param options Options {dark, transparence, 0, 0}
void	add_pix(t_vars *v, t_point p, t_point3 fog, t_point opt)
{
	if (!opt.y && p.z > -1 && v->tmp[0].addr[p.z + 3] == 0)
	{
		p.color = getcolorpix(v, v->tmp[0].addr, p.z);
		if (opt.x)
			p.color = (p.color >> 1) & 8355711;
		if (fog.x)
			p.color = color_lerp(p.color, fog.z, fog.y / 29 * fog.uv);
		img_pix_put(&v->tmp[1], p, v);
	}
	else if (opt.y)
	{
		if (fog.x)
			p.color = color_lerp(p.color, fog.z, fog.y / 29 * fog.uv);
		img_pix_put(&v->tmp[1], p, v);
	}
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
		return ((addr[k] & 0xFF) + ((addr[k + 1]) << 8) + (0 << 16));
	else if (v->game.pain)
		return ((0) + ((0) << 8) + (addr[k + 2] << 16) * v->game.pain);
	else
		return ((addr[k] & 0xFF) + ((addr[k + 1] & 0xFF) << 8)
			+ ((addr[k + 2] & 0xFF) << 16));
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

/// @brief Interpolate color value
/// @param color1 Current color
/// @param color2 Color max value
/// @param t Ratio
/// @return Color interpolated
uint32_t	color_lerp(uint32_t color1, uint32_t color2, double t)
{
	uint32_t	r1;
	uint32_t	g1;
	uint32_t	b1;

	if (t < 0)
		return (color1);
	if (t >= 1)
		return (color2);
	r1 = (color1 >> 16) & 0xFF;
	g1 = (color1 >> 8) & 0xFF;
	b1 = (color1) & 0xFF;
	r1 = (1 - t) * r1 + t * ((color2 >> 16) & 0xFF);
	if (r1 > 0xFF)
		r1 = 0xFF;
	g1 = (1 - t) * g1 + t * ((color2 >> 8) & 0xFF);
	if (g1 > 0xFF)
		g1 = 0xFF;
	b1 = (1 - t) * b1 + t * ((color2) & 0xFF);
	if (b1 > 0xFF)
		b1 = 0xFF;
	return ((r1 << 16) + (g1 << 8) + (b1));
}
