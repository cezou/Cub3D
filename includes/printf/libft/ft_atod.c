/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:39:38 by pmagnero          #+#    #+#             */
/*   Updated: 2024/03/04 14:42:07 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	sauce(const char *p, float result, size_t *dec, size_t *i)
{
	while ((p[++(*i)] >= '0' && p[*i] <= '9')
		|| (p[*i] == '.' && p[*i + 1] >= '0' && p[*i + 1] <= '9' && *dec == 0))
	{
		if (p[*i] == '.')
		{
			*dec = *i;
			(*i)++;
		}
		result = result * 10 + (p[*i] - '0');
	}
	return (result);
}

double	ft_atod(const char *p)
{
	int		sign;
	size_t	i;
	double	result;
	size_t	dec;

	sign = 1;
	result = 0.0;
	i = -1;
	dec = 0;
	if (*p == '\0')
		return (0.0);
	if (p[++i] == '-')
		sign++;
	if (p[i + 1] == '-' || p[i + 1] == '+')
		return (0.0);
	result = sauce(p, result, &dec, &i);
	if (i != ft_strlen(p))
		return (0.0);
	while (--i > dec)
		result = result / 10;
	if (sign % 2 == 0)
		result = -result;
	return (result);
}
