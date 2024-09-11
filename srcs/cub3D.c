/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 09:51:53 by pmagnero          #+#    #+#             */
/*   Updated: 2024/09/11 15:37:17 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	inittextures(t_vars *v, int i)
{
	initimage(v, EMAP);
	while (++i < COMP_N)
	{
		TRACE("img: %d", i);
		v->img[i].img = mlx_xpm_file_to_image(v->mlx, v->img[i].filename,
				&v->img[i].width, &v->img[i].height);
		if (!v->img[i].img)
			exit((prterr(v, "Error mlx texture image\n", 1, 1), 1));
		v->img[i].addr = mlx_get_data_addr(v->img[i].img, &v->img[i].bpp,
				&v->img[i].len, &v->img[i].endian);
		if (!v->img[i].addr)
			exit((prterr(v, "Error mlx texture image address\n", 1, 1), 1));
		v->img[i].xdelta = 0;
		v->img[i].ydelta = 0;
		v->img[i].posx = 0;
		v->img[i].posy = 0;
		v->img[i].animx = 0;
		v->img[i].animy = 0;
		v->img[i].anim = NULL;
		v->img[i].animnb = 0;
	}
	initimage(v, COMP_N);
}

int	main(int ac, char **av)
{
	t_vars	v;
	int		xorcolor;
	int		ycolor;
	int		xycolor;
	t_infos	i;

	if (ac < 2)
		return (perr(E_ARG), FAIL);
	parsing(av[1], &i);
	v.img = (t_imga *)malloc(sizeof(t_imga) * (COMP_N + 1));
	if (!v.img)
		exit((prterr(&v, ERRMALL, 1, 1), 1));
	// (void)argc;
	// (void)argv;
	// showparams(&v);
	init(&v, ac, av);
	init_cam(&v);
	// TEST FLAT TEXTURES
	for (int x = 0; x < 64; x++)
	{
		for (int y = 0; y < 64; y++)
		{
			xorcolor = (x * 256 / 64) ^ (y * 256 / 64);
			// int xcolor = x * 256 / texWidth;
			ycolor = y * 256 / 64;
			xycolor = y * 128 / 64 + x * 128 / 64;
			v.tex[0][64 * y + x] = 65536 * 254 * (x != y && x != 64 - y);
			// flat red texture with black cross
			v.tex[1][64 * y + x] = xycolor + 256 * xycolor + 65536 * xycolor;
			// sloped greyscale
			v.tex[2][64 * y + x] = 256 * xycolor + 65536 * xycolor;
			// sloped yellow gradient
			v.tex[3][64 * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor;
			// xor greyscale
			v.tex[4][64 * y + x] = 256 * xorcolor;
			// xor green
			v.tex[5][64 * y + x] = 65536 * 192 * (x % 16 && y % 16);
			// red bricks
			v.tex[6][64 * y + x] = 65536 * ycolor;
			// red gradient
			v.tex[7][64 * y + x] = 128 + 256 * 128 + 65536 * 128;
			// flat grey texture
		}
	}
	while (1)
	{
		v.game.updated_at = 0;
		hooks(&v);
		if (v.game.start == 0)
			mlx_loop_hook(v.mlx, &maintitleanim, &v);
		else if (v.game.won == 1)
			mlx_loop_hook(v.mlx, &win, &v);
		else if (v.game.won == 2)
			mlx_loop_hook(v.mlx, &lose, &v);
		else if (v.game.won == 3)
			mlx_loop_hook(v.mlx, &credits, &v);
		else
			mlx_loop_hook(v.mlx, &render, &v);
		mlx_loop(v.mlx);
		v.mlx->end_loop = 0;
	}
	return (0);
}
