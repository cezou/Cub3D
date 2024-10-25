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

	if (len(s) < len(ext) + 1)
		return (1);
	i = len(s) - 1;
	e = len(s) - 1;
	while (e >= 0)
	{
		if (s[i] != ext[e])
			return (0);
		e--;
		i--;
	}
	return (1);
}
