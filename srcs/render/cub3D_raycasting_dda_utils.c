/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_raycasting_dda_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:58:10 by pmagnero          #+#    #+#             */
/*   Updated: 2024/10/01 15:07:50 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/// @brief Utils function because of the fcking N0rMlnN3773
/// @param v 
void	dda_utils(t_vars *v)
{
	v->ray.wall_dist = (v->ray.sidedist_y - v->ray.deltadist_y);
	if (v->ray.side == 0)
		v->ray.wall_dist = (v->ray.sidedist_x - v->ray.deltadist_x);
	if (v->ray.img.id == EDOOR)
		check_door(v);
}
