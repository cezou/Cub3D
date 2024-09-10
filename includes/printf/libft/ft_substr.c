/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:05:04 by pmagnero          #+#    #+#             */
/*   Updated: 2023/11/09 10:23:31 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*sub;
	unsigned int	i;
	size_t			slen;

	if (!s)
		return (NULL);
	i = 0;
	slen = len;
	if (start > ft_strlen(s))
	{
		sub = ft_calloc(1, 1);
		return (sub);
	}
	while (s[start + i] != 0 && len-- > 0)
		i++;
	sub = (char *)malloc(sizeof(char) * (i + 1));
	if (!sub)
		return (NULL);
	*sub = 0;
	s = s + start;
	i = 0;
	while (*s != 0 && slen-- > 0)
		sub[i++] = *s++;
	sub[i] = 0;
	return (sub);
}
