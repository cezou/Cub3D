/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:24:14 by pmagnero          #+#    #+#             */
/*   Updated: 2023/12/16 10:47:52 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	if (!del || !lst || !*lst)
		return (0);
	while (lst && *lst)
	{
		temp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = temp;
	}
	return (1);
}
