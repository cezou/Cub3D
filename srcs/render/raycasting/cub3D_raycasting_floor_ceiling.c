/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_raycasting_floor_ceiling.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:38:17 by pmagnero          #+#    #+#             */
/*   Updated: 2024/10/20 20:04:08 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3D.h"

/*HORIZONTAL METHOD*/

/// @brief Init datas for the floor and ceiling calculations
/// @param v Vars
/// @param f Floor structure
/// @param y Y coordinate
static void	init_data_floor(t_vars *v, t_floor *f, int y)
{
	int		d;
	double	posz;

	f->dir_x = v->player.dir_x - v->player.plane_x;
	f->dir_y = v->player.dir_y - v->player.plane_y;
	f->dir_x1 = v->player.dir_x + v->player.plane_x;
	f->dir_y1 = v->player.dir_y + v->player.plane_y;
	f->isfloor = y > v->screen.gameh / 2 + v->ray.pitch;
	d = v->screen.gameh / 2 - y + v->ray.pitch;
	posz = 0.5 * v->screen.gameh - v->player.z;
	if (f->isfloor)
	{
		d = y - v->screen.gameh / 2 - v->ray.pitch;
		posz = 0.5 * v->screen.gameh + v->player.z;
	}
	f->rowdist = posz / d;
	f->fstepx = f->rowdist * (f->dir_x1 - f->dir_x) / v->screen.resw;
	f->fstepy = f->rowdist * (f->dir_y1 - f->dir_y) / v->screen.resw;
	f->fx = v->player.x + f->rowdist * f->dir_x;
	f->fy = v->player.y + f->rowdist * f->dir_y;
}

// color = v->tex[4][64 * ty + tx];

void	add_pix_threaded(t_vars *v, t_point p, t_point3 fog, t_point opt, t_imga *tmp)
{
	if (!opt.y && p.z > -1 && tmp[0].addr[p.z + 3] == 0)
	{
		p.color = getcolorpix(v, tmp[0].addr, p.z);
		if (opt.x)
			p.color = (p.color >> 1) & 8355711;
		if (fog.x)
			p.color = color_lerp(p.color, fog.z, fog.y / 29 * fog.uv);
		img_pix_put(&tmp[1], p, v);
	}
	else if (opt.y)
	{
		if (fog.x)
			p.color = color_lerp(p.color, fog.z, fog.y / 29 * fog.uv);
		img_pix_put(&tmp[1], p, v);
	}
}

/// @brief Add the pixel from the texture to the buffer
/// @param v Vars
/// @param f Floor structure
/// @param p Pixel coordinate to add to the buffer
/// @param img Texture to use
static void	update_floor_ceil_texture_pixels(t_vars *v, t_floor *f, t_point p,
	t_imga *tmp)
{
	while (p.x < v->screen.resw)
	{
		f->cx = (int)(f->fx);
		f->cy = (int)(f->fy);
		f->tx = (int)(tmp[0].width * (f->fx - f->cx)) & (tmp[0].width - 1);
		f->ty = (int)(tmp[0].width * (f->fy - f->cy)) & (tmp[0].width - 1);
		f->fx += f->fstepx;
		f->fy += f->fstepy;
		p.z = (f->ty * tmp[0].len) + (f->tx * 4);
		if (MANDATORY)
			p.color = v->infos.floor;
		if (f->isfloor)
			add_pix_threaded(v, p, (t_point3){1.0, f->rowdist, FOGC, FOGL, 0},
				(t_point){0, p.color, 0, 0}, tmp);
		else if (f->cx < 10 || f->cx > 16)
		{
			if (MANDATORY)
				p.color = v->infos.ceil;
			add_pix_threaded(v, p, (t_point3){1.0, f->rowdist, FOGC, FOGL, 0},
				(t_point){0, p.color, 0, 0}, tmp);
		}
		p.x++;
	}
}

/// @brief Draw the floor and ceiling
/// @param v Vars
void	draw_floor_ceiling(t_vars *v)
{
	int	y;

	y = 0;
	v->tmp[0] = v->img[ESPACE];
	while (y < v->screen.gameh)
	{
		init_data_floor(v, &v->floor, y);
		update_floor_ceil_texture_pixels(v, &v->floor, (t_point){0, y, 0, 0},
			v->tmp);
		y++;
	}
}


void	*job(void *arg)
{
	t_thread_data	*d;
	int				id;
	t_thread_pool	*pool;
	t_vars			*v;

	d = (t_thread_data *)arg;
	id = d->thread_id;
	pool = d->pool;
	v = d->v;
	while (!pool->stop)
	{
		if (pool->stop)
		{
			printf("Thread %d stopping...\n", id);
			break ;
		}
		printf("id: %d, stop: %lld\n", id, pool->job_cond.__align);
		pthread_mutex_lock(&pool->job_mutex);
		while (!pool->work_available && !pool->stop)
			pthread_cond_wait(&pool->job_cond, &pool->job_mutex);
		if (pool->stop)
		{
			pthread_mutex_unlock(&pool->job_mutex);
			printf("Thread %d stopping...\n", id);
			break ;
		}
		pthread_mutex_unlock(&pool->job_mutex);
		if (pool->stop)
		{
			printf("Thread %d stopping...\n", id);
			break ;
		}
		pthread_mutex_lock(&d->data_mutex);
		if (d->job)
		{
			while (d->y_start < d->y_end)
			{
				init_data_floor(v, &d->f, d->y_start);
				update_floor_ceil_texture_pixels(v, &d->f,
					(t_point){0, d->y_start, 0, 0}, d->tmp);
				d->y_start++;
			}
		}
		d->job = 0;
		pthread_mutex_unlock(&d->data_mutex);
		if (pool->stop)
		{
			printf("Thread %d stopping...\n", id);
			break ;
		}
		pthread_barrier_wait(&pool->tbarrier);
		if (pool->stop)
		{
			printf("Thread %d stopping...\n", id);
			break ;
		}
		pthread_barrier_wait(&pool->mbarrier);
		if (pool->stop)
		{
			printf("Thread %d stopping...\n", id);
			break ;
		}
	}
	return (NULL);
}

void	update(t_vars *v, t_imga dest)
{
	int	i;
	int	len;

	len = v->screen.gameh / v->pool.thread_count;
	i = -1;
	while (++i < v->pool.thread_count)
	{
		pthread_mutex_lock(&v->threads_data[i].data_mutex);
		v->threads_data[i].job = 1;
		if (v->game.pause)
			v->threads_data[i].job = 0;
		// if (v->exit)
		// 	v->threads_data[i].stop = 1;
		v->threads_data[i].tmp[0] = v->img[ESPACE];
		v->threads_data[i].tmp[1] = dest;
		v->threads_data[i].y_start = i * (len);
		v->threads_data[i].y_end = (i + 1) * (len);
		if (i == v->pool.thread_count - 1)
			v->threads_data[i].y_end = v->screen.gameh;
		pthread_mutex_unlock(&v->threads_data[i].data_mutex);
	}
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
		v->threads_data[i].y_start = 0;
		v->threads_data[i].y_end = 0;
		v->threads_data[i].job = 0;
		pthread_mutex_unlock(&v->threads_data[i].data_mutex);
	}
}

/*VERTICAL METHOD*/

// void	set_wall_dir(t_vars *v)
// {
// 	if (v->ray.side == 0 && v->ray.dir_x > 0)
// 	{
// 		v->ray.dir_x1 = v->ray.map_x;
// 		v->ray.dir_y1 = v->ray.map_y + v->ray.wall_x;
// 	}
// 	else if (v->ray.side == 0 && v->ray.dir_x < 0)
// 	{
// 		v->ray.dir_x1 = v->ray.map_x + 1.0;
// 		v->ray.dir_y1 = v->ray.map_y + v->ray.wall_x;
// 	}
// 	else if (v->ray.side == 1 && v->ray.dir_y > 0)
// 	{
// 		v->ray.dir_x1 = v->ray.map_x + v->ray.wall_x;
// 		v->ray.dir_y1 = v->ray.map_y;
// 	}
// 	else
// 	{
// 		v->ray.dir_x1 = v->ray.map_x + v->ray.wall_x;
// 		v->ray.dir_y1 = v->ray.map_y + 1.0;
// 	}
// }

// // p.color = v->tex[5][64 * ty + tx];
// void	draw_ceiling(t_vars *v, t_point p, int tx, int ty)
// {
// 	double		currfx;
// 	double		currfy;
// 	double		weight;
// 	double		currdist;
// 	double		distplay;

// 	distplay = 0.0;
// 	while (p.y < v->ray.draw_start)
// 	{
// 		currdist = (v->screen.resh - (2.0 * v->player.z))
// 			/ (v->screen.resh - 2.0 * (p.y - v->ray.pitch));
// 		weight = (currdist - distplay) / (v->ray.wall_dist - distplay);
// 		currfx = weight * v->ray.dir_x1 + (1.0 - weight) * v->player.x;
// 		currfy = weight * v->ray.dir_y1 + (1.0 - weight) * v->player.y;
// 		// if ((int)currfx > 10 && (int)currfx < 16)
// 		// {
// 		// 	p.y++;
// 		// 	continue ;
// 		// }
// 		tx = (int)(currfx * v->img[ESPACE].width) & (v->img[ESPACE].width - 1);
// 	ty = (int)(currfy * v->img[ESPACE].height) & (v->img[ESPACE].height - 1);
// 		p.color = getcolorpix(v, v->img[ESPACE].addr,
// 				(ty * v->img[ESPACE].len) + (tx * 4));
// 		p.color = (p.color >> 1) & 8355711;
// 		img_pix_put(&v->img[EMAP], p, v);
// 		p.y++;
// 	}
// }

// void	draw_floor(t_vars *v, t_point p, int tx, int ty)
// {
// 	double		currfx;
// 	double		currfy;
// 	double		weight;
// 	double		currdist;
// 	double		distplay;

// 	distplay = 0.0;
// 	if (v->ray.img.id == EDOOR && v->ray.side == 1)
// 		v->ray.wall_dist = v->ray.sidedist_y - v->ray.deltadist_y;
// 	else if (v->ray.img.id == EDOOR && v->ray.side == 0)
// 		v->ray.wall_dist = v->ray.sidedist_x - v->ray.deltadist_x;
// 	// if (v->ray.img.id == EDOOR)
// 	// {
// 	// 	perform_dda(v, 1);
// 	// 	calculate_line_height(v);
// 	// }
// 	while (p.y < v->screen.resh)
// 	{
// 		currdist = (v->screen.resh + (2.0 * v->player.z))
// 			/ (2.0 * (p.y - v->ray.pitch) - v->screen.resh);
// 		weight = (currdist - distplay) / (v->ray.wall_dist - distplay);
// 		// if (v->ray.img.id == EDOOR)
// 		// {
// 		// 	weight = (currdist - distplay) /
// (v->ray.wall_dist + v->ray.deltadist_y * 0.5 - distplay);
// 		// }
// 		currfx = weight * v->ray.dir_x1 + (1.0 - weight) * v->player.x;
// 		currfy = weight * v->ray.dir_y1 + (1.0 - weight) * v->player.y;
// 		tx = (int)(currfx * v->img[ESPACE].width) & (v->img[ESPACE].width - 1);
// 	ty = (int)(currfy * v->img[ESPACE].height) & (v->img[ESPACE].height - 1);
// 		p.color = getcolorpix(v, v->img[ESPACE].addr,
// 				(ty * v->img[ESPACE].len) + (tx * 4));
// 		p.color = (p.color >> 1) & 8355711;
// 		img_pix_put(&v->img[EMAP], p, v);
// 		p.y++;
// 	}
// }

// void	set_floor_ceiling_vert(t_vars *v, t_point p)
// {
// 	set_wall_dir(v);
// 	if (v->ray.draw_end < 0)
// 		v->ray.draw_end = v->screen.resh;
// 	draw_ceiling(v, p, 0, 0);
// 	p.color = 0;
// 	p.z = 0;
// 	p.y = v->ray.draw_end;
// 	draw_floor(v, p, 0, 0);
// }
