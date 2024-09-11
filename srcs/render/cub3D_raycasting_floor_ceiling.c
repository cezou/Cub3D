/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_raycasting_floor_ceiling.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:38:17 by pmagnero          #+#    #+#             */
/*   Updated: 2024/09/11 17:35:35 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void	init_ray_floor(t_ray *ray, t_vars *v)
{
	ray->dir_x = v->player.dir_x - v->player.plane_x;
	ray->dir_y = v->player.dir_y - v->player.plane_y;
	ray->dir_x1 = v->player.dir_x + v->player.plane_x;
	ray->dir_y1 = v->player.dir_y + v->player.plane_y;
}

static void	update_texture_pixels(t_vars *v, t_ray *ray, int y)
{
	int			p;
	double		posz;
	double		rowdist;
	double		fstepx;
	double		fstepy;
	double		fx;
	double		fy;
	int			x;
	int			tx;
	int			ty;
	uint32_t	color;

	x = 0;
	p = y - v->screen.resh / 2;
	posz = 0.5 * v->screen.resh;
	rowdist = posz / p;
	fstepx = rowdist * (ray->dir_x1 - ray->dir_x) / v->screen.resw;
	fstepy = rowdist * (ray->dir_y1 - ray->dir_y) / v->screen.resw;
	fx = v->player.x + rowdist * ray->dir_x;
	fy = v->player.y + rowdist * ray->dir_y;
	while (x < v->screen.resw)
	{
		tx = (int)(64 * (fx - (int)(fx))) & (64 - 1);
		ty = (int)(64 * (fy - (int)(fy))) & (64 - 1);
		fx += fstepx;
		fy += fstepy;
		// color = getcolorpix(v->img[1].addr, (texy * v->img[1].len) + (texx * 4), 0);
		color = v->tex[5][64 * ty + tx];
		color = (color >> 1) & 8355711;
		img_pix_put(&v->img[COMP_N], (t_point){x, v->screen.resh - y - 1, 0, color},//  + v->mouse.yoff
			v->screen.resw, v->screen.resh);
		x++;
	}
}

void	set_floor_ceiling(t_vars *v, t_ray *ray)
{
	int		y;

	y = 0;
	while (y < v->img[EMAP].height)
	{
		// if (x >= v->img[EMAP].width)
		// 	return (0);
		init_ray_floor(ray, v);
		update_texture_pixels(v, ray, y);
		// set_dda(&ray, v);
		// perform_dda(v, &ray);
		// calculate_line_height(&ray, v);
		// update_texture_pixels(v, &ray, x);
		y++;
	}
}

    // //FLOOR CASTING
    // for(int y = 0; y < h; y++)
    // {
    //   // rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
    //   float rayDirX0 = dirX - planeX;
    //   float rayDirY0 = dirY - planeY;
    //   float rayDirX1 = dirX + planeX;
    //   float rayDirY1 = dirY + planeY;

    //   // Current y position compared to the center of the screen (the horizon)
    //   int p = y - screenHeight / 2;

    //   // Vertical position of the camera.
    //   float posZ = 0.5 * screenHeight;

    //   // Horizontal distance from the camera to the floor for the current row.
    //   // 0.5 is the z position exactly in the middle between floor and ceiling.
    //   float rowDistance = posZ / p;

    //   // calculate the real world step vector we have to add for each x (parallel to camera plane)
    //   // adding step by step avoids multiplications with a weight in the inner loop
    //   float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / screenWidth;
    //   float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / screenWidth;

    //   // real world coordinates of the leftmost column. This will be updated as we step to the right.
    //   float floorX = posX + rowDistance * rayDirX0;
    //   float floorY = posY + rowDistance * rayDirY0;

    //   for(int x = 0; x < screenWidth; ++x)
    //   {
    //     // the cell coord is simply got from the integer parts of floorX and floorY
    //     int cellX = (int)(floorX);
    //     int cellY = (int)(floorY);

    //     // get the texture coordinate from the fractional part
    //     int tx = (int)(texWidth * (floorX - cellX)) & (texWidth - 1);
    //     int ty = (int)(texHeight * (floorY - cellY)) & (texHeight - 1);

    //     floorX += floorStepX;
    //     floorY += floorStepY;

    //     // choose texture and draw the pixel
    //     int floorTexture = 3;
    //     int ceilingTexture = 6;
    //     Uint32 color;

    //     // floor
    //     color = texture[floorTexture][texWidth * ty + tx];
    //     color = (color >> 1) & 8355711; // make a bit darker
    //     buffer[y][x] = color;

    //     //ceiling (symmetrical, at screenHeight - y - 1 instead of y)
    //     color = texture[ceilingTexture][texWidth * ty + tx];
    //     color = (color >> 1) & 8355711; // make a bit darker
    //     buffer[screenHeight - y - 1][x] = color;
    //   }
    // }
