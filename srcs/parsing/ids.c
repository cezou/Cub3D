/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ids.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:22:37 by cviegas           #+#    #+#             */
/*   Updated: 2024/09/12 17:22:37 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	set_value(t_boolimage *bimg, char *file, void *mlx, int i)
{
	if (bimg->is_set)
		return (lerr(i, "duplicate ID"), -1);
	if (init_xpm(&bimg->imga, file, mlx, i) == -1)
		return (-1);
	bimg->is_set = 1;
	return (0);
}

int	set_texture(t_infos *i, char **l, int ind, void *mlx)
{
	if (!cmp(l[0], "NO"))
		return (set_value(&i->north, l[1], mlx, ind));
	if (!cmp(l[0], "SO"))
		return (set_value(&i->south, l[1], mlx, ind));
	if (!cmp(l[0], "WE"))
		return (set_value(&i->west, l[1], mlx, ind));
	return (set_value(&i->east, l[1], mlx, ind));
}

int	set_a_color(int i, char *values, uint32_t *color, bool *is_set)
{
	char	**rgb;

	if (*is_set)
		return (lerr(i, "duplicate ID"), -1);
	if (nb_occur(values, ',') != 2)
		return (lerr(i, "too much RGB values"), -1);
	rgb = ft_split(values, ",");
	if (!rgb)
		return (perr("Malloc error"), -1);
	if (!is_valid_int(rgb[0]) || !is_valid_int(rgb[1]) || !is_valid_int(rgb[2]))
		return (freeall(rgb), lerr(i,
				"There is an unvalid number (not in [0-255])"), -1);
	*color = (ft_atoi(rgb[0]) << 16) | (ft_atoi(rgb[1]) << 8) | ft_atoi(rgb[2]);
	*is_set = 1;
	freeall(rgb);
	return (0);
}

int	set_colors(t_infos *i, char **l, int ind)
{
	if (!cmp(l[0], "F"))
		return (set_a_color(ind, l[1], &i->floor, &i->f));
	return (set_a_color(ind, l[1], &i->ceil, &i->c));
}

int	set_a_value(t_infos *i, char **l, int ind, void *mlx)
{
	if (is_texture(l[0]))
		return (set_texture(i, l, ind, mlx));
	if (is_color(l[0]))
		return (set_colors(i, l, ind));
	return (lerr(ind, "Unvalid ID"), -1);
}
