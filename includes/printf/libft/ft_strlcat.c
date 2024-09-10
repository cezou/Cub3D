/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:26:33 by pmagnero          #+#    #+#             */
/*   Updated: 2023/11/07 11:06:31 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/* #include <stdio.h> */
/* #include <bsd/string.h> */

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char			*d;
	const char		*s;
	size_t			n;
	size_t			len;

	d = dst;
	s = src;
	n = size;
	while (n-- != 0 && *d != '\0')
		d++;
	len = d - dst;
	n = size - len;
	if (n == 0)
		return (len + ft_strlen(s));
	while (*s != '\0')
	{
		if (n != 1)
		{
			*d++ = *s;
			n--;
		}
		s++;
	}
	*d = '\0';
	return (len + (s - src));
}

/* int	main(int ac, char **av) */
/* { */
/* 	char s1a[10] = "Test1"; */
/* 	char s2a[] = "OKe"; */
/* 	char s1b[10] = "Test1"; */
/* 	char s2b[] = "OKe"; */
/* 	char s3a[10] = "Same"; */
/* 	char s4a[] = "Size"; */
/* 	char s3b[10] = "Same"; */
/* 	char s4b[] = "Size"; */
/* 	char s5a[20] = "Shorter"; */
/* 	char s6a[] = "ThanMyself"; */
/* 	char s5b[20] = "Shorter"; */
/* 	char s6b[] = "ThanMyself"; */
/* 	char s7a[20] = "Shorter"; */
/* 	char s8a[] = "ThanMyself"; */
/* 	char s7b[20] = "Shorter"; */
/* 	char s8b[] = "ThanMyself"; */

/* 	unsigned int k1 = ft_strlcat(s1a, s2a, 6); */
/* 	unsigned int x1 = strlcat(s1b, s2b, 6); */
/* 	unsigned int k2 = ft_strlcat(s3a, s4a, 10); */
/* 	unsigned int x2 = strlcat(s3b, s4b, 10); */
/* 	/\* unsigned int k1 = ft_strlcat(s1a, s2a, 6); *\/ */
/* 	/\* unsigned int x1 = strlcat(s1b, s2b, 6); *\/ */

/*  printf("%s | %d | %d\n", k1 == x1 ? "Success" : "Fail", k1, x1); */
/* 	printf("%s\n", strcmp(s1a, s1b) == 0 */
/*  && strcmp(s2a, s2b) == 0 ? "Success" : "Fail"); */
/* 	printf("%s | %d | %d\n", k2 == x2 ? "Success" : "Fail", k2, x2); */
/* 	printf("%s\n", strcmp(s3a, s3b) == 0 */
/*  && strcmp(s4a, s4b) == 0 ? "Success" : "Fail"); */
/* 	printf("%s\n", ft_strlcat(s5a, s6a, 4) == */
/*  strlcat(s5b, s6b, 4) ? "Success" : "Fail"); */
/* 	printf("%s\n", strcmp(s5a, s5b) == 0 */
/*  && strcmp(s6a, s6b) == 0 ? "Success" : "Fail"); */
/* 	printf("%s\n", ft_strlcat(s7a, s8a, 0) == */
/*  strlcat(s7b, s8b, 0) ? "Success" : "Fail"); */
/* 	printf("%s\n", strcmp(s7a, s7b) == 0 */
/*  && strcmp(s8a, s8b) == 0 ? "Success" : "Fail"); */
/* 	printf("\n\nDetails:\n"); */
/* 	printf("%s:%sK\n%s:%s\n", s1a, s1b, s2a, s2b); */
/* 	printf("%s:%s\n%s:%s\n", s3a, s3b, s4a, s4b); */
/* 	printf("%s:%s\n%s:%s\n", s5a, s5b, s6a, s6b); */
/* 	printf("%s:%s\n%s:%s\n", s7a, s7b, s8a, s8b); */
/* } */
