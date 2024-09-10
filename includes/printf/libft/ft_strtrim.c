/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:10:27 by pmagnero          #+#    #+#             */
/*   Updated: 2023/11/09 18:04:31 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	ft_issep(const char *sep, char c)
{
	size_t	i;

	i = -1;
	while (sep[++i] != 0)
	{
		if (c == sep[i])
			return (1);
	}
	return (0);
}

static int	ft_loop(char const *s1, char const *s2, int order)
{
	int	e;
	int	b;
	int	i;

	i = -1;
	b = 0;
	if (order == 0)
	{
		while (s1[++i] != 0 && ft_issep(s2, s1[i]) == 1)
			b++;
		return (b);
	}
	i = ft_strlen(s1);
	e = i;
	while (s1[--i] != 0 && ft_issep(s2, s1[i]) == 1)
		e--;
	return (e);
}

char	*ft_strtrim(char const *s1, char const *s2)
{
	char	*s;
	int		b;
	int		e;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	i = -1;
	b = ft_loop(s1, s2, 0);
	e = ft_loop(s1, s2, 1);
	if (e - b <= 0)
	{
		s = ft_calloc(1, 1);
		*s = 0;
		return (s);
	}
	s = (char *)malloc(sizeof(char) * (e - b + 1));
	if (!s)
		return (NULL);
	i = -1;
	while (b < e)
		s[++i] = s1[b++];
	s[++i] = 0;
	return (s);
}
