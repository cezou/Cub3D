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

void	s(void)
{
	static int count = 0;
	static int color_index = 0;
	const char *colors[] = {"\033[1;31m", "\033[1;32m", "\033[1;33m",
		"\033[1;34m", "\033[1;35m", "\033[1;36m", "\033[1;37m"};
	int num_colors = sizeof(colors) / sizeof(colors[0]);

	printf("%sSquid: %d\033[0m\n", colors[color_index], count);
	count++;
	color_index = (color_index + 1) % num_colors;
}