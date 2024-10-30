/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_raycasting_floor_ceiling_threaded.c          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:38:17 by pmagnero          #+#    #+#             */
/*   Updated: 2024/10/30 14:03:45 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3D.h"

void	process_data_floor(t_thread_data *d)
{
	while (d->start < d->end)
	{
		init_data_floor(d->v, &d->f, d->start);
		update_floor_ceil_texture_pixels(d->v, &d->f,
			(t_point){0, d->start, 0, 0}, d->tmp);
		d->start++;
	}
}

void	process_data_sky(t_thread_data *d)
{
	t_point	p;

	p = (t_point){-1, -1, 0, 0};
	d->f.lim = ((d->v->game.skybox.height - 1) * d->v->game.skybox.len)
		+ ((d->v->game.skybox.width - 1) * 4);
	set_skybox(d->v, &d->f, d->v->game.skybox.width, d->start);
	p.x = d->start - 1;
	while (++p.x < d->end)
	{
		d->f.t[0] = d->f.tx;
		if (d->f.tx >= d->v->game.skybox.width)
			d->f.t[0] = d->f.tx - d->v->game.skybox.width;
		p.y = -1;
		d->f.t[1] = d->f.ty;
		surf_rows(d->v, p, &d->f, d->tmp);
		p.z += d->f.cx;
		while (p.z > d->end)
		{
			d->f.tx += 1;
			p.z -= d->end;
		}
	}
}

// printf("id: %d, second barrier: %d\n", id, pool->stop);
void	*job(void *arg)
{
	t_thread_data	*d;

	d = (t_thread_data *)arg;
	while (1)
	{
		usleep(2000);
		pthread_mutex_lock(&d->pool->job_mutex);
		while (!d->pool->work_available && !d->pool->stop)
			pthread_cond_wait(&d->pool->job_cond, &d->pool->job_mutex);
		pthread_mutex_unlock(&d->pool->job_mutex);
		pthread_mutex_lock(&d->data_mutex);
		if (d->job == 1)
			process_data_floor(d);
		else if (d->job == 2)
			process_data_sky(d);
		d->job = 0;
		pthread_mutex_unlock(&d->data_mutex);
		pthread_barrier_wait(&d->pool->tbarrier);
		pthread_barrier_wait(&d->pool->mbarrier);
		if (d->pool->stop)
			break ;
	}
	return (NULL);
}

static void	init_job_datas(t_vars *v, t_imga dest)
{
	int	i;
	int	len;

	len = v->screen.gameh / v->pool.thread_count;
	i = -1;
	while (++i < v->pool.thread_count)
	{
		pthread_mutex_lock(&v->threads_data[i].data_mutex);
		v->threads_data[i].job = 1;
		v->threads_data[i].tmp[0] = v->img[ESPACE];
		v->threads_data[i].tmp[1] = dest;
		v->threads_data[i].start = i * (len);
		v->threads_data[i].end = (i + 1) * (len);
		if (i == v->pool.thread_count - 1)
			v->threads_data[i].end = v->screen.gameh;
		pthread_mutex_unlock(&v->threads_data[i].data_mutex);
	}
}

void	draw_floor_ceiling_threaded(t_vars *v, t_imga dest)
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
