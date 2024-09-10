/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:55:01 by pmagnero          #+#    #+#             */
/*   Updated: 2023/11/08 14:12:34 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*dst;
	const char	*srcb;

	dst = (char *)dest;
	srcb = (char *)src;
	if (n == 0 || dst == srcb)
		return (dest);
	while (n-- > 0)
		*(dst++) = *(srcb++);
	return (dest);
}
