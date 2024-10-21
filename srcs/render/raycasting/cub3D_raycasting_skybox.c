/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_raycasting_skybox.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 21:30:54 by pmagnero          #+#    #+#             */
/*   Updated: 2024/10/21 18:40:40 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3D.h"

/// @brief Set skybox datas
/// @param v Vars
void	set_skybox(t_vars *v, t_floor *f, int w, int xs)
{
	f->dir_x = v->player.dir_x - v->player.plane_x;
	f->dir_y = v->player.dir_y - v->player.plane_y;
	f->dir_x1 = v->player.dir_x + v->player.plane_x;
	f->dir_y1 = v->player.dir_y + v->player.plane_y;
	f->tx = (int)(-atan2(f->dir_x, f->dir_y)
			* (double)w / (2 * M_PI) * SKYBOX_REPEATS) + xs;
	f->tx1 = (int)(-atan2(f->dir_x1, f->dir_y1)
			* (double)w / (2 * M_PI) * SKYBOX_REPEATS);
	while (f->tx1 < f->tx)
		f->tx1 += w;
	while (f->tx < 0)
	{
		f->tx += w;
		f->tx1 += w;
	}
	f->cx = f->tx1 - f->tx;
	f->cy = v->screen.gameh / 2 + v->ray.pitch;
	f->dcy = v->game.skybox.height * (v->screen.gameh / 2 + v->ray.pitch)
		/ (v->screen.gameh / 2 + v->screen.gameh / 2) - 1;
	f->ty = v->game.skybox.height - 1 - f->dcy;
}

/// @brief Go through the rows of the screen and add pixels to the buffer
/// @param v Vars
/// @param p Pixel to add to the buffer
/// @param tx Texture x coordinate
/// @param ty Texture y coordinate
void	surf_rows(t_vars *v, t_point p, t_floor *f, t_imga *tmp)
{
	int	cy;

	cy = 0;
	while (++p.y < f->cy)
	{
		p.z = (f->t[1] * v->game.skybox.len) + (f->t[0] * 4);
		if (p.z < f->lim && p.z >= 0 && p.x >= 0 && p.x < v->screen.gamew
			&& p.y >= 0)
			add_pix_custom(v, p, (t_point3){0}, tmp);
		cy += f->dcy;
		while (cy > f->cy)
		{
			f->t[1] += 1;
			cy -= f->cy;
		}
	}
}

/// @brief Draw the skybox on the screen
/// @param v Vars
/// @param p Pixel to add to the buffer
/// @param tx Texture x coordinate
/// @param ty Texture y coordinate
///	@note 
void	draw_skybox(t_vars *v, t_point p, t_floor *f)
{
	f->lim = ((v->game.skybox.height - 1) * v->game.skybox.len)
		+ ((v->game.skybox.width - 1) * 4);
	set_skybox(v, f, v->game.skybox.width, 0);
	while (++p.x < v->screen.resw)
	{
		f->t[0] = f->tx;
		if (f->tx >= v->game.skybox.width)
			f->t[0] = f->tx - v->game.skybox.width;
		p.y = -1;
		f->t[1] = f->ty;
		surf_rows(v, p, f, v->tmp);
		p.z += f->cx;
		while (p.z > v->screen.resw)
		{
			f->tx += 1;
			p.z -= v->screen.resw;
		}
	}
}

static void	init_job_datas(t_vars *v, t_imga dest)
{
	int	i;
	int	len;

	len = v->screen.gamew / v->pool.thread_count;
	i = -1;
	while (++i < v->pool.thread_count)
	{
		pthread_mutex_lock(&v->threads_data[i].data_mutex);
		v->threads_data[i].job = 2;
		if (v->game.pause)
			v->threads_data[i].job = 0;
		v->threads_data[i].tmp[0] = v->img[ESKYBOX];
		v->threads_data[i].tmp[1] = dest;
		v->threads_data[i].start = i * (len);
		v->threads_data[i].end = (i + 1) * (len);
		if (i == v->pool.thread_count - 1)
			v->threads_data[i].end = v->screen.gamew;
		pthread_mutex_unlock(&v->threads_data[i].data_mutex);
	}
}

/// @brief Draw the skybox on the screen
/// @param v Vars
/// @param p Pixel to add to the buffer
/// @param tx Texture x coordinate
/// @param ty Texture y coordinate
///	@note 
void	draw_skybox_threaded(t_vars *v, t_imga dest)
{
	int	i;

	i = -1;
	init_job_datas(v, dest);
	pthread_mutex_lock(&v->pool.job_mutex);
	v->pool.work_available = 1;
	pthread_cond_broadcast(&v->pool.job_cond);
	pthread_mutex_unlock(&v->pool.job_mutex);
	pthread_barrier_wait(&v->pool.mbarrier);
	pthread_mutex_lock(&v->pool.job_mutex);
	v->pool.work_available = 0;
	pthread_mutex_unlock(&v->pool.job_mutex);
	i = -1;
	while (++i < v->pool.thread_count)
	{
		pthread_mutex_lock(&v->threads_data[i].data_mutex);
		v->threads_data[i].start = 0;
		v->threads_data[i].end = 0;
		v->threads_data[i].job = 0;
		pthread_mutex_unlock(&v->threads_data[i].data_mutex);
	}
}
