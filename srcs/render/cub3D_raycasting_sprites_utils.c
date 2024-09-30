/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_raycasting_sprites_utils.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 21:30:54 by pmagnero          #+#    #+#             */
/*   Updated: 2024/09/30 17:42:05 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/// @brief Find guard in the guard array with its coordinates
/// @param v Vars
/// @param x X coordinate
/// @param y Y coordinate
/// @return Index of the guard in the guard array
int	find_guard(t_vars *v, int x, int y)
{
	int		i;

	i = -1;
	while (++i < v->game.nb_guard)
	{
		if (v->guard[i].x == x && v->guard[i].y == y)
			return (v->guard[i].img_i = EGUARDDEATH,
				v->guard[i].animoff = 0, i);
	}
	return (-1);
}
