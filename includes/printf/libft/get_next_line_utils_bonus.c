/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:37:15 by pmagnero          #+#    #+#             */
/*   Updated: 2024/02/05 09:29:47 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_list	*ft_lstnew_gnl(int size)
{
	t_list	*ls;
	size_t	i;
	char	*dst;

	ls = (t_list *)malloc(sizeof(t_list));
	if (!ls)
		return (NULL);
	ls->str = (void *)malloc(sizeof (char) * (size + 1));
	if (!ls->str)
	{
		free(ls);
		return (NULL);
	}
	if (ls->str)
	{
		dst = ls->str;
		i = -1;
		while (++i < (sizeof (char) * (size)))
			dst[i] = '\0';
	}
	ls->str[size] = 0;
	ls->next = NULL;
	return (ls);
}

int	ft_lstdelone_gnl(t_list *lst, char *sbuff, void (*del)(void*))
{
	if (!del)
		return (1);
	if (lst)
	{
		(*del)(lst->str);
		free(lst);
	}
	if (sbuff)
		free(sbuff);
	return (1);
}

int	ft_lstclear_gnl(t_list **lst, void (*del)(void*))
{
	t_list	*temp;

	if (!del || !lst || !*lst)
		return (1);
	while (lst && *lst)
	{
		temp = (*lst)->next;
		ft_lstdelone_gnl(*lst, NULL, del);
		*lst = temp;
	}
	return (1);
}

char	*ft_substr_gnl(char const *s, unsigned int start, size_t len)
{
	char			*sub;
	unsigned int	i;
	size_t			slen;

	if (!s)
		return (NULL);
	i = 0;
	slen = len;
	while (s[start + i] != 0 && len-- > 0)
		i++;
	sub = (char *)malloc(sizeof(char) * (i + 1));
	if (!sub)
		return (NULL);
	*sub = 0;
	s = s + start;
	i = 0;
	while (*s != 0 && slen-- > 0)
		sub[i++] = *s++;
	sub[i] = 0;
	return (sub);
}

size_t	ft_strcat_gnl(char *dst, const char *src, size_t size)
{
	while (*src != '\0')
	{
		dst[size] = *src;
		size++;
		src++;
	}
	dst[size] = '\0';
	return (0);
}
