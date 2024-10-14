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

void	ft_swaps_adjacent_nodes(t_actor **node1, t_actor **node2,
			t_actor **next2, t_actor **prev1)
{
	(*node1)->next = *next2;
	(*node2)->prev = *prev1;
	(*node1)->prev = *node2;
	(*node2)->next = *node1;
	if (*next2)
		(*next2)->prev = *node1;
	if (*prev1)
		(*prev1)->next = *node2;
}

void	ft_swaps_update_head(t_actor **head, t_actor **node1, t_actor **node2)
{
	if (*head == *node1)
		*head = *node2;
	else if (*head == *node2)
		*head = *node1;
}

/// @brief Swap two nodes
/// @param head Head
/// @param node1 Node1
/// @param node2 Node2
void	ft_swaps(t_actor **head, t_actor *node1, t_actor *node2)
{
	t_actor	*prev1;
	t_actor	*next1;
	t_actor	*prev2;
	t_actor	*next2;

	if (node1 == node2)
		return ;
	prev1 = node1->prev;
	next1 = node1->next;
	prev2 = node2->prev;
	next2 = node2->next;
	if (next1 == node2)
		ft_swaps_adjacent_nodes(&node1, &node2, &next2, &prev1);
	else
	{
		prev1->next = node2;
		next1->prev = node2;
		prev2->next = node1;
		next2->prev = node1;
		node1->next = next2;
		node1->prev = prev2;
		node2->next = next1;
		node2->prev = prev1;
	}
	ft_swaps_update_head(head, &node1, &node2);
}

/// @brief Sort in descending order the two ways circular linked list
/// @param head Head
void	sort_descending(t_actor **head)
{
	bool	swapped;
	t_actor	*current;
	t_actor	*last_sorted;

	if (*head == NULL || (*head)->next == *head)
		return ;
	swapped = true;
	last_sorted = NULL;
	while (swapped)//&& last_sorted != *head
	{
		swapped = false;
		current = *head;
		while (current->next != *head && current->next != last_sorted)
		{
			if (current->dist < current->next->dist)
			{
				ft_swaps(head, current, current->next);
				swapped = true;
			}
			else
				current = current->next;
		}
		last_sorted = current;
	}
}
