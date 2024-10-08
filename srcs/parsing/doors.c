/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:23:25 by cviegas           #+#    #+#             */
/*   Updated: 2024/10/08 17:33:08 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void	derr(int i, int j, t_vars *v)
{
	ft_printf(STDERR,
				RED "Error\nMap: " RCOLOR LIL_RED "Door at line %d, column "
					"%d isn't between two walls\n" RCOLOR,
				v->infos.map_index + i,
				j);
}
static bool	is_unclosed_door(int i, int j, char **map)
{
	return (map[i][j] == 'D' && !((map[i - 1][j] == '1' && map[i + 1][j] == '1')
			|| (map[i][j - 1] == '1' && map[i][j + 1] == '1')));
}

bool	is_there_unclosed_doors(char **map, t_vars *v)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (is_unclosed_door(i, j, map))
				return (derr(i, j, v), 1);
		}
	}
	return (0);
}
