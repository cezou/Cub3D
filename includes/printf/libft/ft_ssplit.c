/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssplit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:12:20 by pmagnero          #+#    #+#             */
/*   Updated: 2024/02/28 13:18:24 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isd(char *delim, char c)
{
	int	i;

	i = -1;
	while (delim[++i])
		if (delim[i] == c)
			return (1);
	return (0);
}

static int	ft_count_words(const char *str, char *c, char *q)
{
	int	i;
	int	count;
	int	quote;

	i = -1;
	count = 0;
	quote = 0;
	while (str[++i] != '\0')
	{
		if (ft_isd(q, str[i]))
			quote++;
		if (quote % 2 != 0)
			continue ;
		if ((ft_isd(c, str[i + 1]) || ft_isd(q, str[i + 1]) || str[i + 1] == 0)
			&& !ft_isd(c, str[i]))
			count++;
	}
	return (count);
}

static t_var	initvars(void)
{
	t_var	vars;

	vars.c = 0;
	vars.i = -1;
	vars.q = 0;
	vars.w = 0;
	return (vars);
}

static int	ft_assign(const char *s, char **res, t_var *v, char **d)
{
	while (s[++(v->i)] != '\0')
	{
		if (ft_isd(d[1], s[(v->i)]))
			v->q++;
		if (v->q % 2 != 0)
			continue ;
		if (ft_isd(d[0], s[(v->i)]) || s[(v->i)] == 0)
			v->c = v->i + 1;
		if (!ft_isd(d[0], s[v->i]) && (ft_isd(d[0], s[v->i + 1])
				|| ft_isd(d[1], s[v->i + 1]) || s[v->i + 1] == 0))
		{
			res[v->w] = malloc(sizeof(char) * ((v->i) - v->c + 2 - v->q));
			if (!res[v->w])
				return (v->w);
			if (v->q != 2)
				ft_strlcpy(res[v->w], (s + (v->c)), v->i - v->c + 2);
			else
				ft_strlcpy(res[v->w], (s + (v->c + 1)), v->i - v->c + 2 - v->q);
			v->w++;
			v->q = 0;
		}
	}
	return (0);
}

// #include <stdio.h>

char	**ft_ssplit(char const *s, char *c, char *q)
{
	char	**res;
	size_t	size;
	size_t	i;
	t_var	v;
	char	*d[2];

	if (!s || !c)
		return (NULL);
	v = initvars();
	size = ft_count_words(s, c, q);
	res = NULL;
	d[0] = c;
	d[1] = q;
	res = (char **)malloc(sizeof(*res) * (size + 1));
	if (!res)
		return (NULL);
	v.w = ft_assign(s, res, &v, d);
	if (v.w > 0)
	{
		i = -1;
		while (++i < v.w)
			free(res[i]);
		return (free(res), NULL);
	}
	return ((res[size] = 0), res);
}

// int	main(int argc, char **argv)
// {
// 	char	**s;
// 	int		i;

// 	i = -1;
// 	if (argc < 2)
// 		return (0);
// 	s = ft_ssplit(argv[1], " ", "'");
// 	while (s[++i])
// 		printf("%s\n", s[i]);
// 	return (0);
// }
