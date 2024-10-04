/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_floodfill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 21:51:47 by cviegas           #+#    #+#             */
/*   Updated: 2024/09/19 12:34:13 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

bool	needs_to_be_surrounded(char c)
{
	return (c == 'N' || c == 'O' || c == 'S' || c == 'W' || c == '0'
		|| c == 'D');
}

bool	is_not_accepted(char **map, int i, int j)
{
	return (i == 0 || j == 0 || !map[i] || !map[i][j] || is_in_string(map[i][j],
			WHITESPACES));
}

bool	is_surrounded_aux(char **map, int i, int j, size_t map_start)
{
	if (!map[i])
		return (cerr(i + map_start, j), 0);
	if (map[i][j] == '1' || map[i][j] == 'V')
		return (1);
	if (is_not_accepted(map, i, j))
		return (cerr(i + map_start, j), 0);
	map[i][j] = 'V';
	return (is_surrounded_aux(map, i + 1, j, map_start)
		&& is_surrounded_aux(map, i, j + 1, map_start) && is_surrounded_aux(map,
			i - 1, j, map_start) && is_surrounded_aux(map, i, j - 1,
			map_start));
}

bool	is_surrounded(char **map, int i, int j, size_t map_start)
{
	char	**temp;
	bool	res;

	temp = tab_dup(map);
	res = is_surrounded_aux(temp, i, j, map_start);
	return (freeall(temp), res);
}

bool	is_map_closed(char **map, size_t map_start)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (needs_to_be_surrounded(map[i][j]))
			{
				if (!is_surrounded(map, i, j, map_start))
					return (0);
			}
		}
	}
	return (1);
}
