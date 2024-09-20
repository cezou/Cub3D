/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:09:37 by pmagnero          #+#    #+#             */
/*   Updated: 2024/09/20 15:37:54 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/// @brief Convert radian to degre
/// @param rad Radian angle
/// @return Angle in degre
float	rad_to_deg(float rad)
{
	float	deg;

	deg = rad * (180 / M_PI);
	if (deg < 0)
		deg += 360;
	return (deg);
}

/// @brief Convert degre to radian
/// @param deg Degre angle
/// @return Angle in radian
float	deg_to_rad(float deg)
{
	return (deg * (M_PI / 180));
}

/// @brief Add a 90 degre angle to the coordinates x,y with the direction
/// @param dir Direction of the vector
/// @param x 
/// @param y 
/// @return Transformed coordinates
t_point2	get_90_angle(int dir, double x, double y)
{
	double		deg;
	double		rad;
	t_point2	p;

	deg = rad_to_deg(atan2(y, x)) + (90 * dir);
	rad = deg_to_rad(deg);
	p.x = (cos(rad));
	p.y = (sin(rad));
	p.x += x;
	p.y += y;
	deg = (atan2(p.y - y, p.x - x));
	return ((t_point2){cos(deg), sin(deg), 0, 0});
}
