/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:19:42 by pmagnero          #+#    #+#             */
/*   Updated: 2023/11/09 14:47:10 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char ))
{
	char			*s1;
	unsigned int	i;

	i = -1;
	if (!s || !f)
		return (NULL);
	s1 = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!s1)
		return (NULL);
	ft_strlcpy(s1, s, ft_strlen(s) + 1);
	while (s1[++i])
		s1[i] = (*f)(i, s1[i]);
	s1[i] = 0;
	return (s1);
}
