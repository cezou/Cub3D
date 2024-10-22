/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 09:51:53 by pmagnero          #+#    #+#             */
/*   Updated: 2024/10/22 14:18:57 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

/// @brief Init one texture
/// @param v Vars
/// @param img Texture to initialize
void	inittexture(t_vars *v, t_imga *img, int i)
{
	img->img = mlx_xpm_file_to_image(v->mlx, img->filename, &img->width,
			&img->height);
	img->id = i;
	img->animy = img->height;
	if (!img->img)
		exit((prterr(v, "Error mlx texture image\n", 1, 1), 1));
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->len, &img->endian);
	if (!img->addr)
		exit((prterr(v, "Error mlx texture image address\n", 1, 1), 1));
}

/// @brief Init textures
/// @param v Vars
/// @param i Texture index to start from in the image array
void	inittextures(t_vars *v, int i)
{
	initimage(v, EMAP, v->screen.gamew, v->screen.gameh);
	initimage(v, COMP_N, v->screen.resw, v->screen.resh);
	initimage(v, EBUFF, v->screen.resw, v->screen.resh);
	v->img[ESOUTH] = v->infos.south.imga;
	v->img[EEAST] = v->infos.east.imga;
	v->img[EWEST] = v->infos.west.imga;
	v->img[ENORTH] = v->infos.north.imga;
	while (++i < EBUFF)
		inittexture(v, &v->img[i], i);
	scale_img((t_point){0}, &v->img[EKEK], &v->img[COMP_N]);
}

int	main(int ac, char **av)
{
	t_vars	v;

	init(&v, ac, av);
	while (1)
	{
		mlx_clear_window(v.mlx, v.screen.win);
		mlx_do_sync(v.mlx);
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
		else if (v.game.won == 4)
			mlx_loop_hook(v.mlx, &transition_melt_screen, &v);
		else
			mlx_loop_hook(v.mlx, &render, &v);
		mlx_loop(v.mlx);
		v.mlx->end_loop = 0;
	}
	return (0);
}
