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

/// @brief Function compare to use with qsort, it is used to sort alphabetically
/// @param a Const pointer of the first element
/// @param b Const pointer of the second element
/// @return 0/1 
int	cmpalpha(const void *const a, const void *const b)
{
	return (ft_strncmp((*(struct dirent **)a)->d_name,
			(*(struct dirent **)b)->d_name,
			ft_strlen((*(struct dirent **)b)->d_name)));
}

/// @brief Load the file in the data structure array from the folder
/// if it is an xpm file
/// @param v Vars
/// @param fd Directory structure pointer
/// @param f The actual file object
/// @param dir The directory path
/// @return Boolean false if the file is not a xpm file
bool	load_file(t_vars *v, DIR *fd, struct dirent **f, const char *dir)
{
	int (i) = v->img[ESKYBOX].animnb;
	if (!ft_strncmp((*f)->d_name, ".", 1) || !ft_strncmp((*f)->d_name, "..", 2)
		|| ft_strncmp((*f)->d_name + (ft_strlen((*f)->d_name) - 4), ".xpm", 4))
		return (*f = readdir(fd), false);
	v->img[ESKYBOX].anim[++i].filename = ft_calloc(ft_strlen(dir)
			+ ft_strlen((*f)->d_name) + 2, sizeof(char));
	if (!v->img[ESKYBOX].anim[i].filename)
		exit((prterr((closedir(fd), v), ERRMALL, 1, 1), 1));
	ft_strlcat(v->img[ESKYBOX].anim[i].filename, dir, ft_strlen(dir) + 1);
	ft_strlcat(v->img[ESKYBOX].anim[i].filename, "/",
		ft_strlen(v->img[ESKYBOX].anim[i].filename) + 2);
	ft_strlcat(v->img[ESKYBOX].anim[i].filename, (*f)->d_name,
		ft_strlen(v->img[ESKYBOX].anim[i].filename)
		+ ft_strlen((*f)->d_name) + 1);
	int (file) = open(v->img[ESKYBOX].anim[i].filename, O_RDONLY);
	if (file == -1)
		exit((prterr((closedir(fd), v),
					"Error : Failed to open entry file\n", 1, 1), 1));
	inittexture(v, &v->img[ESKYBOX].anim[i], i);
	*f = readdir(fd);
	if (close(file) == -1)
		exit((prterr((closedir(fd), v), "Error : Close file\n\n", 1, 1), 1));
	return (v->img[ESKYBOX].animnb = i, true);
}

/// @brief Sort files alphabetically before putting them in the data structure
/// @param v Vars
/// @param fd Directory structure pointer
/// @param f The actual file object
void	sort_files_alphabetically(t_vars *v, DIR *fd, struct dirent **f)
{
	struct dirent	**lst;
	int				i;

	i = 1;
	v->img[ESKYBOX].animnb = -1;
	*f = readdir(fd);
	while (*f)
		*f = readdir((++i, fd));
	lst = malloc(sizeof(*lst) * i);
	if (!lst)
		exit((prterr((closedir(fd), v), ERRMALL, 1, 1), 1));
	v->img[ESKYBOX].anim = ft_calloc(i, sizeof(t_imga));
	if (!v->img[ESKYBOX].anim)
		exit((prterr((free(lst), closedir(fd), v), ERRMALL, 1, 1), 1));
	rewinddir(fd);
	i = -1;
	*f = readdir(fd);
	while (*f)
	{
		lst[++i] = *f;
		*f = readdir(fd);
	}
	qsort(lst, i, sizeof(*lst), cmpalpha);
	free(lst);
}

/// @brief Load all the xpm images from a folder into a data structure
/// @param v Vars
/// @param dir Directory path
void	load_images_from_folder(t_vars *v, const char *dir)
{
	DIR				*fd;
	struct dirent	*in_file;

	if (MANDATORY)
		return ;
	fd = opendir(dir);
	if (!fd)
		exit((prterr(v, "Error : Failed to open input directory\n", 1, 1), 1));
	sort_files_alphabetically(v, fd, &in_file);
	rewinddir(fd);
	in_file = readdir(fd);
	while (in_file)
	{
		if (!load_file(v, fd, &in_file, dir))
			continue ;
	}
	v->img[ESKYBOX].animnb++;
	if (closedir(fd) == -1)
		exit((prterr(v,
					"Error : Close dir\n\n", 1, 1), 1));
}

/// @brief Init and scale image
/// @param v Vars
/// @param index Index of the image in the data structure array img
/// @param b Boolean if it is not the last image to be init with this function
/// @param animnb Number of animation frame in the image, used to get the offset
void	initanim(t_vars *v, int index, int b, int animnb)
{
	double	factorx;
	double	factory;
	double	scalefactor;

	factorx = (double)v->screen.gamew / 800;
	factory = (double)v->screen.gameh / 600;
	scalefactor = factorx;
	if (factorx >= factory)
		scalefactor = factory;
	v->img[ETMP].filename = v->img[index].filename;
	inittexture(v, &v->img[ETMP], ETMP);
	v->img[index].width = scalefactor * v->img[ETMP].width * 3;
	v->img[index].height = scalefactor * v->img[ETMP].height * 3;
	initimage(v, index, v->img[index].width, v->img[index].height);
	scale_img((t_point){0}, &v->img[ETMP], &v->img[index]);
	v->img[index].animx = v->img[ETMP].width / animnb * (1.0
			/ v->img[index].ratiox);
	v->img[index].animy = v->img[index].height;
	if (b)
		mlx_destroy_image(v->mlx, v->img[ETMP].img);
}
