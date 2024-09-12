/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:22:46 by cviegas           #+#    #+#             */
/*   Updated: 2024/09/12 17:22:47 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	perr(const char *s)
{
	ft_printf(STDERR, "%sError\n%s%s%s\n", RED, LIL_RED, s, RCOLOR);
}

void	merr(const char *s)
{
	ft_printf(STDERR, "%sError\nMap: %s%s%s%s\n", RED, RCOLOR, LIL_RED, s,
		RCOLOR);
}

void	lerr(size_t i, const char *s)
{
	ft_printf(STDERR, "%sError\nLine %s%u%s: %s%s%s%s\n", RED, YELLOW, i, RED,
		RCOLOR, LIL_RED, s, RCOLOR);
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
