/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:34:04 by pmagnero          #+#    #+#             */
/*   Updated: 2023/11/09 15:06:05 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	h;
	size_t	n;

	if (!big && len == 0)
		return (NULL);
	h = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while (big[h] != '\0')
	{
		n = 0;
		while (big[h + n] == little[n] && (h + n) < len)
		{
			if (big[h + n] == '\0' && little[n] == '\0')
				return ((char *)&big[h]);
			n++;
		}
		if (little[n] == '\0')
			return ((char *)big + h);
		h++;
	}
	return (0);
}

/* #include <stdio.h> */
/* #include <bsd/string.h> */

/* int main(void) */
/* { */
/* 	char haystack[30] = "aaabcabcd"; */
/* 	char needle[10] = "aabc"; */
/* 	printf("KEK%sKAK%sKUK",
 ft_strnstr(haystack, needle, -1),
 strnstr(haystack, needle, -1)); */
/* } */
