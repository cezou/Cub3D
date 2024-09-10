/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_set_font.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 13:30:47 by amalliar          #+#    #+#             */
/*   Updated: 2024/03/13 19:44:30 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_int.h"

/*
** Allows to specify the font that will be used by mlx_string_put.
**
** Note: only fixed-width bitmap fonts are supported by Xlib, refer to xfontsel
** utility to get valid font names for this function.
*/

// void	mlx_set_font(t_xvar *xvar, t_win_list *win, char *name)
// {
// 	// XFontStruct	*font;
// 	// XCharStruct	overall;
//   	// int			dir;
// 	// int			asc;
// 	// int			desc;
// 	static Font		font = 0;

// 	if (font)
// 		XUnloadFont(xvar->display, font);
// 	font = XLoadFont(xvar->display, name);
// 	// name = "-sony-*-medium-*-*-*-24-*-*-*-*-*-*-*";
// 	// printf("KAK%s\n", name);
// 	// font = XLoadQueryFont(xvar->display, name);
// 	// if (!font)
// 	// {
// 	// 	fprintf (stderr, "unable to load font %s: using fixed\n", name);
// 	// 	font = XLoadQueryFont (xvar->display, "fixed");
// 	// }
// 	// XSetFont(xvar->display, win->gc, font->fid);
// 	// XTextExtents(font->, "KEEEEK", 6, &dir, &asc, &desc, &overall);
// 	// XDrawString(xvar->display,win->window,win->gc, 500, 500, "KEEEEK", strlen("KEEEEK"));
// 	// printf("PKEK%d\n", font->fid);
// 	XSetFont(xvar->display, win->gc, font);
// }
void	mlx_set_font(t_xvar *xvar, t_win_list *win, char *name)
{
	static Font		font = 0;

	if (font)
		XUnloadFont(xvar->display, font);
	font = XLoadFont(xvar->display, name);
	XSetFont(xvar->display, win->gc, font);
}
