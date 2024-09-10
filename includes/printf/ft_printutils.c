/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printutils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:26:35 by pmagnero          #+#    #+#             */
/*   Updated: 2024/02/05 09:28:55 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_isformatid(char c)
{
	return (c == 'c' || c == 's'
		|| c == 'p' || c == 'd'
		|| c == 'i' || c == 'u'
		|| c == 'x' || c == 'X' || c == '%');
}

void	ft_getdecx(unsigned int nbr, char *b, unsigned int len, int *size)
{
	if (nbr < len)
		(*size)++;
	if (nbr >= len)
	{
		ft_getdecx(nbr / len, b, len, size);
		ft_getdecx(nbr % len, b, len, size);
	}
}

void	ft_putnbr_base(long long int nbr, char *b, unsigned int len, int fd)
{
	if (nbr < 0)
		nbr = -nbr;
	if (nbr < len)
		write(fd, &b[nbr], 1);
	if (nbr >= len)
	{
		ft_putnbr_base(nbr / len, b, len, fd);
		ft_putnbr_base(nbr % len, b, len, fd);
	}
}

void	ft_printspaces(long int zeros, int *len, char space, int fd)
{
	while (zeros-- > 0)
		*len += write(fd, &space, 1);
}
