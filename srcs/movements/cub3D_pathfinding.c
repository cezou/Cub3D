/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_pathfinding.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:16:14 by pmagnero          #+#    #+#             */
/*   Updated: 2024/10/27 14:48:03 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/// @brief A Utility Function to calculate the 'h' heuristics.
/// @param s Map position source
/// @param d Map position destination
/// @return Distance value between position source and destination position
double	calculatehvalue(t_map *s, t_map *d)
{
	return (sqrt((s->x - d->x) * (s->x - d->x)
			+ (s->y - d->y) * (s->y - d->y)));
}

/**
 * @brief Generating one successor of the cell
 * @param v 		Vars
 * @param astar 	Structure holding datas
 * @param p 		Pair value
 * @param dir 		Map square to test
 * 
 * @code
 *   N.W  N  N.E
 *     \  |  /
 * 	    \ | /
 *  W----Cell----E
 * 	    / | \
 *     /  |  \
 *   S.W  S  S.E
 * 
 * Cell-->Popped Cell (i, j)
 * N -->  North       (i-1, j)
 * S -->  South       (i+1, j)
 * E -->  East        (i, j+1)
 * W -->  West           (i, j-1)
 * N.E--> North-East  (i-1, j+1)
 * N.W--> North-West  (i-1, j-1)
 * S.E--> South-East  (i+1, j+1)
 * S.W--> South-West  (i+1, j-1)
 * @endcode
*/
bool	gen_succ(t_vars *v, t_astar *astar, t_pair p, t_map *dir)
{
	if (isdestination(dir, astar->target))
	{
		astar->celld[p.i][p.j].parent_i = astar->i;
		astar->celld[p.i][p.j].parent_j = astar->j;
		return (astar->celld[p.i][p.j].map = dir, astar->finddst = true, true);
	}
	else if (astar->closedlst[p.i][p.j] == false
		&& dir->val != '1' && dir->val != 'D')
	{
		astar->gnew = astar->celld[astar->i][astar->j].g + 1.0;
		astar->hnew = calculatehvalue(dir, astar->target);
		astar->fnew = astar->gnew + astar->hnew;
		if (astar->celld[p.i][p.j].f == __FLT_MAX__
			|| astar->celld[p.i][p.j].f > astar->fnew)
		{
			check_and_insert_node(v, astar, p, dir);
			astar->celld[p.i][p.j].f = astar->fnew;
			astar->celld[p.i][p.j].g = astar->gnew;
			astar->celld[p.i][p.j].h = astar->hnew;
			astar->celld[p.i][p.j].parent_i = astar->i;
			astar->celld[p.i][p.j].parent_j = astar->j;
			astar->celld[p.i][p.j].map = dir;
		}
	}
	return (false);
}

/// @brief Generate all the 8 successors of the cell
/// @param v Vars
/// @param astar Structure holding datas
/// @param tmp Current node of the open linked list
/// @return 
bool	generate_successors(t_vars *v, t_astar *astar)
{
	if (gen_succ(v, astar, (t_pair){astar->i - 1, astar->j},
		astar->curr->up))
		return (true);
	if (gen_succ(v, astar, (t_pair){astar->i + 1, astar->j},
		astar->curr->down))
		return (true);
	if (gen_succ(v, astar, (t_pair){astar->i, astar->j + 1},
		astar->curr->right))
		return (true);
	if (gen_succ(v, astar, (t_pair){astar->i, astar->j - 1},
		astar->curr->left))
		return (true);
	if (gen_succ(v, astar, (t_pair){astar->i - 1, astar->j + 1},
		astar->curr->up->right))
		return (true);
	if (gen_succ(v, astar, (t_pair){astar->i - 1, astar->j - 1},
		astar->curr->up->left))
		return (true);
	if (gen_succ(v, astar, (t_pair){astar->i + 1, astar->j + 1},
		astar->curr->down->right))
		return (true);
	if (gen_succ(v, astar, (t_pair){astar->i + 1, astar->j - 1},
		astar->curr->down->left))
		return (true);
	return (false);
}

/// @brief Init astar algorithm datas 
/// @param v Vars
/// @param astar Structure holding datas
/// @return 
// ft_printf(1, "We are already at the destination\n"), 
bool	init_astar(t_vars *v, t_astar *astar)
{
	if (isdestination(astar->curr, astar->target))
		return (false);
	astar->i = -1;
	while (++astar->i < v->mapv.maph)
	{
		astar->j = -1;
		while (++astar->j < v->mapv.mapw)
		{
			astar->closedlst[astar->i][astar->j] = false;
			astar->celld[astar->i][astar->j].f = __FLT_MAX__;
			astar->celld[astar->i][astar->j].g = __FLT_MAX__;
			astar->celld[astar->i][astar->j].h = __FLT_MAX__;
			astar->celld[astar->i][astar->j].parent_i = -1;
			astar->celld[astar->i][astar->j].parent_j = -1;
			astar->celld[astar->i][astar->j].map = NULL;
		}
	}
	astar->i = astar->curr->y;
	astar->j = astar->curr->x;
	astar->celld[astar->i][astar->j].f = 0.0;
	astar->celld[astar->i][astar->j].g = 0.0;
	astar->celld[astar->i][astar->j].h = 0.0;
	astar->celld[astar->i][astar->j].parent_i = astar->i;
	astar->celld[astar->i][astar->j].parent_j = astar->j;
	return (astar->celld[astar->i][astar->j].map = astar->curr, true);
}

/// @brief Pathfinding algorithm
/// @param v Vars
/// @param astar Structure holding datas
bool	astar(t_vars *v, t_astar *astar)
{
	t_pathfinding	*tmp;

	astar->nb_astar = 0;
	astar->finddst = false;
	if (!init_astar(v, astar))
		return (false);
	tmp = new_cell(0.0, astar->i, astar->j, astar->curr);
	if (!tmp)
		exit((prterr(v, ERRMALL, 1, 1), 1));
	add_cell(astar, &tmp, &astar->open);
	while (astar->open)
	{
		astar->i = astar->open->i;
		astar->j = astar->open->j;
		astar->curr = astar->open->curr;
		astar->next = astar->open->next;
		erase_head(astar, &astar->open);
		astar->closedlst[astar->i][astar->j] = true;
		if (generate_successors(v, astar))
			return (clear_lst(astar, &astar->open), tracepath(v, astar), true);
	}
	return (clear_lst(astar, &astar->open), false);
}
// if (!astar->finddst)
	// ft_printf(1, "Failed to find the Destination Cell\n");
// ft_printf(1, "The destination has been reached\n"),