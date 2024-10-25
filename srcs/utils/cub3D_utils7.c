/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:13:00 by pmagnero          #+#    #+#             */
/*   Updated: 2024/04/05 12:19:12 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/// @brief 
/// @param v 
/// @param actors 
/// @param node 
void	add_cell(t_astar *astar, t_pathfinding **node, t_pathfinding **lst)
{
	astar->nb_astar++;
	if (!(*lst))
		(*lst) = (*node);
	else
	{
		(*node)->next = (*lst);
		(*node)->prev = (*lst)->prev;
		if ((*lst)->next == (*lst))
			(*lst)->next = (*node);
		else
			(*lst)->prev->next = (*node);
		(*lst)->prev = (*node);
	}
}

/// @brief Create a new node in the linked list
/// @param v Vars
/// @param a Pointer of the current node
/// @param p Node data
/// @return The new node to add to the linked list
t_pathfinding	*new_cell(double f, int i, int j, t_map *dir)
{
	t_pathfinding	*node;

	node = (t_pathfinding *)ft_calloc(1, sizeof(t_pathfinding));
	if (!node)
		return (NULL);
	node->f = f;
	node->i = i;
	node->j = j;
	node->curr = dir;
	node->next = node;
	node->prev = node;
	return (node);
}

/// @brief Clear double of cells
/// @param tab Double array of cells
/// @return 
int	cells_clear(t_cell **tab)
{
	int	i;

	i = -1;
	if (!tab)
		return (0);
	while (tab[++i])
		free(tab[i]);
	free(tab);
	tab = NULL;
	return (0);
}

/// @brief Clear double boolean array
/// @param tab Double boolean array
/// @return 
int	booltab_clear(bool **tab)
{
	int	i;

	i = -1;
	if (!tab)
		return (0);
	while (tab[++i])
		free(tab[i]);
	free(tab);
	tab = NULL;
	return (0);
}

/// @brief Clear a linked list 
/// @param astar Structure holding datas of the pathfinding algorithm
void	clear_lst(t_astar *astar)
{
	int				i;
	t_pathfinding	*tmp;

	i = -1;
	tmp = astar->open;
	while (++i < astar->nb_astar && tmp)
		tmp = del_node(astar, &i, &astar->open, &tmp);
	astar->open = NULL;
}
