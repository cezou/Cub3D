/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_and_imgs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:22:28 by cviegas           #+#    #+#             */
/*   Updated: 2024/09/12 17:22:29 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	init_imgs(t_vars *v)
{
	v->infos.north.imga.img = NULL;
	v->infos.north.is_set = NULL;
	v->infos.east.imga.img = NULL;
	v->infos.east.is_set = NULL;
	v->infos.south.imga.img = NULL;
	v->infos.south.is_set = NULL;
	v->infos.west.imga.img = NULL;
	v->infos.west.is_set = NULL;
}

int	init_xpm(t_imga *img, char *path, void *mlx, int i)
{
	img->img = mlx_xpm_file_to_image(mlx, path, &img->width, &img->height);
	if (!img->img)
		return (lerr(i, "Mlx Image init failed"), -1);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->len, &img->endian);
	if (!img->addr)
		return (lerr(i, "Mlx Image address failed"), -1);
	img->xdelta = 0;
	img->ydelta = 0;
	img->posx = 0;
	img->posy = 0;
	img->animx = 0;
	img->animy = 0;
	img->anim = NULL;
	img->animnb = 0;
	return (0);
}

void	pfree_img(t_imga *img, t_vars *v)
{
	if (img->img)
		mlx_destroy_image(v->mlx, img->img);
}

void	clean_exit(char **l, int fd, t_vars *v, bool free_line)
{
	close(fd);
	if (free_line)
		freeall(l);
	pfree_img(&v->infos.east.imga, v);
	pfree_img(&v->infos.west.imga, v);
	pfree_img(&v->infos.south.imga, v);
	pfree_img(&v->infos.north.imga, v);
	mlx_destroy_display(v->mlx);
	free(v->mlx);
	exit(FAIL);
}
