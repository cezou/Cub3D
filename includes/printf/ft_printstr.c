/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:26:35 by pmagnero          #+#    #+#             */
/*   Updated: 2024/02/28 13:18:37 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printstr(t_flags flags, int c, char *str, char fid)
{
	long int	min;

	min = flags.min;
	if (flags.min != 0)
	{
		c += ft_strlen(str);
		if (flags.minus == 1)
			ft_putstr_fd(str, flags.fd);
		min -= ft_strlen(str);
		while (min-- > 0)
			c += write(flags.fd, " ", 1);
		if (flags.minus == 0)
			ft_putstr_fd(str, flags.fd);
	}
	else
	{
		c += ft_strlen(str);
		ft_putstr_fd(str, flags.fd);
	}
	if (flags.max > 0 || fid == 'c')
		free(str);
	return (c);
}

int	ft_str(va_list pI, int c, t_flags flags, char fid)
{
	char	*strcpy;
	char	*str;

	if (fid == '%')
		return (c + write(flags.fd, "%", 1));
	if (fid == 'c')
	{
		fid = (char) va_arg(pI, int);
		if (flags.minus == 1)
			c += write(flags.fd, &fid, 1);
		while (--flags.min > 0)
			c += write(flags.fd, " ", 1);
		if (flags.minus == 0)
			c += write(flags.fd, &fid, 1);
		return (c);
	}
	strcpy = (char *) va_arg(pI, char *);
	if (!strcpy && (flags.max > 5 || flags.max < 0))
		strcpy = "(null)";
	str = strcpy;
	if (flags.max > 0)
		str = ft_substr(strcpy, 0, flags.max);
	if (flags.max == 0)
		str = "";
	return (ft_printstr(flags, c, str, fid));
}
