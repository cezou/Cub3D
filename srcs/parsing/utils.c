/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:22:46 by cviegas           #+#    #+#             */
/*   Updated: 2024/09/19 19:05:12 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

bool	is_in_string(char c, char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (c == s[i])
			return (1);
	}
	return (0);
}

int	cmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

size_t	tab_len(char **tab)
{
	int	i;

	if (!tab)
		return (0);
	i = -1;
	while (tab[++i])
		;
	return (i);
}

char	**tab_dup(char **tab)
{
	char	**dup;
	int		i;

	dup = malloc((tab_len(tab) + 1) * sizeof(char *));
	if (!dup)
		return (NULL);
	i = -1;
	while (tab[++i])
	{
		dup[i] = ft_strdup(tab[i]);
		if (!dup[i])
			return (freeall(dup), NULL);
	}
	dup[i] = 0;
	return (dup);
}
