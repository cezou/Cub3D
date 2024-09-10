/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:50:05 by pmagnero          #+#    #+#             */
/*   Updated: 2023/11/07 18:13:03 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	cc;

	cc = c;
	while (1)
	{
		if (*s == cc)
			return ((char *)s);
		if (*s == '\0')
			return (NULL);
		s++;
	}
}

/* #include <stdio.h> */
/* #include <string.h> */

/* int main(void) */
/* { */
/* 	char s[] = "tripouille"; */
/* 	printf("KEK%sKAK%sKUK", ft_strchr(s, 0), strchr(s, 0)); */
/* } */
