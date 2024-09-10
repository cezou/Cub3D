/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:03:57 by pmagnero          #+#    #+#             */
/*   Updated: 2023/11/07 18:06:08 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*found;
	const char	*p;

	c = (unsigned char) c;
	if (c == '\0')
		return (ft_strchr(s, '\0'));
	found = NULL;
	while (1)
	{
		p = ft_strchr(s, c);
		if (p == NULL)
			break ;
		found = p;
		s = p + 1;
	}
	return ((char *) found);
}

/* #include <stdio.h> */
/* #include <string.h> */

/* int main(void) */
/* { */
/* 	char s[] = "tripouille"; */
/* 	printf("KEK"); */
/* 	printf("%s", ft_strrchr(s, 't' + 256)); */
/* 	printf("KAK"); */
/* 	printf("%s", strrchr(s, 't' + 256)); */
/* 	printf("KUK"); */
/* } */
