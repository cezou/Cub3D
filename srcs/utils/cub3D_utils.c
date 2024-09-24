/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 21:59:52 by pmagnero          #+#    #+#             */
/*   Updated: 2024/09/24 05:32:47 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/// @brief Print the map as it is in the file if we are in debug
/// @param v Vars
/// @return 
int	printmap2(t_vars *v)
{
	t_map	*tmp;

	tmp = v->mapv.map;
	if (!DEBUG)
		return (0);
	while (tmp)
	{
		if (tmp->x == 0)
			ft_printf(1, "\n");
		ft_printf(1, "%c", tmp->val);
		tmp = tmp->right;
	}
	ft_printf(1, "\n");
	return (0);
}

/// @brief Print an error in red + show the usage + clear datas of the program +
///	reset xset keyboard input delay
/// @param v Vars
/// @param err Error string to print
/// @param cleardatab Boolean to clear the datas
/// @param init Boolean to check if we are previous init or not
void	prterr(t_vars *v, char *err, int cleardatab, int init)
{
	ft_printf(2, "\n%s%s\n%s\n%s", RED, ERROR, err, RCOLOR);
	showparams(v);
	if (cleardatab)
		cleardata(v, init);
}

/// @brief Print usage and informations about the program in the console
/// @param v Vars
void	showparams(t_vars *v)
{
	(void)v;
	ft_printf(1, "%s%s", BLUE, CUB3D);
	ft_printf(1, "\n");
	ft_printf(1, "\nUsage: ./cub3D [map] [resolution]\n");
	ft_printf(1, "\n");
	ft_printf(1, "\tmap: map description file path with \".cub\" extension\n");
	ft_printf(1, "\n");
	ft_printf(1, "\tresolution: [width] [height]\n");
	ft_printf(1, "\t\t(default): 1024 768\n");
	ft_printf(1, "%s", RCOLOR);
	ft_printf(1, "\n%s", POTATO);
	ft_printf(1, "\n%s\t\t\t\t\t\t\tBy CESAIRE VIEGAS <cviegas@student.42.fr>%s\
", GREEN, RCOLOR);
	ft_printf(1, "\n%s\t\t\t\t\t\t\t+ PIERRE MAGNERON <pmagnero@student.42.fr>%s\
\n\n\n", GREEN, RCOLOR);
}

/// @brief Generate a random number(int) between 0 and n
/// @param nb Number max
/// @return The random number generated
int	myrand(int nb)
{
	if (!MANDATORY)
		return (rand() % nb);
	else
		return (0);
}

/// @brief Create and init an MLX image at the specified index in the img table
/// @param v Vars
/// @param index Index
void	initimage(t_vars *v, int index, int width, int height)
{
	v->img[index].img = mlx_new_image(v->mlx, width, height);
	if (!v->img[index].img)
		exit((prterr(v, "Error mlx map image\n", 1, 1), 1));
	v->img[index].addr = mlx_get_data_addr(v->img[index].img,
			&v->img[index].bpp, &v->img[index].len, &v->img[index].endian);
	if (!v->img[index].addr)
		exit((prterr(v, "Error mlx map image address\n", 1, 1), 1));
}
