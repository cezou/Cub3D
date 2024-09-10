/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtolower.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:15:23 by pmagnero          #+#    #+#             */
/*   Updated: 2024/01/30 17:18:05 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtolower(char *s)
{
	int	i;

	i = -1;
	if (!s)
		return (NULL);
	while (s[++i])
		s[i] = ft_tolower(s[i]);
	return (s);
}
