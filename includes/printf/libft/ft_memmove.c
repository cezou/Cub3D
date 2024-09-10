/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:37:27 by pmagnero          #+#    #+#             */
/*   Updated: 2023/11/09 14:57:30 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*from;
	char	*to;
	size_t	i;

	if (!dest && !src)
		return (NULL);
	from = (char *) src;
	to = (char *) dest;
	if (to > from)
		while (n-- > 0)
			to[n] = from[n];
	else
	{
		i = -1;
		while (++i < n)
			to[i] = from[i];
	}
	return (dest);
}
