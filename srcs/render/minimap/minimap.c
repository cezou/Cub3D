/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 15:20:01 by cviegas           #+#    #+#             */
/*   Updated: 2024/10/05 15:20:01 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3D.h"
#include <math.h>

/// @brief Draw the border of the minimap.
/// @param size Size of each square in the border.
static void	draw_border(float size, int nb_blocks, t_vars *v)
{
	int	i;

	i = -1;
	while (++i < nb_blocks + 2)
		draw_scaled_img(&v->img[EMAPBORDER], (t_v2f){size * (i), 0}, size, v);
	i = -1;
	while (++i < nb_blocks + 2)
		draw_scaled_img(&v->img[EMAPBORDER], (t_v2f){0, size * (i)}, size, v);
	i = -1;
	while (++i < nb_blocks + 2)
		draw_scaled_img(&v->img[EMAPBORDER], (t_v2f){size * (nb_blocks + 1),
			size * (i)}, size, v);
	i = -1;
	while (++i < nb_blocks + 2)
		draw_scaled_img(&v->img[EMAPBORDER], (t_v2f){size * (i), size
			* (nb_blocks + 1)}, size, v);
}

/// @brief Draw a block on the minimap depending on the letters in the mapfile
/// @param screen Position on the screen where the block should be drawn.
/// @param i_j Coordinates in the map array.
/// @param size Size of the block.
static void	draw_a_block(t_v2f screen, t_v2i i_j, float size, t_vars *v)
{
	if (i_j[1] < 0 || i_j[0] < 0 || i_j[1] >= (int)tab_len(v->infos.map)
		|| i_j[0] >= (int)ft_strlen(v->infos.map[i_j[1]]))
		return (draw_square(screen, size, W_P, v));
	if (v->infos.map[i_j[1]][i_j[0]] == '1')
		draw_square(screen, size, W_P, v);
	else if (v->infos.map[i_j[1]][i_j[0]] == 'D')
		draw_scaled_img(&v->img[EDOOR], screen, size, v);
	else
		draw_scaled_img(&v->img[ESPACE], screen, size, v);
}

static void	pick_and_draw(t_v2f size_angle, t_v2i x_y, t_v2f pos, t_vars *v)
{
	t_v2i	center;
	t_v2i	src;
	int		color;
	t_v2f	ratio;
	t_imga	*img;

	img = &v->img[EMAPHEAD];
	center = (t_v2i){img->width / 2, img->height / 2};
	ratio[0] = (float)img->width / size_angle[0];
	ratio[1] = (float)img->height / size_angle[0];
	src[0] = (int)(((x_y[0] * ratio[0] - center[0]) * cos(size_angle[1])
				- (x_y[1] * ratio[1] - center[1]) * sin(size_angle[1]))
			+ center[0]);
	src[1] = (int)(((x_y[0] * ratio[0] - center[0]) * sin(size_angle[1])
				+ (x_y[1] * ratio[1] - center[1]) * cos(size_angle[1]))
			+ center[1]);
	if (src[0] >= 0 && src[0] < img->width && src[1] >= 0
		&& src[1] < img->height)
	{
		color = *(int *)(img->addr + (src[1] * img->len + src[0] * (img->bpp
						/ 8)));
		if (color != 0x00FFFF)
			img_pix_put(&v->img[EBUFF], (t_point){pos[0] + x_y[0], pos[1]
				+ x_y[1], 0, color}, v);
	}
}

static void	draw_player(float size, size_t nb_blocks, t_vars *v)
{
	t_v2f	pos;
	size_t	x;
	int		y;
	float	angle;

	pos = (t_v2f){size / 2 + (nb_blocks / 2) * size, size / 2 + (nb_blocks / 2)
		* size};
	angle = (atan2(v->player.dir_y, v->player.dir_x) * -180.0 / M_PI + 90.0)
		* M_PI / 180.0;
	x = 0;
	while (x < size)
	{
		y = -1;
		while (++y < size)
		{
			pick_and_draw((t_v2f){size, angle}, (t_v2i){x, y}, pos, v);
		}
		x++;
	}
}

/// @brief Draw a minimap in the top-left corner of the screen,
/// @brief depending on the zoom: scrolling increase or decrease
/// @brief the number of blocks drawn on the map
void	rendermap(t_vars *v)
{
	t_v2i	i_j;
	t_v2i	x_y;
	t_v2f	screen;
	size_t	nb_blocks;
	float	size;

	nb_blocks = v->hud.map_zoom;
	size = v->screen.resw * 0.15 / nb_blocks;
	i_j[0] = (i)v->player.x - (nb_blocks / 2 + 1);
	x_y[0] = -1;
	while (++i_j[0] < (i)v->player.x + (i)(nb_blocks / 2 + 1) && (++x_y[0], 1))
	{
		x_y[1] = -1;
		i_j[1] = (i)v->player.y - (nb_blocks / 2 + 1);
		while (++i_j[1] < v->player.y + (nb_blocks / 2) && (++x_y[1] || 1))
		{
			screen = (t_v2f){size + (x_y[0] - (v->player.x - (i)v->player.x))
				* size, size + (x_y[1] - (v->player.y - (i)v->player.y))
				* size};
			draw_a_block(screen, i_j, size, v);
		}
	}
	draw_player(size, nb_blocks, v);
	draw_border(size, nb_blocks, v);
}
