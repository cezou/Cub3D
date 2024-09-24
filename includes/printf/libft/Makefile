# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/18 11:28:17 by pmagnero          #+#    #+#              #
#    Updated: 2024/03/04 14:41:17 by pmagnero         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

HEADER = .

FLAG = -Wall -Wextra -Werror

OPTION = -I $(HEADER)

SRC =	ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_strlen.c \
		ft_strlcat.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_strncmp.c \
		ft_atoi.c \
		ft_strdup.c \
		ft_bzero.c \
		ft_memset.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_strlcpy.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strnstr.c \
		ft_calloc.c \
		ft_substr.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_split.c \
		ft_ssplit.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_abs.c \
		ft_atol.c \
		ft_isspace.c \
		ft_lstprint.c \
		ft_minmax.c \
		ft_strtolower.c \
		ft_getfirstquote.c \
		ft_swap.c \
		ft_atof.c \
		ft_atod.c \
		ft_atold.c \

BSOURCES = \
	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
	ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJ = $(SRC:.c=.o)
BOBJECTS = $(BSOURCES:.c=.o)

.c.o:
	cc $(FLAG) $(OPTION) -c $< -o ${<:.c=.o}

all: $(NAME) bonus

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

bonus: $(OBJ) $(BOBJECTS)
	ar rcs $(NAME) $(OBJ) $(BOBJECTS)

clean:
	/bin/rm -f $(OBJ) $(BOBJECTS)
	/bin/rm -f *.gch

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
