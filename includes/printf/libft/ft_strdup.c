/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:28:01 by pmagnero          #+#    #+#             */
/*   Updated: 2023/11/07 11:11:55 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/* #include <stdio.h> */
/* #include <string.h> */

char	*ft_strdup(const char *s)
{
	char		*dest;
	size_t		len;

	len = 0;
	while (s[len])
		len++;
	dest = (char *)malloc((len + 1) * sizeof(*dest));
	if (!dest)
		return (NULL);
	*dest = 0;
	len = 0;
	while (*s)
	{
		dest[len] = *s;
		s++;
		len++;
	}
	dest[len] = 0;
	return (dest);
}

/* int	main(int ac, char **av) */
/* { */
/* 	if (ac != 2) */
/* 		return (0); */
/* 	printf("%%%s%%\n", ft_strdup(av[1])); */
/* 	printf("%%%s%%", strdup(av[1])); */
/* 	return (0); */
/* } */
