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
/// @param i Increment variable
/// @return 
int	printmap(t_vars *v, int i)
{
	t_map	*tmp;

	ft_printf((tmp = v->mapv.map, 1), "MAP: %d, %d\n", v->mapv.mapw,
		v->mapv.maph);
	while (tmp)
	{
		ft_printf(1, "point %d x: %d y: %d z: %d val: %c ", i++, tmp->x, tmp->y,
			tmp->z, tmp->val);
		if (tmp->right)
			ft_printf(1, "rightval: %c rightx: %d righty: %d, ",
				tmp->right->val, tmp->right->x, tmp->right->y);
		if (tmp->left)
			ft_printf(1, "leftval: %c leftx: %d lefty: %d, ", tmp->left->val,
				tmp->left->x, tmp->left->y);
		if (tmp->up)
			ft_printf(1, "upval: %c upx: %d upy: %d, ", tmp->up->val,
				tmp->up->x, tmp->up->y);
		if (tmp->down)
			ft_printf(1, "downval: %c downx: %d downy: %d", tmp->down->val,
				tmp->down->x, tmp->down->y);
		ft_printf((tmp = tmp->right, 1), "\n");
	}
	ft_printf(1, "player pos: %d %d\n", v->player.player->x,
		v->player.player->y);
	return (0);
}

/// @brief Add a new element to the linked list
/// @param map The pointer to the first element of the linked list
/// @param node New node to add to linked list
/// @param tmp Temporary variable to go through the linked list
/// @param left Left node
void	add_element(t_map **map, t_map **node, t_map **tmp, t_map **left)
{
	if (!(*map))
		(*map) = (*node);
	else
	{
		(*tmp)->right = (*node);
		if ((*left))
			(*tmp)->left = (*left);
		(*left) = (*tmp);
		if ((*tmp)->up)
			(*tmp)->up->down = (*tmp);
		(*tmp) = (*tmp)->right;
	}
}

/// @brief Create a new node in the linked list
/// @param v Vars
/// @param val Value of the character read from the file
/// @param p Pointer of the current node
/// @return The new node to add to the linked list
t_map	*new_point(t_vars *v, char val, t_map **p)
{
	t_map	*node;

	node = (t_map *)malloc(sizeof(t_map));
	if (!node)
		return (NULL);
	node->x = v->mapv.tmpx;
	node->y = v->mapv.tmpy;
	node->right = NULL;
	node->left = NULL;
	node->down = NULL;
	node->up = *p;
	if (*p)
		*p = (*p)->right;
	if (val == 'N' || val == 'S' || val == 'E' || val == 'W')
		v->player.player = node;
	if (val == 'D')
		v->game.nb_door++;
	if (val == 'G')
		v->game.nb_guard++;
	return (node->val = val, node->rev = 0, node->z = 0, node);
}

/// @brief Find door in the door array with its coordinates
/// @param v Vars
/// @param x X coordinate
/// @param y Y coordinate
/// @return Index of the door in the door array
int	find_door(t_vars *v, int x, int y, int pouet)
{
	int		i;

	i = -1;
	while (++i < v->game.nb_door)
	{
		if (v->door[i].x == x && v->door[i].y == y)
		{
			if (pouet && v->player.player->x == v->door[i].x
				&& v->player.player->y == v->door[i].y)
				continue ;
			return (i);
		}
	}
	return (-1);
}

/// @brief Save img to another image with an offset
/// @param dest Image destination
/// @param src Image source
/// @param offset Offset of the src image
void	save_screen_to_buffer(t_imga dest, t_imga src, size_t offset)
{
	ft_memcpy(dest.addr + offset, src.addr,
		src.width * src.height * (src.bpp / 8));
}
