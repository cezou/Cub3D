/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:25:54 by pmagnero          #+#    #+#             */
/*   Updated: 2023/11/07 11:07:22 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/* #include <string.h> */
/* #include <stdio.h> */

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int				i;
	unsigned char	c1;
	unsigned char	c2;

	i = 0;
	while (n-- && (*s1 || *s2))
	{
		c1 = *s1;
		c2 = *s2;
		i = c1 - c2;
		if (*s1 != *s2)
			break ;
		s1++;
		s2++;
	}
	return (i);
}

/* int main(int ac, char**av) */
/* { */
/* 	int n; */
/* 	size_t k = 3; */

/* 	n = 3; */
/* 	if (ac > 2) */
/* 	{ */
/* 		printf("%d\n", ft_strncmp(av[1], av[2], n)); */
/* 		printf("%d", strncmp(av[1], av[2], k)); */
/* 	} */
/* } */
