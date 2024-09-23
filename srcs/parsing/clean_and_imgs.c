/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_and_imgs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:22:28 by cviegas           #+#    #+#             */
/*   Updated: 2024/09/23 01:58:09 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	init_infos(t_vars *v, char *file, int *fd)
{
	v->mapv.filename = file;
	*fd = open(file, O_RDONLY);
	if (*fd == -1)
		exit((merr("file doesn't exist or open failed"), FAIL));
	v->mlx = mlx_init();
	if (!v->mlx)
		exit((close(*fd), perr("MLX init failed"), FAIL));
	v->infos.north.imga.img = NULL;
	v->infos.north.is_set = NULL;
	v->infos.east.imga.img = NULL;
	v->infos.east.is_set = NULL;
	v->infos.south.imga.img = NULL;
	v->infos.south.is_set = NULL;
	v->infos.west.imga.img = NULL;
	v->infos.west.is_set = NULL;
	v->infos.f = 0;
	v->infos.c = 0;
}

int	init_xpm(t_imga *img, char *path, void *mlx, int i)
{
	img->img = mlx_xpm_file_to_image(mlx, path, &img->width, &img->height);
	if (!img->img)
		return (lerr(i, "Mlx Image init failed"), -1);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->len, &img->endian);
	if (!img->addr)
		return (lerr(i, "Mlx Image address failed"), -1);
	return (0);
}

void	pfree_img(t_imga *img, t_vars *v)
{
	if (img->img)
		mlx_destroy_image(v->mlx, img->img);
}

void	clean_exit(char **l, int fd, t_vars *v, bool free_line)
{
	if (fd != INT_MAX)
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
