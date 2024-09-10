/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 09:46:56 by pmagnero          #+#    #+#             */
/*   Updated: 2023/12/12 14:27:21 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(const char *nptr)
{
	int			sign;
	size_t		i;
	long		result;

	sign = 1;
	result = 0;
	i = 0;
	if (*nptr == '\0')
		return (0);
	while (nptr[i] == 32 || (nptr[i] > 8 && nptr[i] < 14))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign++;
		if (nptr[++i] == '-' || nptr[i] == '+')
			return (0);
	}
	i--;
	while (nptr[++i] >= '0' && nptr[i] <= '9')
		result = result * 10 + (nptr[i] - '0');
	if (sign % 2 == 0)
		result = -result;
	return (result);
}
