/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_raycasting_sprites.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 21:30:54 by pmagnero          #+#    #+#             */
/*   Updated: 2024/09/22 22:04:09 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/// @brief Set datas for sprites like distance from the player, sprite height...
/// @param v Vars
/// @param sp Sprite struct containing calcul datas
/// @param g The actual sprite to draw
// using 'transformY' instead of the real distance prevents fisheye 
void	transform_sprite(t_vars *v, t_sprite *sp, t_guard g)
{
	double		invdet;
	double		spritex;
	double		spritey;
	double		transformx;

	spritex = g.x - v->player.x;
	spritey = g.y - v->player.y;
	invdet = 1.0 / (v->player.plane_x * v->player.dir_y
			- v->player.plane_y * v->player.dir_x);
	transformx = invdet * (v->player.dir_y * spritex
			- v->player.dir_x * spritey);
	sp->transformy = invdet * (v->player.plane_x * spritey
			- v->player.plane_y * spritex);
	sp->spritescreenx = (int)((v->screen.resw / 2)
			* (1 + transformx / sp->transformy));
	sp->vmovescreen = (int)(g.vmove / sp->transformy)
		+ v->ray.pitch + v->player.z / sp->transformy;
	sp->spriteheight = abs((int)(v->screen.resh / sp->transformy)) / g.vdiv;
}

/// @brief Set dimensions of the sprite
/// @param v Vars
/// @param sp Sprite struct containing calcul datas 
/// @param g The actual sprite to draw
void	set_sprite_boundaries(t_vars *v, t_sprite *sp, t_guard g)
{
	sp->drawstarty = -sp->spriteheight / 2
		+ v->screen.resh / 2 + sp->vmovescreen;
	if (sp->drawstarty < 0)
		sp->drawstarty = 0;
	sp->drawendy = sp->spriteheight / 2 + v->screen.resh / 2 + sp->vmovescreen;
	if (sp->drawendy >= v->screen.resh)
		sp->drawendy = v->screen.resh - 1;
	sp->spritewidth = abs((int)(v->screen.resh / sp->transformy)) / g.udiv;
	sp->drawstartx = -sp->spritewidth / 2 + sp->spritescreenx;
	if (sp->drawstartx < 0)
		sp->drawstartx = 0;
	sp->drawendx = sp->spritewidth / 2 + sp->spritescreenx;
	if (sp->drawendx >= v->screen.resw)
		sp->drawendx = v->screen.resw - 1;
}

/// @brief Sort sprites from far to close
/// @param v Vars
/// @param i Increment variable =-1
/// @param sort Integer used to sort =0
void	sort_sprites(t_vars *v, int i, int sort)
{
	while (++i < v->game.nb_guard)
	{
		v->guard[i].dist = pow((v->player.x - v->guard[i].x), 2)
			+ pow((v->player.y - v->guard[i].y), 2);
	}
	i = 0;
	while (true)
	{
		if (i < v->game.nb_guard - 1 && v->guard[i].dist < v->guard[i + 1].dist)
		{
			ft_swaps(&v->guard[i], &v->guard[i + 1]);
			sort++;
			i++;
			continue ;
		}
		if (sort)
		{
			i = 0;
			sort = 0;
			continue ;
		}
		break ;
	}
}

/// @brief Add pixels of the sprite to the buffer
/// @param v Vars
/// @param sp Sprite struct containing calcul datas 
/// @param p The actual sprite to draw
void	draw_sprite(t_vars *v, t_sprite *sp, t_point p, t_guard g)
{
	int	tx;
	int	ty;

	p.x = sp->drawstartx - 1;
	while (++p.x < sp->drawendx)
	{
		tx = (int)(256 * (p.x - (sp->spritescreenx - sp->spritewidth / 2))
				* 64 / sp->spritewidth) / 256 + g.animoff;
		p.y = sp->drawstarty - 1;
		if (sp->transformy > 0 && p.x > 0 && p.x < v->screen.resw
			&& sp->transformy < v->ray.zbuffer[p.x])
		{
			while (++p.y < sp->drawendy)
			{
				p.z = (p.y - sp->vmovescreen) * 256 - v->screen.resh * 128
					+ sp->spriteheight * 128;
				ty = ((p.z * v->img[g.img_i].height) / sp->spriteheight) / 256;
				p.z = (ty * v->img[g.img_i].len) + (tx * 4);
				add_pix_to_buffer(v, v->img[g.img_i], p,
					(t_point2){1, sp->transformy, FOG_COLOR, FOG_LEVEL});
			}
		}
	}
}

/// @brief Draw sprites
/// @param v Vars
void	draw_sprites(t_vars *v)
{
	int	i;

	i = -1;
	while (++i < v->game.nb_guard)
	{
		sort_sprites(v, -1, 0);
		transform_sprite(v, &v->sprite, v->guard[i]);
		set_sprite_boundaries(v, &v->sprite, v->guard[i]);
		draw_sprite(v, &v->sprite, (t_point){0, 0, 0, 0}, v->guard[i]);
	}
}
