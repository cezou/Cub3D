/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_pathfinding_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:16:14 by pmagnero          #+#    #+#             */
/*   Updated: 2024/10/25 23:19:48 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"


/// @brief Delete a node from a linked list
/// @param astar Structure holding datas of the pathfinding algorithm
/// @param k Iterator of the linked list
/// @param head Head of the linked list
/// @param node Node to delete in the linked list
/// @return The next node in the linked list
t_pathfinding	*del_node(t_astar *astar, int *k, t_pathfinding **head,
					t_pathfinding **node)
{
	t_pathfinding	*del;
	t_pathfinding	*next;
	t_pathfinding	*tmp;

	tmp = *node;
	next = tmp->next;
	del = tmp;
	if (!(*head) || !del)
		return (next);
	if ((*head) == del)
		(*head) = del->next;
	del->next->prev = del->prev;
	del->prev->next = del->next;
	free(((*k)--, astar->nb_astar--, del));
	return (next);
}

/// @brief Erase the head from the linked list
/// @param astar Structure holding datas of the pathfinding algorithm
void	erase_head(t_astar *astar)
{
	if (astar->nb_astar == 1)
	{
		free((astar->nb_astar--, astar->open));
		astar->open = NULL;
	}
	else
	{
		astar->open->next->prev = astar->open->prev;
		astar->open->prev->next = astar->open->next;
		free(astar->open);
		astar->open = astar->next;
		astar->nb_astar--;
	}
}

/// @brief Utilitary function to print the generated path by the astar algorithm
/// @param v Vars
/// @param astar Structure holding datas of the pathfinding algorithm
void	tracepath(t_vars *v, t_astar *astar)
{
	int (row) = astar->target->y;
	int (col) = astar->target->x;
	int (tmprow) = 0;
	int (tmpcol) = 0;
	int (i) = -1;
	t_pathfinding *(tmp) = NULL;
	clear_lst(astar);
	astar->nb_astar = 0;
	tmp = astar->trace;
	ft_printf(1, "\nThe path is \n");
	while (!(astar->celld[row][col].parent_i == row
		&& astar->celld[row][col].parent_j == col))
	{
		tmp = new_cell(0.0, row, col, NULL);
		if (!tmp)
			exit((prterr(v, ERRMALL, 1, 1), 1));
		add_cell(astar, &tmp, &astar->trace);
		tmprow = astar->celld[row][col].parent_i;
		tmpcol = astar->celld[row][col].parent_j;
		row = tmprow;
		col = tmpcol;
	}
	tmp = new_cell(0.0, row, col, NULL);
	if (!tmp)
		exit((prterr(v, ERRMALL, 1, 1), 1));
	add_cell(astar, &tmp, &astar->trace);
	tmp = astar->trace;
	i = -1;
	while (++i < astar->nb_astar && astar->trace)
	{
		ft_printf(1, "-> (%d,%d)\n", astar->trace->i, astar->trace->j);
		tmp = del_node(astar, &i, &astar->trace, &astar->trace);
	}
}

/// @brief Check if a node exist in a linked list
/// @param astar Structure holding datas of the pathfinding algorithm
/// @param i Value to check
/// @param j Value to check
/// @return Boolean if the node exist or not
bool	check_node_exist(t_astar *astar, int i, int j)
{
	t_pathfinding	*tmp;
	int				k;

	k = -1;
	tmp = astar->open;
	while (++k < astar->nb_astar && tmp)
	{
		if (tmp->i == i && tmp->j == j)
			return (true);
		tmp = tmp->next;
	}
	return (false);
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
