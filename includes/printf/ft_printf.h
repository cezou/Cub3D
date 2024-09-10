/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 14:51:17 by pmagnero          #+#    #+#             */
/*   Updated: 2023/11/16 18:07:37 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include "libft/libft.h"
/*TO REMOVE */
# include <stdio.h>

typedef struct s_flags
{
	char		*fid;
	long int	min;
	long int	max;
	int			minus;
	char		zero;
	int			dot;
	char		plus;
	int			isneg;
	int			hash;
	int			fd;
	int			c;
}		t_flags;

int		ft_printf(int fd, const char *format, ...);

int		ft_isformatid(char c);
void	ft_getdecx(unsigned int nbr, char *b, unsigned int len, int *size);
void	ft_putnbr_base(long long int nbr, char *b, unsigned int len, int fd);

void	ft_parseflags(char *tmp, t_flags *flags, int b, int i);
int		ft_argtype(char fid, va_list pI, char *tmp, int fd);
void	ft_printspaces(long int zeros, int *len, char space, int fd);

long	ft_printx(t_flags f, long int zeros, int *k, unsigned int d);
int		ft_x(int c, long d, t_flags flags);
int		ft_printstr(t_flags flags, int c, char *str, char fid);
int		ft_str(va_list pI, int c, t_flags flags, char fid);
int		ft_print_addr(unsigned long int addr, t_flags flags);
int		ft_p(va_list pI, int c, t_flags flags);

#endif
