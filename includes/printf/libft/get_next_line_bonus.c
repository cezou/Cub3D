/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:36:50 by pmagnero          #+#    #+#             */
/*   Updated: 2024/02/05 09:29:35 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_haseol(const char *str, int checknl)
{
	int	i;

	i = -1;
	if (!str)
		return (0);
	while (str[++i] != 0)
		if (str[i] == '\n' && checknl == 1)
			return (i + 1);
	if (checknl == 0)
		return (i);
	return (0);
}

char	*ft_bufferize(char *sbuff[FD], char *last, t_data *data)
{
	int	len;
	int	nl;

	if (ft_haseol(last, 1))
		data->buff = ft_substr_gnl(last, 0, ft_haseol(last, 1));
	else
		data->buff = ft_substr_gnl(last, 0, ft_haseol(last, 0));
	if (!data->buff)
		return (NULL);
	len = ft_haseol(last, 0);
	nl = ft_haseol(last, 1);
	if (len != nl && nl != 0)
	{
		sbuff[data->fd] = ft_substr_gnl(last, nl, len - nl);
		if (!sbuff[data->fd])
			return (NULL);
	}
	if ((*sbuff && sbuff[data->fd] != NULL
			&& sbuff[data->fd][0] == '\0' && BUFFER_SIZE < 8)
		|| BUFFER_SIZE == 1)
	{
		free(sbuff[data->fd]);
		sbuff[data->fd] = 0;
	}
	return (sbuff[data->fd]);
}

char	*ft_readbuffer(t_list **lst, t_list *node, t_data *data, t_list *tmp)
{
	while (data->rd > 0)
	{
		if (*lst)
			tmp = node;
		if (*lst && tmp)
			data->n = ft_haseol(tmp->str, 0);
		node = ft_lstnew_gnl(BUFFER_SIZE + data->n);
		if (!node)
			return (NULL);
		if (*lst && tmp)
			ft_strcat_gnl((*node).str, tmp->str, ft_haseol((*node).str, 0));
		data->rd = read(data->fd, (*node).str + data->n, BUFFER_SIZE);
		if (data->rd == 0 && tmp && ft_lstdelone_gnl(node, NULL, &free))
			return (tmp->str);
		if (!*lst)
			*lst = node;
		else
		{
			tmp->next = node;
			tmp = (tmp)->next;
		}
		if (ft_haseol((*node).str, 1))
			break ;
	}
	return ((*node).str);
}

char	*ft_read(t_data *data, t_list **lst, long size, t_list *node)
{
	static char	*sbuff[FD] = {NULL};
	char		*last;

	if (sbuff[data->fd] != NULL && sbuff[data->fd][0] != '\0')
	{
		size = ft_haseol(sbuff[data->fd], 0);
		node = ft_lstnew_gnl(size);
		if (!node && ft_lstdelone_gnl(node, sbuff[data->fd], &free))
			return (NULL);
		ft_strcat_gnl((*node).str, sbuff[data->fd], 0);
		*lst = node;
		if (ft_haseol(sbuff[data->fd], 1) > 0)
			size = ft_haseol(sbuff[data->fd], 1);
		free(sbuff[data->fd]);
		sbuff[data->fd] = 0;
	}
	if (*lst && ft_haseol((*lst)->str, 1))
		data->rd = 0;
	last = ft_readbuffer(lst, node, data, NULL);
	if ((!last || !*last || data->rd < 0) && ft_lstclear_gnl(lst, &free)
		&& ft_lstdelone_gnl(NULL, sbuff[data->fd], &free))
		return (NULL);
	return (sbuff[data->fd] = (ft_bufferize(sbuff, last, data)), data->buff);
}

char	*get_next_line(int fd)
{
	t_list	*head;
	char	*res;
	t_list	*node;
	t_data	data;

	data.fd = fd;
	data.n = 0;
	data.rd = 1;
	data.buff = NULL;
	node = NULL;
	head = NULL;
	if (fd >= FD || fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	res = ft_read(&data, &head, 0, node);
	if (head)
		ft_lstclear_gnl(&head, &free);
	return (res);
}
