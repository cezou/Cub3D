/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atold.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 09:46:56 by pmagnero          #+#    #+#             */
/*   Updated: 2024/03/06 14:05:46 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long double	sauce(const char *p, long double r, size_t *dec, size_t *i)
{
	while ((p[++(*i)] >= '0' && p[*i] <= '9')
		|| (p[*i] == '.' && p[*i + 1] >= '0' && p[*i + 1] <= '9' && *dec == 0))
	{
		if (p[*i] == '.')
		{
			*dec = *i;
			(*i)++;
		}
		r = r * 10 + (p[*i] - '0');
	}
	return (r);
}

long double	ft_atold(const char *p)
{
	int			sign;
	size_t		i;
	long double	result;
	size_t		dec;

	sign = 1;
	result = 0.0;
	i = -1;
	dec = 0;
	if (*p == '\0')
		return (0.0);
	if (p[i + 1] == '-')
		sign++;
	if (sign)
		i++;
	result = sauce(p, result, &dec, &i);
	if (i != ft_strlen(p))
		return (0.0);
	while (--i > dec)
		result = result / 10;
	if (sign % 2 == 0)
		result = -result;
	return (result);
}
