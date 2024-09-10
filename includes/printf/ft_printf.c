/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:26:35 by pmagnero          #+#    #+#             */
/*   Updated: 2024/01/29 12:10:57 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_kek(char c, t_flags *flags)
{
	if (c == '-')
		flags->minus = 1;
	if (c == '0')
		flags->zero = '0';
	if (c == ' ')
		flags->plus = ' ';
	if (c == '+')
		flags->plus = '+';
	if (c == '#')
		flags->hash = 1;
}

void	ft_parseflags(char *tmp, t_flags *flags, int b, int i)
{
	char		*w_str;

	while (tmp[++i] != 0)
	{
		ft_kek(tmp[i], flags);
		if (ft_isdigit(tmp[i]) && tmp[i] != '0')
		{
			b = i;
			while (ft_isdigit(tmp[++i]) != 0)
				;
			w_str = ft_substr(&tmp[b], 0, i - b);
			flags->min = ft_atoi(w_str);
			free(w_str);
		}
		if (tmp[i] == '.')
		{
			flags->dot = 1;
			b = ++i;
			while (ft_isdigit(tmp[i]) != 0)
				i++;
			w_str = ft_substr(&tmp[b], 0, i - b);
			flags->max = ft_atoi(w_str);
			free(w_str);
		}
	}
}

t_flags	ft_init(char fid, char *tmp, int fd)
{
	t_flags	flags;

	if (fid == 'x')
		flags.fid = "0123456789abcdef";
	else if (fid == 'X')
		flags.fid = "0123456789ABCDEF";
	else
		flags.fid = "0123456789";
	flags.min = 0;
	flags.max = -1;
	flags.minus = 0;
	flags.zero = ' ';
	flags.dot = 0;
	flags.plus = 'n';
	flags.isneg = 0;
	flags.hash = 0;
	flags.fd = fd;
	flags.c = 0;
	if (tmp)
		ft_parseflags(tmp, &flags, 0, -1);
	return (flags);
}

int	ft_argtype(char fid, va_list pI, char *tmp, int fd)
{
	t_flags	flags;
	long	d;

	flags = ft_init(fid, tmp, fd);
	if (fid == 's' || fid == 'c' || fid == '%')
		flags.c = ft_str(pI, flags.c, flags, fid);
	else if (fid == 'p')
		flags.c = ft_p(pI, flags.c, flags);
	else if (fid == 'x' || fid == 'X' || fid == 'u' || fid == 'd' || fid == 'i')
	{
		if (fid == 'd' || fid == 'i')
		{
			d = (int) va_arg(pI, int);
			if (d < 0)
			{
				flags.plus = '-';
				flags.isneg = 1;
			}
		}
		else
			d = (unsigned int) va_arg(pI, unsigned int);
		flags.c = ft_x(flags.c, ft_abs(d), flags);
	}
	free(tmp);
	return (flags.c);
}

int	ft_printf(int f, const char *format, ...)
{
	int		c;
	int		i;
	int		b;
	va_list	p;

	i = -1;
	c = 0;
	va_start(p, format);
	while (format[++i] != 0)
	{
		if (format[i] != '%')
			c += write(f, &format[i], 1);
		else
		{
			b = i++;
			while (ft_isformatid(format[i]) == 0)
				i++;
			c += ft_argtype((format[i]), p, ft_substr(&format[b], 1, i - b), f);
			if (c < 0)
				break ;
		}
	}
	va_end(p);
	return (c);
}
