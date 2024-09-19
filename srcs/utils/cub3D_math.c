/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:09:37 by pmagnero          #+#    #+#             */
/*   Updated: 2024/09/17 17:33:35 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

float	rad_to_deg(float rad)
{
	float	deg;

	deg = rad * (180 / M_PI);
	if (deg < 0)
		deg += 360;
	return (deg);
}

float	deg_to_rad(float deg)
{
	return (deg * (M_PI / 180));
}

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
