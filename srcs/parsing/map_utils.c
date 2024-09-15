/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:22:11 by cviegas           #+#    #+#             */
/*   Updated: 2024/09/15 18:18:42 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

bool	isnt_cub_ended(const char *s)
{
	int	i;

	if (ft_strlen(s) < 4)
		return (1);
	i = ft_strlen(s) - 1;
	if (s[i] == 'b' && s[i - 1] == 'u' && s[i - 2] == 'c' && s[i - 3] == '.')
		return (0);
	return (1);
}

bool	there_is_only_whitespaces(const char *s)
{
	int		i;
	int		j;
	bool	its_a_whitespace;

	i = -1;
	while (s[++i])
	{
		its_a_whitespace = 0;
		j = -1;
		while (WHITESPACES[++j])
		{
			if (s[i] == WHITESPACES[j])
			{
				its_a_whitespace = 1;
				break ;
			}
		}
		if (!its_a_whitespace)
			return (0);
	}
	return (1);
}

bool	is_char_valid(char c)
{
	int	i;

	i = -1;
	while (VALID[++i])
	{
		if (c == VALID[i])
			return (1);
	}
	return (0);
}

bool	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}
