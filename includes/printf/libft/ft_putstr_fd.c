/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:26:28 by pmagnero          #+#    #+#             */
/*   Updated: 2023/11/09 15:07:38 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	char	buffer[1000000];
	size_t	buffer_index;
	size_t	i;

	if (!s)
		return ;
	i = -1;
	buffer_index = 0;
	while (s[++i] != '\0')
	{
		buffer[buffer_index++] = s[i];
		if (buffer_index == 1000000)
		{
			write(fd, buffer, 1000000);
			buffer_index = 0;
		}
	}
	write(fd, buffer, buffer_index);
}
