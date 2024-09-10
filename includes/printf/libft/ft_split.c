/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:12:20 by pmagnero          #+#    #+#             */
/*   Updated: 2024/01/29 12:13:11 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isdelim(char *delim, char c)
{
	int	i;

	i = -1;
	while (delim[++i])
		if (delim[i] == c)
			return (1);
	return (0);
}

static int	ft_count_words(const char *str, char *c)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i] != '\0')
	{
		if ((ft_isdelim(c, str[i + 1]) || str[i + 1] == 0)
			&& !ft_isdelim(c, str[i]))
			count++;
	}
	return (count);
}

static int	ft_assign(const char *str, char **res, int word, char *cs)
{
	int	i;
	int	c;

	i = -1;
	c = 0;
	while (str[++i] != '\0')
	{
		if (ft_isdelim(cs, str[i]) || str[i] == 0)
			c = i + 1;
		if (!ft_isdelim(cs, str[i])
			&& (ft_isdelim(cs, str[i + 1]) || str[i + 1] == 0))
		{
			res[word] = (char *)malloc(sizeof(char) * (i - c + 2));
			if (!res[word])
				return (word);
			ft_strlcpy(res[word], (str + c), i - c + 2);
			word++;
		}
	}
	return (0);
}

char	**ft_split(char const *s, char *c)
{
	char	**res;
	size_t	size;
	size_t	i;
	size_t	word;

	if (!s || !c)
		return (NULL);
	size = ft_count_words(s, c);
	res = (char **)malloc(sizeof(*res) * (size + 1));
	if (!res)
		return (NULL);
	word = ft_assign(s, res, 0, c);
	if (word > 0)
	{
		i = -1;
		while (++i < word)
			free(res[i]);
		free(res);
		return (NULL);
	}
	res[size] = 0;
	return (res);
}
