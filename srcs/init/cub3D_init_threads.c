/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_init_threads.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:09:56 by pmagnero          #+#    #+#             */
/*   Updated: 2024/10/30 12:32:41 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	init_thread_data(t_vars *v, int i)
{
	if (pthread_mutex_init(&v->threads_data[i].data_mutex, NULL))
		exit((prterr(v, "Thread mutex init\n", 1, 1), 1));
	v->threads_data[i].thread_id = i;
	v->threads_data[i].pool = &v->pool;
	v->threads_data[i].v = v;
	v->threads_data[i].start = 0;
	v->threads_data[i].end = 0;
	v->threads_data[i].f = (t_floor){0};
	v->threads_data[i].job = 0;
	v->threads_data[i].tmp[0] = (t_imga){0};
	v->threads_data[i].tmp[1] = (t_imga){0};
}

void	init_thread_pool(t_vars *v, int i)
{
	if (!MANDATORY)
	{
		v->pool.thread_count = THREAD_COUNT;
		v->pool.threads = (pthread_t *)malloc(sizeof(pthread_t) * THREAD_COUNT);
		if (!v->pool.threads)
			exit((prterr(v, ERRMALL, 1, 1), 1));
		if (pthread_barrier_init(&v->pool.tbarrier, NULL, THREAD_COUNT)
			|| pthread_barrier_init(&v->pool.mbarrier, NULL, THREAD_COUNT + 1)
			|| pthread_mutex_init(&v->pool.job_mutex, NULL)
			|| pthread_cond_init(&v->pool.job_cond, NULL))
			exit((prterr(v, "Thread init failed\n", 1, 1), 1));
		v->pool.work_available = 0;
		v->pool.stop = 0;
		while (++i < THREAD_COUNT)
		{
			init_thread_data(v, i);
			if (pthread_create(&v->pool.threads[i], NULL, job,
					&v->threads_data[i]))
				exit((prterr(v, "Thread creation failed\n", 1, 1), 1));
		}
	}
}
