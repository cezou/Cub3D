/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:39:38 by pmagnero          #+#    #+#             */
/*   Updated: 2024/10/27 19:20:29 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	sauce(const char *p, float result, size_t *i)
{
	while ((p[(*i)] >= '0' && p[*i] <= '9'))
	{
		result = result * 10 + (p[(*i)] - '0');
		(*i)++;
	}
	return (result);
}

double	ft_atod(const char *p)
{
	int		sign;
	size_t	i;
	double	result;
	double	dec;

	size_t (dot) = 0;
	sign = 1;
	result = 0.0;
	i = -1;
	dec = 0.0;
	if (*p == '\0')
		return (0.0);
	if (p[++i] == '-')
		sign++;
	if (p[i + 1] == '-' || p[i + 1] == '+')
		return (0.0);
	result = sauce(p, result, &i);
	if (p[i++] == '.')
		dec = sauce((dot = i - 1, p), dec, &i);
	while (--i > dot)
		dec = dec / 10;
	result += dec;
	if (sign % 2 == 0)
		result = -result;
	return (result);
}
