/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_pathfinding.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:16:14 by pmagnero          #+#    #+#             */
/*   Updated: 2024/10/24 20:17:15 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	tracepath(t_vars *v, t_astar *astar)
{
	int (row) = astar->target->y;
	int (col) = astar->target->x;
	int	(tmprow) = 0;
	int	(tmpcol) = 0;
	int (i) = -1;
	int (j) = -1;
	t_pathfinding *(tmp) = NULL;
	// ft_printf(1, "\nThe path is r: %d, c: %d", row, col);
	// astar->open = new_cell(0.0, row, col);
	// if (!astar->open)
	// 	exit((prterr(v, ERRMALL, 1, 1), 1));
	// add_cell(astar, &astar->open);
	// tmp = astar->open;
	ft_printf(1, "\nnb_astar: %d\n", astar->nb_astar);
	while (++i < v->mapv.maph)
	{
		j = -1;
		while (++j < v->mapv.mapw)
			if (astar->celld[i][j].parent_i != -1 && astar->celld[i][j].parent_j != -1)
				ft_printf(1, "-> |(%d,%d)(%d,%d)|",
					astar->celld[i][j].parent_i, astar->celld[i][j].parent_j,
					i, j);
	}
	ft_printf(1, "\nThe path is ");
	while (!(astar->celld[row][col].parent_i == row
		&& astar->celld[row][col].parent_j == col))
	{
		ft_printf(1, "OI-> (%d,%d) ", row, col);
		tmp = new_cell(0.0, row, col);
		if (!tmp)
			exit((prterr(v, ERRMALL, 1, 1), 1));
		add_cell(astar, &tmp);
		tmprow = astar->celld[row][col].parent_i;
		tmpcol = astar->celld[row][col].parent_j;
		row = tmprow;
		col = tmpcol;
	}
	tmp = new_cell(0.0, row, col);
	if (!tmp)
		exit((prterr(v, ERRMALL, 1, 1), 1));
	add_cell(astar, &tmp);
	tmp = astar->open;
	i = -1;
	while (++i < astar->nb_astar && tmp)
	{
		ft_printf(1, "-> (%d,%d) ", tmp->i, tmp->j);
		// astar->next = tmp->next;
		// astar->del = tmp;
		// if (!astar->open || !astar->del)
		// 	break ;
		// if (astar->open == astar->del)
		// 	astar->open = astar->del->next;
		// astar->del->next->prev = astar->del->prev;
		// astar->del->prev->next = astar->del->next;
		// free((astar->nb_astar--, astar->del));
		tmp = tmp->next;
	}
	ft_printf(1, "KEK\n");
}

/// @brief Check if we reached the destination cell
/// @param src Source cell
/// @param dst Destination cell
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
double	calculatehvalue(t_map *s, t_map *d)
{
	return ((double)sqrt((s->x - d->x) * (s->x - d->x)
			+ (s->y - d->y) * (s->y - d->y)));
}

/**
 * @brief Generating one successor of the cell
 * @param v 		Vars
 * @param astar 	Structure holding datas
 * @param tmp 		Current node of the open linked list
 * @param i 		Row index
 * @param j 		Column index
 * 
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
*/
bool	generate_successor(t_vars *v, t_astar *astar, t_pathfinding *tmp, int i, int j, t_map *dir)
{
	if (dir->val != '1' && dir->val != 'D')
	{
		// printf("currx: %d, curry: %d\n", astar->curr->x, astar->curr->y);
		// printf("dirx: %d, diry: %d\n", dir->x, dir->y);
		if (isdestination(dir, astar->target))
		{
			astar->celld[i][j].parent_i = i;
			astar->celld[i][j].parent_j = j;
			ft_printf(1, "The destination has been reached\n");
			tracepath(v, astar);
			astar->finddst = true;
			return (true);
		}
		else if (!astar->closedlst[i][j] && dir->val != '1' && dir->val != 'D')
		{
			astar->gnew = astar->celld[i][j].g + 1.0;
			astar->hnew = calculatehvalue(dir, astar->target);
			// printf("hnew: %f\n", astar->hnew);
			astar->fnew = astar->gnew + astar->hnew;
			if (astar->celld[i][j].f == __FLT_MAX__
				|| astar->celld[i][j].f > astar->fnew)
			{
				tmp = new_cell(astar->fnew, i, j);
				if (!tmp)
					exit((prterr(v, ERRMALL, 1, 1), 1));
				// printf("newi: %d, newj: %d\n", tmp->i, tmp->j);
				// printf("dirnewi: %d, dirnewj: %d\n", dir->x, dir->y);
				tmp->curr = dir;
				add_cell(astar, &tmp);
				astar->celld[i][j].f = astar->fnew;
				astar->celld[i][j].g = astar->gnew;
				astar->celld[i][j].h = astar->hnew;
				astar->celld[i][j].parent_i = i;
				astar->celld[i][j].parent_j = j;
			}
		}
	}
	return (false);
}

/// @brief Generate all the 8 successors of the cell
/// @param v Vars
/// @param astar Structure holding datas
/// @param tmp Current node of the open linked list
/// @return 
bool	generate_successors(t_vars *v, t_astar *astar, t_pathfinding *tmp)
{
//----------- 1st Successor (North) ------------
	// printf("generate successor North\n");
	if (generate_successor(v, astar, tmp, astar->i - 1, astar->j, astar->curr->up))
		return (true);
//----------- 2nd Successor (South) ------------
	// printf("generate successor South\n");
	if (generate_successor(v, astar, tmp, astar->i + 1, astar->j, astar->curr->down))
		return (true);
//----------- 3nd Successor (EAST) ------------
	// printf("generate successor East\n");
	if (generate_successor(v, astar, tmp, astar->i, astar->j + 1, astar->curr->right))
		return (true);
//----------- 4nd Successor (WEST) ------------
	// printf("generate successor West\n");
	if (generate_successor(v, astar, tmp, astar->i, astar->j - 1, astar->curr->left))
		return (true);
//----------- 5nd Successor (North-East) ------------
	// printf("generate successor North-East\n");
	if (generate_successor(v, astar, tmp, astar->i - 1, astar->j + 1, astar->curr->up->right))
		return (true);
//----------- 6nd Successor (North-WEST) ------------
	// printf("generate successor North-West\n");
	if (generate_successor(v, astar, tmp, astar->i - 1, astar->j - 1, astar->curr->up->left))
		return (true);
//----------- 7nd Successor (South-East) ------------
	// printf("generate successor South-East\n");
	if (generate_successor(v, astar, tmp, astar->i + 1, astar->j + 1, astar->curr->down->right))
		return (true);
//----------- 8nd Successor (South-WEST) ------------
	// printf("generate successor South-West\n");
	if (generate_successor(v, astar, tmp, astar->i + 1, astar->j - 1, astar->curr->down->left))
		return (true);
	return (astar->curr = tmp->curr, false);
}

/// @brief Pathfinding algorithm
/// @param v Vars
/// @param astar Structure holding datas
bool	astar(t_vars *v, t_astar *astar)
{
	t_pathfinding	*tmp;

	int (k) = -1;
	astar->finddst = false;
	if (isdestination(astar->curr, astar->target))
		return (printf("We are already at the destination\n"));
	astar->i = -1;
	while (++astar->i < v->mapv.maph)
	{
		astar->j = -1;
		while (++astar->j < v->mapv.mapw)
		{
			astar->celld[astar->i][astar->j].f = __FLT_MAX__;
			astar->celld[astar->i][astar->j].g = __FLT_MAX__;
			astar->celld[astar->i][astar->j].h = __FLT_MAX__;
			astar->celld[astar->i][astar->j].parent_i = -1;
			astar->celld[astar->i][astar->j].parent_j = -1;
		}
	}
	astar->i = astar->curr->y;
	astar->j = astar->curr->x;
	astar->celld[astar->i][astar->j].f = 0.0;
	astar->celld[astar->i][astar->j].g = 0.0;
	astar->celld[astar->i][astar->j].h = 0.0;
	astar->celld[astar->i][astar->j].parent_i = astar->i;
	astar->celld[astar->i][astar->j].parent_j = astar->j;
	astar->open = new_cell(0.0, astar->i, astar->j);
	if (!astar->open)
		exit((prterr(v, ERRMALL, 1, 1), 1));
	add_cell(astar, &astar->open);
	tmp = astar->open;
	tmp->curr = astar->curr;
	(void)k;
	while (tmp)//++k < astar->nb_astar && 
	{
		astar->i = tmp->i;
		astar->j = tmp->j;
		ft_printf(1, "i: %d, j: %d\n", tmp->i, tmp->j);
		astar->next = tmp->next;
		astar->del = tmp;
		if (!astar->open || !astar->del)
			break ;
		if (astar->open == astar->del)
			astar->open = astar->del->next;
		astar->del->next->prev = astar->del->prev;
		astar->del->prev->next = astar->del->next;
		free((k--, astar->nb_astar--, astar->del));
		tmp = astar->next;
		astar->closedlst[astar->i][astar->j] = true;
		if (generate_successors(v, astar, tmp))
			return (true);
	}
	if (!astar->finddst)
		printf("Failed to find the Destination Cell\n");
	return (false);
}
