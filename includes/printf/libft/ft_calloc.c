/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:43:46 by pmagnero          #+#    #+#             */
/*   Updated: 2023/11/08 15:13:39 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	t;

	if (nmemb > size)
		t = size;
	else
		t = nmemb;
	if (nmemb * size < t || nmemb * size > 2147483647)
		return (NULL);
	ptr = (void *)malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	if (ptr)
		ft_bzero(ptr, nmemb * size);
	return (ptr);
}
