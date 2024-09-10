/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:26:35 by pmagnero          #+#    #+#             */
/*   Updated: 2023/12/01 17:42:31 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long	ft_printx(t_flags f, long int zeros, int *k, unsigned int d)
{
	int	len;

	len = *k;
	if ((f.min > 0 && f.minus == 0 && f.zero == ' '))
		ft_printspaces(zeros, k, f.zero, f.fd);
	if (f.max > 0)
		zeros = f.max - (*k);
	if (f.max > 0 && f.max < f.min && f.dot == 1 && f.minus == 0)
		zeros = f.max - len;
	if (f.hash == 1 && d != 0 && f.fid[10] >= 'A' && f.fid[10] <= 'Z')
		*k += write(f.fd, "0X", 2);
	else if (f.hash == 1 && d != 0 && f.fid[10] >= 'a' && f.fid[10] <= 'z')
		*k += write(f.fd, "0x", 2);
	if (f.plus != 'n')
		*k += write(f.fd, &f.plus, 1);
	if ((zeros > 0 && f.hash == 1 && f.dot == 1)
		|| f.max - *k >= 0 || (f.max > 0 && f.max < f.min
			&& f.dot == 1 && *k >= f.max)
		|| (f.min > 0 && f.minus == 0 && f.zero == '0'))
		ft_printspaces(zeros, k, '0', f.fd);
	return (zeros);
}

static long	ft_initzero(t_flags *f, int len, long d)
{
	long	zeros;

	zeros = 0;
	zeros = f->min - len - f->isneg;
	if (f->max < f->min && f->dot == 1 && f->max > len)
		zeros = f->min - f->max - f->isneg;
	if (f->min <= f->max && f->dot == 1 && f->min > len)
	{
		zeros = f->max;
		f->zero = '0';
	}
	if ((f->zero == '0' && f->dot == 1 && f->min > f->max && f->max > 0)
		|| (d == 0 && f->zero == '0' && f->dot == 1 && f->max == 0))
		f->zero = ' ';
	if (f->plus == ' ' || f->plus == '+' || (f->hash == 1 && d > 0))
		zeros = zeros - 1 - f->hash;
	return (zeros);
}

int	ft_x(int c, long d, t_flags f)
{
	int			*k;
	long int	zeros;
	int			len;

	len = 0;
	k = &len;
	ft_getdecx(d, f.fid, ft_strlen(f.fid), k);
	if (d == 0 && f.max == 0 && f.min == 0)
		return (c);
	zeros = ft_initzero(&f, len, d);
	zeros = ft_printx(f, zeros, k, d);
	if ((d == 0 && f.max == 0 && f.dot == 1)
		|| (d == 0 && f.minus == 1 && f.dot == 1 && f.max == 0))
		write(f.fd, " ", 1);
	else
		ft_putnbr_base(d, f.fid, ft_strlen(f.fid), f.fd);
	zeros = f.min - *k;
	if (zeros > 0 && ((f.dot == 1 && f.max > 0) || (f.minus == 1)))
		ft_printspaces(zeros, k, ' ', f.fd);
	return (len + c);
}
