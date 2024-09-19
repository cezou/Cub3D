/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ids_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:22:16 by cviegas           #+#    #+#             */
/*   Updated: 2024/09/12 17:22:59 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

bool	is_everything_set(t_infos i)
{
	return (i.c && i.f && i.north.is_set && i.west.is_set && i.south.is_set
		&& i.east.is_set);
}

bool	is_texture(char *s)
{
	return (!cmp(s, "NO") || !cmp(s, "SO") || !cmp(s, "WE") || !cmp(s, "EA"));
}

bool	is_color(char *s)
{
	return (!cmp(s, "F") || !cmp(s, "C"));
}

size_t	nb_occur(const char *s, char c)
{
	size_t	i;
	size_t	o;

	if (!s)
		return (0);
	o = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			o++;
		i++;
	}
	return (o);
}
