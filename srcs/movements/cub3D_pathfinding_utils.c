/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_pathfinding_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:16:14 by pmagnero          #+#    #+#             */
/*   Updated: 2024/10/26 16:04:26 by pmagnero         ###   ########.fr       */
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
void	erase_head(t_astar *astar, t_pathfinding **lst)
{
	if (astar->nb_astar == 1)
	{
		free((astar->nb_astar--, *lst));
		*lst = NULL;
	}
	else
	{
		(*lst)->next->prev = (*lst)->prev;
		(*lst)->prev->next = (*lst)->next;
		free((*lst));
		(*lst) = astar->next;
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
	t_pathfinding *(tmp) = astar->trace;
	astar->nb_astar = 0;
	ft_printf(1, "\nThe path is \n");
	while (!(astar->celld[row][col].parent_i == row
		&& astar->celld[row][col].parent_j == col))
	{
		tmp = new_cell(0.0, row, col, astar->celld[row][col].map);
		if (!tmp)
			exit((prterr(v, ERRMALL, 1, 1), 1));
		add_cell(astar, &tmp, &astar->trace);
		tmprow = astar->celld[row][col].parent_i;
		tmpcol = astar->celld[row][col].parent_j;
		row = tmprow;
		col = tmpcol;
	}
	tmp = new_cell(0.0, row, col, astar->celld[row][col].map);
	if (!tmp)
		exit((prterr(v, ERRMALL, 1, 1), 1));
	add_cell(astar, &tmp, &astar->trace);
}

/// @brief Check if a node exist in a linked list
/// and insert it in the linked list
/// @param v Vars
/// @param astar Structure holding datas of the pathfinding algorithm
/// @param p Pair value to check
/// @param dir Map square to check
/// @return 
void	check_and_insert_node(t_vars *v, t_astar *astar, t_pair p,
			t_map *dir)
{
	t_pathfinding	*tmp;
	int				k;
	bool			exist;

	exist = false;
	k = -1;
	tmp = astar->open;
	while (++k < astar->nb_astar && tmp)
	{
		if (tmp->i == p.i && tmp->j == p.j)
			exist = true;
		tmp = tmp->next;
	}
	if (exist)
		return ;
	tmp = new_cell(astar->fnew, p.i, p.j, dir);
	if (!tmp)
		exit((prterr(v, ERRMALL, 1, 1), 1));
	add_cell(astar, &tmp, &astar->open);
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
