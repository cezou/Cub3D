/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_pathfinding.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:16:14 by pmagnero          #+#    #+#             */
/*   Updated: 2024/10/22 19:32:11 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

// A structure to hold the necessary parameters
typedef struct s_cell
{
	// Row and Column index of its parent
	// Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
	int		parent_i;
	int		parent_j;
	// f = g + h
	double	f;
	double	g;
	double	h;
}	t_cell;

/// @brief 
/// @param src 
/// @param dst 
/// @return 
bool	isdestination(t_map *src, t_map *dst)
{
	if (src->x == dst->x && src->y == dst->y)
		return (true);
	else
		return (false);
}

/// @brief 
/// @param v 
/// @param src 
/// @param dst 
bool	astar(t_vars *v, t_actor *actor, t_map *src, t_map *dst)
{
	bool			closedlst[v->mapv.mapw][v->mapv.maph];
	t_cell			celldetails[v->mapv.mapw][v->mapv.maph];
	t_pathfinding	*tmp;
	int				i;
	int				j;
	bool			finddst;

	finddst = false;
	ft_memset(closedlst, false, sizeof(closedlst));
	if (isdestination(src, dst))
		return (printf("We are already at the destination\n"));

	i = -1;
	while (++i < v->mapv.mapw)
	{
		j = -1;
		while (++j < v->mapv.maph)
		{
			celldetails[i][j].f = __FLT_MAX__;
			celldetails[i][j].g = __FLT_MAX__;
			celldetails[i][j].h = __FLT_MAX__;
			celldetails[i][j].parent_i = -1;
			celldetails[i][j].parent_j = -1;
		}
	}
	i = src->x;
	j = src->y;
	celldetails[i][j].f = 0.0;
	celldetails[i][j].g = 0.0;
	celldetails[i][j].h = 0.0;
	celldetails[i][j].parent_i = i;
	celldetails[i][j].parent_j = j;
	tmp = (t_pathfinding *)ft_calloc(1, sizeof(t_pathfinding));
	if (!tmp)
		exit((prterr(v, ERRMALL, 1, 1), 1));
	tmp->f = 0.0;
	tmp->i = i;
	tmp->j = j;
	tmp->next = tmp;
	tmp->prev = tmp;
	add_cell(v, &actor->astar, &tmp, actor);
	while (tmp)
	{
		break ;
		// tmp = tmp->next;
	}
	if (!finddst)
		printf("Failed to find the Destination Cell\n");
	return (false);
}
