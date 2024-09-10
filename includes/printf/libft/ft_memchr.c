/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:24:07 by pmagnero          #+#    #+#             */
/*   Updated: 2023/11/08 14:29:00 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*big;
	size_t			i;

	big = (void *) s;
	i = -1;
	while (++i < n)
	{
		if (big[i] == (unsigned char)c)
			return (&big[i]);
	}
	return (NULL);
}
