/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:15:23 by pmagnero          #+#    #+#             */
/*   Updated: 2023/12/16 10:50:52 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstprint(t_list **ls, int fd)
{
	t_list	*tmp;

	tmp = *ls;
	while (tmp)
	{
		write(fd, "node: ", 6);
		write(fd, tmp->str, ft_strlen(tmp->str));
		write(fd, "\n", 1);
		if (tmp->next)
		{
			write(fd, "node->next: ", 12);
			write(fd, tmp->next->str, ft_strlen(tmp->next->str));
			write(fd, "\n", 1);
		}
		tmp = tmp->next;
	}
}
