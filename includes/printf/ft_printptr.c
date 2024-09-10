/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:26:35 by pmagnero          #+#    #+#             */
/*   Updated: 2024/02/28 13:18:47 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_addr(unsigned long int addr, t_flags flags)
{
	char	buff[17];
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (addr > 0)
	{
		buff[i++] = "0123456789abcdef"[addr % 16];
		addr /= 16;
	}
	write(flags.fd, "0x", 2);
	len = i;
	while (i > 0)
		write(flags.fd, &buff[--i], 1);
	return (len + 2);
}

int	ft_p(va_list pI, int c, t_flags flags)
{
	void				*d;
	int					i;
	long int			min;
	unsigned long int	addr;

	min = flags.min;
	i = 0;
	d = (void *) va_arg(pI, void *);
	addr = (unsigned long int) d;
	while (addr > 0 && ++i > 0)
		addr /= 16;
	min -= i + 2;
	if (!d)
		min = flags.min - 5;
	if (flags.minus == 0)
		while (min-- > 0)
			c += write(flags.fd, " ", 1);
	if (!d)
		c += write(flags.fd, "(nil)", 5);
	else
		c += ft_print_addr((unsigned long int)d, flags);
	if (flags.minus == 1)
		while (min-- > 0)
			c += write(flags.fd, " ", 1);
	return (c);
}
