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
void	sort_descending(t_actor **head, int bound, bool swapped,
		t_actor *last_sorted)
{
	t_actor	*current;

	if (*head == NULL || (*head)->next == *head)
		return ;
	while (swapped && last_sorted != *head)
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
			if (++bound >= 10000)
				return ;
		}
		last_sorted = current;
	}
}

// void	list_splice(t_actor *plft, t_actor *prgt)
// {
// 	t_actor	*pnod;

// 	pnod = prgt;
// 	prgt->prev->next = prgt->next;      /* remove right node */
// 	prgt->next->prev = prgt->prev;
// 	prgt->prev = plft->prev;            /* insert right node */
// 	prgt->next = plft;                  /*  before left node */
// 	plft->prev->next = prgt;
// 	plft->prev = prgt;
// }

// void	sort_descending(t_actor **list)
// {
// 	t_actor	*pFst;                      /* first node of list */
// 	t_actor	*pOld;                      /* beg old list */
// 	t_actor	*pNxt;                      /* nxt old list */
// 	t_actor	*pNew;                      /* cur new list */

// 	if (list == NULL || *list == NULL)   /* check for null ptr */
// 		return ;
// 	pFst = *list;
// 	if (pFst == pFst->next)              /* check for single node */
// 		return ;
// 	pNxt = pFst->next;                  /* insert old into new */
// 	pOld = pNxt;
// 	while (pOld != pFst)
// 	{
// 		pNxt = pOld->next;
// 		pNew = pFst;
// 		while (pNew != pOld && pNew->dist > pOld->dist)
// 			pNew = pNew->next;
// 		if (pNew != pOld)
// 		{
// 			list_splice(pNew, pOld);
// 			if (pNew == pFst)
// 				pFst = pOld;
// 		}
// 		pOld = pNxt;
// 	}
// 	*list = pFst;                       /* update ptr to list */
// }

// t_actor	*list_merge(t_actor *pLft, t_actor *pRgt, t_actor *pEnd)
// {
// 	t_actor	*pNod;
// 	t_actor	*pNxt;

// 	/* set ptr to fisrt node of merged list (return value) */
// 	pNod = (pRgt->dist < pLft->dist) ? pRgt : pLft;
// 	while(1){                           /* merge lists */
// 		if(pRgt->dist < pLft->dist){
// 			pNxt = pRgt->next;
// 			list_splice(pLft, pRgt);
// 			pRgt = pNxt;
// 			if(pRgt == pEnd)
// 				return pNod;
// 		} else {
// 			pLft = pLft->next;
// 			if(pLft == pRgt)
// 				return pNod;
// 		}
// 	}
// }

// #define ASZ 32
// void list_sort(struct Node** list)
// {
// struct Node* apNd[ASZ] = {NULL};        /* array of ptrs to runs */
// struct Node* pFst;                      /* first node of list */
// struct Node* pRgt;                      /* right pointer */
// struct Node* pEnd;                      /* end|wrk pointer */
// size_t i;

// 	if(list == NULL || *list == NULL)   /* check for null ptr */
// 		return;
// 	pFst = *list;
// 	if(pFst == pFst->next)              /* check for single node */
// 		return;
// 	pEnd = pFst;                        /* merge nodes into array */
// 	do{
// 		pRgt = pEnd;
// 		pEnd = pEnd->next;
// 		for(i = 0; i < ASZ && apNd[i] != NULL; i++){
// 			pRgt = list_merge(apNd[i], pRgt, pEnd);
// 			if(apNd[i] == pFst)
// 				pFst = pRgt;
// 			apNd[i] = NULL;
// 		}
// 		if(i == ASZ)                    /*   don't go past end array */
// 			i--;
// 		apNd[i] = pRgt;
// 	}while(pEnd != pFst);

// 	/* merge array into single sorted list */
// 	for(i = 0; i < ASZ && apNd[i] == NULL; i++);
// 	pRgt = apNd[i++];
// 	while(1){
// 		for( ; i < ASZ && apNd[i] == NULL; i++);
// 		if (i == ASZ)
// 			break;
// 		pRgt = list_merge(apNd[i++], pRgt, pEnd);
// 	}
// 	*list = pRgt;                       /* update ptr to list */
// }