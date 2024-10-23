/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_pathfinding.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:16:14 by pmagnero          #+#    #+#             */
/*   Updated: 2024/10/23 23:36:52 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

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

/// @brief A Utility Function to calculate the 'h' heuristics.
/// @param s Map position source
/// @param d Map position destination
/// @return Distance value between position source and destination position
double calculateHValue(t_map *s, t_map *d)
{
    // Return using the distance formula
    return ((double)sqrt(
        (s->x - d->x) * (s->x - d->x)
        + (s->y - d->y) * (s->y - d->y)));
}

/*
Generating all the 8 successor of this cell

	  N.W  N  N.E
	    \  |  /
		 \ | /
	W----Cell----E
		 / | \
	    /  |  \
	  S.W  S  S.E

Cell-->Popped Cell (i, j)
N -->  North       (i-1, j)
S -->  South       (i+1, j)
E -->  East        (i, j+1)
W -->  West           (i, j-1)
N.E--> North-East  (i-1, j+1)
N.W--> North-West  (i-1, j-1)
S.E--> South-East  (i+1, j+1)
S.W--> South-West  (i+1, j-1)
*/

void	generate_successor(t_map *map, t_cell **celldetails, bool **closedlst, int i, int j)
{
	if (map->up->val == 0)
	{
		if (isdestination(map->up, map))
		{
			celldetails[i - 1][j].parent_i = i;
			celldetails[i - 1][j].parent_j = j;
			ft_printf("The destination has been reached\n");
			// tracePath(cellDetails, dest);
			finddst = true;
			return (true);
		}
		else if (!closedlst[i - 1][j] && map->up->val == 0)
		{
			gnew = celldetails[i - 1][j].g + 1.0;
			hnew = calculateHValue(map->up, v->player.player);
			fnew = gnew + hnew;
			if (celldetails[i - 1][j].f == __FLT_MAX__
				|| celldetails[i - 1][j].f > fnew)
			{
				tmp = new_cell(fnew, i - 1, j);
				if (!tmp)
					exit((prterr(v, ERRMALL, 1, 1), 1));
				add_cell(&actor->astar, &tmp, actor);
				celldetails[i][j].f = fnew;
				celldetails[i][j].g = gnew;
				celldetails[i][j].h = hnew;
				celldetails[i][j].parent_i = i;
				celldetails[i][j].parent_j = j;
			}
		}
	}
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
	t_pathfinding	*del;
	t_pathfinding	*next;
	t_map			*map;
	int				i;
	int				j;
	bool			finddst;
	double			gnew;
	double			hnew;
	double			fnew;

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
	tmp = new_cell(0.0, i, j);
	if (!tmp)
		exit((prterr(v, ERRMALL, 1, 1), 1));
	add_cell(&actor->astar, &tmp, actor);
	map = actor->map_pos;
	while (tmp)
	{
		i = tmp->i;
		j = tmp->j;

// Delete the node
		next = tmp->next;
		del = tmp;
		if (!actor->astar || !del)
			return (next);
		if (actor->astar == del)
			actor->astar = del->next;
		del->next->prev = del->prev;
		del->prev->next = del->next;
		free((actor->nb_astar--, del));

		closedlst[i][j] = true;
//----------- 1st Successor (North) ------------
		generate_successor();
	}
	if (!finddst)
		printf("Failed to find the Destination Cell\n");
	return (false);
}
