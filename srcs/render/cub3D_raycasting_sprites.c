/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_raycasting_sprites.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 21:30:54 by pmagnero          #+#    #+#             */
/*   Updated: 2024/10/10 16:02:09 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/// @brief Set datas for sprites like distance from the player, sprite height...
/// @param v Vars
/// @param sp Sprite struct containing calcul datas
/// @param g The actual sprite to draw
// using 'transformY' instead of the real distance prevents fisheye 
void	transform_sprite(t_vars *v, t_sprite_data *sp, t_sprite g)
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
	sp->spriteheight = abs((int)(v->screen.gameh / sp->transformy)) / g.vdiv;
}

/// @brief Set dimensions of the sprite
/// @param v Vars
/// @param sp Sprite struct containing calcul datas 
/// @param g The actual sprite to draw
void	set_sprite_boundaries(t_vars *v, t_sprite_data *sp, t_sprite g)
{
	sp->drawstarty = -sp->spriteheight / 2
		+ v->screen.gameh / 2 + sp->vmovescreen;
	if (sp->drawstarty < 0)
		sp->drawstarty = 0;
	sp->drawendy = sp->spriteheight / 2 + v->screen.gameh / 2 + sp->vmovescreen;
	if (sp->drawendy >= v->screen.gameh)
		sp->drawendy = v->screen.gameh - 1;
	sp->spritewidth = abs((int)(v->screen.gameh / sp->transformy)) / g.udiv;
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
	while (++i < v->game.nb_sprites)
	{
		v->sprites[i].dist = pow((v->player.x - v->sprites[i].x), 2)
			+ pow((v->player.y - v->sprites[i].y), 2);
	}
	i = 0;
	while (true)
	{
		if (i < v->game.nb_sprites - 1)
		{
			if (v->sprites[i].dist < v->sprites[i + 1].dist)
				ft_swaps((sort = 1, &v->sprites[i]), &v->sprites[i + 1]);
			else
				sort++;
			if (sort == v->game.nb_sprites - 1)
				break ;
			i++;
		}
		else
		{
			i = 0;
			sort = 0;
		}
	}
}

/// @brief Add pixels of the sprite to the buffer
/// @param v Vars
/// @param sp Sprite struct containing calcul datas 
/// @param p The actual sprite to draw
void	draw_sprite(t_vars *v, t_sprite_data *sp, t_sprite *g, t_point p)
{
	int		tx;
	int		ty;

	p.x = sp->drawstartx - 1;
	hitguard(v, sp, g);
	guardattack(v, sp, g);
	while (++p.x < sp->drawendx)
	{
		tx = (int)(256 * (p.x - (sp->spritescreenx - sp->spritewidth / 2))
				* 64 / sp->spritewidth) / 256 + g->animoff;
		p.y = sp->drawstarty - 1;
		if (sp->transformy > 0 && p.x > 0 && p.x < v->screen.resw
			&& sp->transformy < v->ray.zbuffer[p.x])
		{
			while (++p.y < sp->drawendy)
			{
				p.z = (p.y - sp->vmovescreen) * 256 - v->screen.gameh * 128
					+ sp->spriteheight * 128;
				ty = ((p.z * v->tmp[0].height) / sp->spriteheight) / 256;
				p.z = (ty * v->tmp[0].len) + (tx * 4);
				add_pix(v, p, (t_point2){1, sp->transformy, FOGC, FOGL},
					(t_point){0});
			}
		}
	}
}

/// @brief Draw sprites
/// @param v Vars
void	draw_sprites(t_vars *v)
{
	int		i;

	i = -1;
	sort_sprites(v, -1, 0);
	while (++i < v->game.nb_sprites)
	{
		v->tmp[0] = v->img[v->sprites[i].img_i];
		transform_sprite(v, &v->sp, v->sprites[i]);
		set_sprite_boundaries(v, &v->sp, v->sprites[i]);
		draw_sprite(v, &v->sp, &v->sprites[i], (t_point){0});
	}
}
