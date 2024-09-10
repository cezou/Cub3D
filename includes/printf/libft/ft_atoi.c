/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:27:13 by pmagnero          #+#    #+#             */
/*   Updated: 2023/11/08 15:41:05 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include <stdio.h> */
#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int		sign;
	size_t	i;
	int		result;

	sign = 1;
	result = 0;
	i = 0;
	if (*nptr == '\0')
		return (0);
	while (nptr[i] == 32 || (nptr[i] > 8 && nptr[i] < 14))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign++;
		if (nptr[++i] == '-' || nptr[i] == '+')
			return (0);
	}
	i--;
	while (nptr[++i] >= '0' && nptr[i] <= '9')
		result = result * 10 + (nptr[i] - '0');
	if (sign % 2 == 0)
		result = -result;
	return (result);
}

/* int	main(void) */
/* { */
/* 	printf("42:%d", ft_atoi("  \n  42t4457")); */
/* 	printf("|%d\n", atoi("  \n  42t4457")); */
/* 	printf("-42:%d", ft_atoi(" ---+42sfs:f545")); */
/* 	printf("|%d\n", atoi(" -42sfs:f545")); */
/* 	printf("0:%d", ft_atoi("\0 1337")); */
/* 	printf("|%d\n", atoi("\0 1337")); */
/* 	printf("0:%d", ft_atoi("-0")); */
/* 	printf("|%d\n", atoi("-0")); */
/* 	printf("0:%d", ft_atoi(" - 1 3 2 5 6 3 2 1 6 7")); */
/* 	printf("|%d\n", atoi(" - 1 3 2 5 6 3 2 1 6 7")); */
/* 	printf("-1325632167:%d", ft_atoi("-1325632167")); */
/* 	printf("|%d\n", atoi("-1325632167")); */
/* 	printf("-100:%d", ft_atoi("-100")); */
/* 	printf("|%d\n", atoi("-100")); */
/* 	printf("min:%d", ft_atoi("\t---+2147483648")); */
/* 	printf("|%d\n", atoi("\t-2147483648")); */
/* 	printf("max:%d", ft_atoi("\t+2147483647")); */
/* 	printf("|%d\n", atoi("\t2147483647")); */
/* 	printf("max:%d", ft_atoi("\0")); */
/* 	printf("|%d\n", atoi("\0")); */
/* } */
