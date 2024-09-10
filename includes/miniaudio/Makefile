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

NAME = libminiaudio.a

HEADER = .

FLAG = -fPIE

OPTION =  -I $(HEADER)

SRC =	miniaudio.c

OBJ = $(SRC:.c=.o)

.c.o:
	cc $(FLAG) $(OPTION) -c $< -o ${<:.c=.o}

all: $(NAME)

$(NAME): 	$(OBJ)
	ar rcs $(NAME) $(OBJ)

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

bonus:	all

.PHONY: all clean fclean re bonus
