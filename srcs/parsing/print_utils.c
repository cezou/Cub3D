/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 21:44:07 by cviegas           #+#    #+#             */
/*   Updated: 2024/09/18 21:44:15 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	s(void)
{
	static int	count = 0;
	static int	color_index = 0;
	const char	*colors[] = {"\033[1;31m", "\033[1;32m", "\033[1;33m",
		"\033[1;34m", "\033[1;35m", "\033[1;36m", "\033[1;37m"};
	int			num_colors;

	num_colors = sizeof(colors) / sizeof(colors[0]);
	printf("%sSquid: %d\033[0m\n", colors[color_index], count);
	count++;
	color_index = (color_index + 1) % num_colors;
}

void	cerr(int i, int j)
{
	ft_printf(STDERR,
		RED "Error\nMap: " RCOLOR LIL_RED "Char at line %d, column\
		%d (± 1) isn't surround by walls\n" RCOLOR,
		i,
		j);
}

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
