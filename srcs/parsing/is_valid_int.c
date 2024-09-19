/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cviegas <cviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:22:11 by cviegas           #+#    #+#             */
/*   Updated: 2024/09/12 17:22:11 by cviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static size_t	skip_i_and_sign(const char *s, int *sign, bool *is_there_plus)
{
	size_t	i;

	i = 0;
	*sign = 1;
	if (s[i] == '+')
	{
		*is_there_plus = 1;
		i++;
	}
	else if (s[i] == '-')
	{
		*sign = -1;
		i++;
	}
	return (i);
}

bool	is_valid_int(const char *s)
{
	long long int	atonb;
	size_t			i;
	int				sign;
	bool			voidb;

	if (!s || !s[0])
		return (0);
	atonb = 0;
	i = skip_i_and_sign(s, &sign, &voidb);
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		atonb *= 10;
		atonb += s[i] - '0';
		if (atonb > 255)
			return (0);
		i++;
	}
	atonb *= sign;
	if (atonb >= 0 && atonb <= 255)
		return (1);
	return (0);
}
