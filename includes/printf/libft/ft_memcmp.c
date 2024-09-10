/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:29:33 by pmagnero          #+#    #+#             */
/*   Updated: 2023/11/08 14:52:50 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned const char	*p1;
	unsigned const char	*p2;
	int					i;

	i = 0;
	p1 = (unsigned const char *)s1;
	p2 = (unsigned const char *)s2;
	if (n != 0)
	{
		while (n > 0)
		{
			if (*p1 != *p2)
			{
				i = *p1 - *p2;
				return (i);
			}
			p1++;
			p2++;
			n--;
		}
	}
	return (0);
}
