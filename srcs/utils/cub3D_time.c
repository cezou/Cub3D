/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_time.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 21:59:52 by pmagnero          #+#    #+#             */
/*   Updated: 2024/04/05 17:54:35 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static uint64_t	gettimeofday_ms(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

uint64_t	timestamp_in_ms(t_vars *v)
{
	// static int	frames = -1;

	// if (MANDATORY)
	// 	return (++frames);
	if (v->game.created_at == 0)
		v->game.created_at = gettimeofday_ms();
	return (gettimeofday_ms() - v->game.created_at);
}

void	scrolling(t_vars *v, float *h, char *str, t_point2 p)
{
	if (*h >= 2000)
	{
		mlx_set_font(v->mlx, v->screen.win, v->img->fontname2);
		mlx_string_put(v->mlx, v->screen.win, v->screen.resw * 0.35,
			v->screen.resh * 0.45,
			G_P, "THANKS TO 42 AND EVERY ONE WHO TESTED IT");
		mlx_set_font(v->mlx, v->screen.win, v->img->fontname);
		return ;
	}
	if (p.z)
		mlx_set_font(v->mlx, v->screen.win, v->img->fontname2);
	mlx_string_put(v->mlx, v->screen.win,
		v->screen.resw * p.x, p.y - (*h), p.color, str);
	*h += 0.05f;
	mlx_set_font(v->mlx, v->screen.win, v->img->fontname);
}

// int	timer(int delay)
// {
// 	time_t	start_time;
// 	time_t	current_time;
// 	double	diff;

// 	diff = 0;
// 	time(&start_time);
// 	time(&current_time);
// 	while (diff < delay)
// 	{
// 		diff = difftime(current_time, start_time);
// 		time(&current_time);
// 	}
// 	return (1);
// }