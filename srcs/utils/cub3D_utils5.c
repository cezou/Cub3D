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

/// @brief Print the linked list and the content of each node for debug purpose
/// @param v Vars
/// @return 
int	printactors(t_vars *v)
{
	t_actor	*tmp;
	t_actor	*head;

	head = v->actors;
	tmp = v->actors->next;
	printf("Actors: \n");
	while (tmp != head)
	{
		printf("img: %d x: %f y: %f", tmp->img_i,
			tmp->x, tmp->y);
		printf("\n");
		tmp = tmp->next;
	}
	printf("img: %d x: %f y: %f", tmp->img_i,
		tmp->x, tmp->y);
	printf("\n");
	return (0);
}

/// @brief Add a new element to the linked list
/// @param v Vars
/// @param actors The pointer to the first element of the linked list
/// @param node New node to add to linked list
void	add_actor(t_vars *v, t_actor **actors, t_actor **node)
{
	v->game.nb_actors++;
	if (!(*actors))
		(*actors) = (*node);
	else
	{
		(*node)->next = (*actors);
		(*node)->prev = (*actors)->prev;
		if ((*actors)->next == (*actors))
			(*actors)->next = (*node);
		else
			(*actors)->prev->next = (*node);
		(*actors)->prev = (*node);
	}
}

/// @brief Create a new node in the linked list
/// @param v Vars
/// @param a Pointer of the current node
/// @param p Node data
/// @return The new node to add to the linked list
t_actor	*new_actor(t_vars *v)
{
	t_actor	*node;

	(void)v;
	node = (t_actor *)ft_calloc(1, sizeof(t_actor));
	if (!node)
		return (NULL);
	return (node);
}

/// @brief Clear the linked list
/// @param lst Linked list
/// @return
int	actors_clear(t_actor *lst)
{
	t_actor	*temp;
	t_actor	*head;

	head = lst;
	if (!lst)
		return (1);
	while (lst)
	{
		temp = (lst)->next;
		if (lst->astar.celld)
			cells_clear(lst->astar.celld);
		if (lst->astar.closedlst)
			booltab_clear(lst->astar.closedlst);
		if (lst->astar.open)
			free(lst->astar.open);
		free(lst);
		lst = temp;
		if (temp == head)
			break ;
	}
	return (1);
}
