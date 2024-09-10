/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:15:09 by pmagnero          #+#    #+#             */
/*   Updated: 2023/11/09 14:15:45 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_itoa_size(int nbr, char *base, int len)
{
	char	c[33];
	char	*p;
	int		size;

	p = c + 33;
	size = 0;
	if (nbr == 0)
		return (1);
	if (nbr < 0)
		nbr = -nbr;
	while (nbr != 0)
	{
		*--p = base[nbr % len];
		nbr /= len;
		size++;
	}
	return (size);
}

static void	ft_itoa_loop(int nbr, char *base, int len, char *result)
{
	int	size;
	int	offset;

	offset = 0;
	size = ft_strlen(result);
	if (nbr == 0)
		result[--size] = base[nbr];
	if (nbr == -2147483648)
	{
		result[0] = '-';
		result[1] = '2';
		nbr = 147483648;
		offset = 2;
	}
	if (nbr < 0)
	{
		nbr = -nbr;
		result[0] = '-';
		offset = 1;
	}
	while (size > offset)
	{
		result[--size] = base[nbr % len];
		nbr /= len;
	}
}

char	*ft_itoa(int n)
{
	char	*res;
	int		len;
	char	*base;

	base = "0123456789";
	len = ft_itoa_size(n, base, 10);
	if (n < 0)
		len++;
	res = (char *)malloc(sizeof(*res) * (len + 1));
	if (!res)
		return (NULL);
	res[len] = 0;
	while (--len > -1)
		res[len] = 'q';
	ft_itoa_loop(n, base, 10, res);
	return (res);
}
/* #include <stdio.h> */

/* int	main(int ac, char **av) */
/* { */
/* 	char	*result; */

/* 	if (ac < 2) */
/* 		return (0); */
/* 	result = ft_itoa(atoi(av[1])); */
/* 	printf("K%sK", result); */
/* 	printf("Y%dY", atoi(av[1])); */
/* 	/\* free(result); *\/ */
/* } */
