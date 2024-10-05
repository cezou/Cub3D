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

/// @brief Draw a square on the minimap.
/// @param pos Position containing the starting coordinates.
/// @param size Size of the square.
/// @param color Color of the square.
void	draw_square(t_v2f pos, float size, int color, t_vars *v)
{
	size_t	x;
	int		y;

	x = 0;
	while (x < size)
	{
		y = -1;
		while (++y < size)
			img_pix_put(&v->tmp[1], (t_point){pos[0] + x, pos[1] + y, 0, color},
				v);
		x++;
	}
}

/// @brief Draw the border of the minimap.
/// @param size Size of each square in the border.
void	draw_border(float size, int nb_blocks, t_vars *v)
{
	int	i;

	i = -1;
	while (++i < nb_blocks + 2)
		draw_square((t_v2f){size * (i), 0}, size, B_P, v);
	i = -1;
	while (++i < nb_blocks + 2)
		draw_square((t_v2f){0, size * (i)}, size, B_P, v);
	i = -1;
	while (++i < nb_blocks + 2)
		draw_square((t_v2f){size * (nb_blocks + 1), size * (i)}, size, B_P, v);
	i = -1;
	while (++i < nb_blocks + 2)
		draw_square((t_v2f){size * (i), size * (nb_blocks + 1)}, size, B_P, v);
}

/// @brief Draw a block on the minimap depending on the letters in the mapfile
/// @param screen Position on the screen where the block should be drawn.
/// @param i_j Coordinates in the map array.
/// @param size Size of the block.
void	draw_a_block(t_v2f screen, t_v2i i_j, float size, t_vars *v)
{
	if (i_j[1] < 0 || i_j[0] < 0 || i_j[1] >= (int)tab_len(v->infos.map)
		|| i_j[0] >= (int)ft_strlen(v->infos.map[i_j[1]]))
		return (draw_square(screen, size, W_P, v));
	if (v->infos.map[i_j[1]][i_j[0]] == '1')
		draw_square(screen, size, W_P, v);
	else if (v->infos.map[i_j[1]][i_j[0]] == 'D')
		draw_square(screen, size, GR_P, v);
	else
		draw_square(screen, size, v->infos.floor, v);
}

/// @brief Draw a minimap in the top-left corner of the screen,
/// @brief depending on the zoom: scrolling increase or decrease
// @brief the number of blocks drawn on the map
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
	draw_square((t_v2f){size / 2 + (nb_blocks / 2) * size, size / 2 + (nb_blocks
			/ 2) * size}, size, RE_P, v);
	draw_border(size, nb_blocks, v);
}
