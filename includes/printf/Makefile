# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pmagnero <pmagnero@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/18 11:28:17 by pmagnero          #+#    #+#              #
#    Updated: 2023/11/20 10:42:07 by pmagnero         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

HEADER = .

FLAG = -Wall -Wextra -Werror -g

OPTION =  -I ./libft -I $(HEADER)

SRC =	ft_printf.c \
		ft_printstr.c \
		ft_printptr.c \
		ft_printux.c \
		ft_printutils.c\
		get_next_line.c \
		get_next_line_utils.c \

OBJ = $(SRC:.c=.o)

.c.o:
	cc $(FLAG) $(OPTION) -c $< -o ${<:.c=.o}

all: $(NAME)

$(NAME): 	$(OBJ)
	@make -C libft
	@cp libft/libft.a .
	@mv libft.a $(NAME)
	ar rcs $(NAME) $(OBJ)

clean:
	/bin/rm -f $(OBJ)
	@make clean -C libft

fclean: clean
	/bin/rm -f $(NAME)
	/bin/rm -f libft/libft.a

re: fclean all

bonus:	all

.PHONY: all clean fclean re bonus
