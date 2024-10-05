#include "../../../includes/cub3D.h"
#include <stdio.h> // Pour les messages de débogage

/// @brief Draw a rectangle on the minimap.
/// @param p Point containing the starting coordinates and color.
/// @param width Width of the rectangle.
/// @param height Height of the rectangle.
/// @param v Vars
void	draw_rectangle(t_point p, size_t width, size_t height, t_vars *v)
{
	size_t	x;
	int		y;

	x = 0;
	while (x < width)
	{
		y = -1;
		while (++y < (int)height)
			img_pix_put(&v->tmp[1], (t_point){p.x + x, p.y + y, 0, p.color}, v);
		x++;
	}
}

void	draw_border(int block_size, t_vars *v)
{
	int	i;

	i = -1;
	while (++i < 12)
		draw_rectangle((t_point){block_size * (i), 0, 0, 0x000000}, block_size,
			block_size, v);
	i = -1;
	while (++i < 12)
		draw_rectangle((t_point){0, block_size * (i), 0, 0x000000}, block_size,
			block_size, v);
	i = -1;
	while (++i < 12)
		draw_rectangle((t_point){block_size * 11, block_size * (i), 0,
			0x000000}, block_size, block_size, v);
	i = -1;
	while (++i < 12)
		draw_rectangle((t_point){block_size * (i), block_size * 11, 0,
			0x000000}, block_size, block_size, v);
}

/// @brief Draw a minimap in the top-left corner of the screen.
/// @param v Vars
void	rendermap(t_vars *v)
{
	int		i;
	int		j;
	int		x;
	int		y;
	float	screen_x;
	float	screen_y;
	int		block_size;
	float	offset_x;
	float	offset_y;

	offset_x = v->player.x - (int)v->player.x;
	offset_y = v->player.y - (int)v->player.y;
	block_size = (int)(v->screen.resw * 0.15 / 10);
	i = (int)v->player.x - 5;
	x = 0;
	while (i < v->player.x + 5)
	{
		y = 0;
		j = (int)v->player.y - 5;
		while (j < v->player.y + 5)
		{
			screen_x = block_size + (x - offset_x) * block_size;
			screen_y = block_size + (y - offset_y) * block_size;
			if (j < 0 || i < 0 || j >= (int)tab_len(v->infos.map)
				|| i >= (int)ft_strlen(v->infos.map[j])
				|| (v->infos.map[j][i] == '1'))
				draw_rectangle((t_point){screen_x, screen_y, 0, 0xFFFFFF},
					block_size, block_size, v);
			else
				draw_rectangle((t_point){screen_x, screen_y, 0, v->infos.floor},
					block_size, block_size, v);
			j++;
			y++;
		}
		x++;
		i++;
	}
	draw_rectangle((t_point){block_size + 4.5 * block_size, block_size + 4.5
		* block_size, 0, 0xFF0000}, block_size, block_size, v);
	draw_border(block_size, v);
}
