/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_floodfill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 21:51:47 by cviegas           #+#    #+#             */
/*   Updated: 2024/09/18 21:53:16 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

bool	needs_to_be_surrounded(char c)
{
	return (c == 'N' || c == 'O' || c == 'S' || c == 'W' || c == '0'
		|| c == 'D');
}

bool	is_surrounded(char **map, int i, int j)
{
	(void)map;
	(void)i;
	(void)j;
	return (1);
}

bool	is_map_closed(char **map)
{
	int i;
	int j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (needs_to_be_surrounded(map[i][j]))
			{
				if (!is_surrounded(map, i, j))
					return (cerr(i, j), 0);
			}
		}
	}
	return (1);
}