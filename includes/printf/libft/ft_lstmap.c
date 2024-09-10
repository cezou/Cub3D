/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:24:56 by pmagnero          #+#    #+#             */
/*   Updated: 2024/02/05 09:29:19 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*temp;
	t_list	*beg;

	if (!lst || !f || !del)
		return (NULL);
	beg = NULL;
	while (lst)
	{
		temp = ft_lstnew((*f)(lst->str));
		if (!temp)
		{
			while (beg)
			{
				temp = beg->next;
				(*del)(beg->str);
				free(beg);
				beg = temp;
			}
			lst = NULL;
			return (NULL);
		}
		ft_lstadd_back(&beg, temp);
		lst = lst->next;
	}
	return (beg);
}
