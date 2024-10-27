/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:09:37 by pmagnero          #+#    #+#             */
/*   Updated: 2024/10/27 17:54:41 by pmagnero         ###   ########.fr       */
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

// if (v->sprites[i].state != EIDLE && v->sprites[i].state != EDEAD
// 	&& v->sprites[i].state != ECHASE && v->sprites[i].state != EATTACKR
// 	&& v->sprites[i].animoff >= v->img[v->sprites[i].img_i].width)
// 	v->sprites[i].animoff = 0;
//tmp->ms * v->game.frametime
enum	e_direction
{
	down,
	left_down,
	left,
	left_up,
	up,
	right_up,
	right,
	right_down
};

/// @brief Get direction from an angle, corresponding to a sprite index
/// @param angle Angle
/// @return Direction/ Sprite index
static int	get_direction(double angle)
{
	angle = ceil(angle);
	if (angle < -7 * M_PI / 8 || angle >= 7 * M_PI / 8)
		return (up);
	else if (angle < -5 * M_PI / 8)
		return (left_up);
	else if (angle < -3 * M_PI / 8)
		return (left);
	else if (angle < -M_PI / 8)
		return (left_down);
	else if (angle < M_PI / 8)
		return (down);
	else if (angle < 3 * M_PI / 8)
		return (right_down);
	else if (angle < 5 * M_PI / 8)
		return (right);
	else if (angle < 7 * M_PI / 8)
		return (right_up);
	else
		return (down);
}
// double (gtpvectorx) = 0.0;
// double (gtpvectory) = 0.0;
// double (gtpnorm) = 0.0;
// gtpnorm = sqrt((v->player.x - tmp->x) * (v->player.x - tmp->x)
// 		+ (v->player.y - tmp->y) * (v->player.y - tmp->y));
// gtpvectorx = (v->player.x - tmp->x);
// gtpvectory = (v->player.y - tmp->y);
// relative_angle = acos((gtpvectorx * tmp->vectorx + gtpvectory * tmp->vectory)
// / (tmp->norm * gtpnorm));
// printf("angle to player: %f, angle: %f, relative: %f, playerangle: %f\n",
	// tmp->angletoplay, tmp->angle, relative_angle, v->player.angle);

/// @brief Calculate the angle between two vectors
/// @param v Vars
/// @param tmp Actor pointer
void	calc_angle(t_vars *v, t_actor *tmp)
{
	double (relative_angle) = 0.0;
	tmp->angletoplay = atan2(v->player.y - tmp->y, v->player.x - tmp->x);
	relative_angle = tmp->angletoplay - tmp->angle;
	if (relative_angle > M_PI)
		relative_angle -= 2 * M_PI;
	if (relative_angle <= -M_PI)
		relative_angle += 2 * M_PI;
	tmp->animoffx = get_direction(relative_angle) * v->img[tmp->img_i].animx;
}
