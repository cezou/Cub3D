/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:37:59 by pmagnero          #+#    #+#             */
/*   Updated: 2024/04/05 23:35:47 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/// @brief Stop and clear thread pool
/// @param v Vars
void	stop_threads_pool(t_vars *v)
{
	int	i;

	i = -1;
	v->exit = 1;
	ft_printf(1, "Broadcast stop\n");
	pthread_mutex_lock(&v->pool.job_mutex);
	v->pool.stop = 1;
	pthread_cond_broadcast(&v->pool.job_cond);
	pthread_mutex_unlock(&v->pool.job_mutex);
	pthread_barrier_wait(&v->pool.mbarrier);
	ft_printf(1, "Thread pool stopping...\n");
	while (++i < THREAD_COUNT)
		pthread_join(v->pool.threads[i], NULL);
	ft_printf(1, "Thread pool stopped !\n");
	ft_printf(1, "Thread pool clearing...\n");
	free(v->pool.threads);
	pthread_barrier_destroy(&v->pool.tbarrier);
	pthread_barrier_destroy(&v->pool.mbarrier);
	pthread_mutex_destroy(&v->pool.job_mutex);
	i = -1;
	while (++i < THREAD_COUNT)
		pthread_mutex_destroy(&v->threads_data[i].data_mutex);
	pthread_cond_destroy(&v->pool.job_cond);
	ft_printf(1, "Thread pool cleared !\n");
}
	// pthread_cancel(v->pool.threads[i]);
	// pthread_mutex_lock(&v->pool.job_mutex);
	// v->exit = 1;
	// v->pool.stop = 1;
	// pthread_mutex_unlock(&v->pool.job_mutex);
	// pthread_mutex_lock(&v->pool.job_mutex);
	// pthread_cond_broadcast(&v->pool.job_cond);
	// pthread_mutex_unlock(&v->pool.job_mutex);
	// pthread_barrier_wait(&v->pool.mbarrier);
	// while (++i < THREAD_COUNT)
	// 	pthread_join(v->pool.threads[i], NULL);
