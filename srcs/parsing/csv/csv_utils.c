/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csv_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 08:17:47 by cviegas           #+#    #+#             */
/*   Updated: 2024/10/25 08:20:20 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3D.h"

void	eerr(const char *s, int i)
{
	ft_printf(STDERR, "%sError\nExtension: %s%sLine %d, %s%s\n", RED, RCOLOR,
		LIL_RED, i, s, RCOLOR);
}

bool	isnt_ended_by(const char *s, const char *ext)
{
	int	i;
	int	e;

	if (len(s) < len(ext))
		return (1);
	i = len(s) - 1;
	e = len(ext) - 1;
	while (e >= 0)
	{
		if (s[i] != ext[e])
			return (1);
		e--;
		i--;
	}
	return (0);
}

bool	is_valid(double d)
{
	return (d >= 0 && d <= 128);
}

bool	is_bool(double d)
{
	return (d == 0 || d == 1);
}

bool	there_is_unvalid_values(t_obj obj)
{
	return (!((obj.x && obj.y && obj.animx && is_valid(obj.uv)
				&& is_valid(obj.v)) && is_bool(obj.h)
			&& is_bool(obj.pickable)));
}
