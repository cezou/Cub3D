/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:37:21 by pmagnero          #+#    #+#             */
/*   Updated: 2024/02/05 09:29:41 by pmagnero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <sys/types.h>
/*TO REMOVE */
# include <stdio.h>

# define FD 512

typedef struct s_list
{
	char			*str;
	struct s_list	*next;
}	t_list;

typedef struct s_data
{
	int		rd;
	int		n;
	int		fd;
	char	*buff;
}	t_data;

char	*get_next_line(int fd);
char	*ft_read(t_data *data, t_list **lst, long size, t_list *node);
char	*ft_readbuffer(t_list **lst, t_list *node, t_data *data, t_list *tmp);
char	*ft_bufferize(char *sbuff[FD], char *buff, t_data *data);
t_list	*ft_lstnew_gnl(int size);
int		ft_lstdelone_gnl(t_list *lst, char *sbuff, void (*del)(void*));
int		ft_lstclear_gnl(t_list **lst, void (*del)(void*));
size_t	ft_strcat_gnl(char *dst, const char *src, size_t size);
size_t	ft_haseol(const char *str, int checknl);
char	*ft_substr_gnl(char const *s, unsigned int start, size_t len);

#endif
