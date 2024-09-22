# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/18 11:28:17 by pmagnero          #+#    #+#              #
#    Updated: 2024/09/20 16:48:38 by pmagnero         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

NAME_BONUS = cub3D_bonus

HEADER = ./includes

HEADER_MINIAUDIO = ./includes/miniaudio

OBJS_DIR	= objs/
OBJS_DIR_B	= objs_b/

FLAG = -Wall -Wextra -Werror -g -O3

MLX_FLAG = -lXext -lX11 -lz -lm -pthread -ldl -lpthread -lXfixes -lasound

OPTION = -I$(HEADER) -I$(HEADER_MINIAUDIO) -I./includes/printf -I./includes/printf/libft -I./includes/mlx_linux/minilibx-linux

LIBFT = includes/printf/libftprintf.a

MINIAUDIO = includes/miniaudio/libminiaudio.a

MLX = includes/mlx_linux/minilibx-linux/libmlx_Linux.a

# debug
d	=	0
# no comment error in norme
c 	=	0

ifeq ($(d),1)
	DEBUG	=	-ggdb
else
    DEBUG	=	
endif

CC	=	cc

VALGRIND_F	=	--leak-check=full --show-leak-kinds=all --track-fds=yes #--show-leak-kinds=all --log-fd=1 --trace-children=yes

NORME	=	srcs/**/*.c includes/*.h includes/printf/*.c includes/printf/*.h includes/printf/**/*.c includes/printf/**/*.h

# ARGS ?= $(shell bash -c 'read -p "ARGS= " args; echo $$args')

# # @$(call disp_title,Norme,$(NORM_COLOR_T))
# ➤  [0;38;5;$(NORM_COLOR)mNorme/g;s/Warning/[38;5;$(NORM_COLOR_WAR)mWarning/g;s/Error/[38;5;$(NORM_COLOR_ERR)mError/g"

COLOR_TITLE	=	36
COLOR_KO	=	31
COLOR_OK	=	32


SRCS =	srcs/cub3D.c \
		srcs/controls/cub3D_hooks.c \
		srcs/controls/cub3D_hooks_utils.c \
		srcs/controls/cub3D_controls.c \
		srcs/controls/cub3D_mouse.c \
		srcs/render/cub3D_render_menus.c \
		srcs/render/cub3D_render.c \
		srcs/render/cub3D_scenes.c \
		srcs/render/cub3D_raycasting.c \
		srcs/render/cub3D_raycasting_sprites.c \
		srcs/render/cub3D_raycasting_dda.c \
		srcs/render/cub3D_raycasting_floor_ceiling.c \
		srcs/render/cub3D_raycasting_skybox.c \
		srcs/menus/cub3D_menus_naviguation.c \
		srcs/utils/cub3D_time.c \
		srcs/utils/cub3D_math.c \
		srcs/utils/cub3D_utils.c \
		srcs/utils/cub3D_utils2.c \
		srcs/utils/cub3D_utils3.c \
		srcs/utils/cub3D_clear.c \
		srcs/init/cub3D_init.c \
		srcs/init/cub3D_init_anim.c \
		srcs/init/cub3D_init_paths.c \
		srcs/init/cub3D_init_sounds.c \
		srcs/init/cub3D_init_window.c \
		srcs/movements/cub3D_movements.c \
		srcs/movements/cub3D_movements2.c \
		srcs/parsing/cub3D_parse.c \
		srcs/parsing/parsing.c \
		srcs/parsing/is_valid_int.c \
		srcs/parsing/utils.c \
		srcs/parsing/ids.c \
		srcs/parsing/ids_utils.c \
		srcs/parsing/clean_and_imgs.c \
		srcs/parsing/map.c \
		srcs/parsing/map_utils.c \
		srcs/parsing/print_utils.c \
		srcs/parsing/map_floodfill.c


# srcs/movements/cub3D_collisions.c
# srcs/cub3D_pathfinding.c 
# srcs/animations/cub3D_animations.c 
# srcs/animations/cub3D_animations2.c 
	
# cub3D_isometric.c
# cub3D_projection_bonus.c \

OBJS			 = $(SRCS:.c=.o)
OBJS_B			 = $(SRCS:.c=.o)
OBJECTS_PREFIXED = $(addprefix $(OBJS_DIR), $(OBJS))
OBJECTS_PREFIXED_B = $(addprefix $(OBJS_DIR_B), $(OBJS_B))

$(OBJS_DIR)%.o : %.c includes/cub3D.h
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)srcs/controls
	@mkdir -p $(OBJS_DIR)srcs/init
	@mkdir -p $(OBJS_DIR)srcs/render
	@mkdir -p $(OBJS_DIR)srcs/menus
	@mkdir -p $(OBJS_DIR)srcs/animations
	@mkdir -p $(OBJS_DIR)srcs/movements
	@mkdir -p $(OBJS_DIR)srcs/utils
	@mkdir -p $(OBJS_DIR)srcs/parsing
ifeq ($(d),1)
	@$(CC) -DDEBUG=1 -DMANDATORY=1 $(DEBUG) $(FLAG) -c $< -o $@
else
	$(CC) -DMANDATORY=1 $(FLAG) -c $< -o $@
endif

$(OBJS_DIR_B)%.o : %.c includes/cub3D.h
	@mkdir -p $(OBJS_DIR_B)
	@mkdir -p $(OBJS_DIR_B)srcs/controls
	@mkdir -p $(OBJS_DIR_B)srcs/init
	@mkdir -p $(OBJS_DIR_B)srcs/render
	@mkdir -p $(OBJS_DIR_B)srcs/menus
	@mkdir -p $(OBJS_DIR_B)srcs/animations
	@mkdir -p $(OBJS_DIR_B)srcs/movements
	@mkdir -p $(OBJS_DIR_B)srcs/parsing
	@mkdir -p $(OBJS_DIR_B)srcs/utils
ifeq ($(d),1)
	@$(CC) -D_POSIX_C_SOURCE=199309L -DDEBUG=1 $(DEBUG) $(FLAG) -c $< -o $@
else
	$(CC) -D_POSIX_C_SOURCE=199309L $(FLAG) -c $< -o $@
endif

#$(ARGS)
# @valgrind $(VALGRIND_F) ./$(NAME) $(ARGS) | grep -aE "total heap usage:|ERROR SUMMARY:" | awk '{if ($$5 == $$7 && NR==1) printf "%s \033[$(COLOR_OK)mOK!\033[0m\n", $$0; else if ($$5 != $$7 && NR==1) printf "%s \033[$(COLOR_KO)mERROR!\033[0m\n", $$0;if ($$4 == 0 && NR==2) printf "%s \033[$(COLOR_OK)mOK!\033[0m\n", $$0; else if ($$4 > 0 && NR==2) printf "%s \033[$(COLOR_KO)mERROR!\033[0m\n", $$0}'
# test:
# 	@echo "\n\033[$(COLOR_TITLE)m########################################"
# 	@echo "################  TESTS  ###############"
# 	@echo "########################################\033[0m\n"
# 	@echo "\n\033[$(COLOR_TITLE)m################  TEST 0 ################\033[0m\n\n"
# 	@cd Leopst && bash basic_test.sh --yes -d && cd .. && rm -rf stderr stdout
# 	@echo "\n\033[$(COLOR_TITLE)m################  TEST 1 ################\033[0m\n\n"
# 	@make --no-print-directory -C push_swap_tester
# 	@./push_swap_tester/complexity 100 100 700 checker_linux ; echo $$? | awk '{if ($$0 == '1') {printf "\n\033[$(COLOR_KO)mERROR!\nHmm, it seems that your algo dont work DUMBASS.\033[0m\n\n"} else {printf "\n\033[$(COLOR_OK)m\nWELL DONE ! let'\''s see the last test.\033[0m\n\n"}}'
# 	@./push_swap_tester/complexity 500 100 5500 checker_linux && echo $$? | awk '{if ($$0 == '1') {printf "\n\033[$(COLOR_KO)mERROR!\nHmm, it seems that your algo dont work DUMBASS.\033[0m\n\n"} else {printf "\n\033[$(COLOR_OK)m\nWELL DONE ! You are good to go.\033[0m\n\n"}}'

$(NAME): $(OBJECTS_PREFIXED)
	@echo "\n\033[$(COLOR_TITLE)m########################################"
	@echo "################  MAKE  ################"
	@echo "########################################\033[0m\n"
ifeq ($(d),1)
	@make --no-print-directory -sC includes/printf
else
	make -C includes/printf
endif
	$(CC) -o $(NAME) $(FLAG) $(OPTION) $(OBJECTS_PREFIXED) $(MINIAUDIO) $(MLX) $(MLX_FLAG) $(LIBFT)

$(NAME_BONUS): $(OBJECTS_PREFIXED_B)
	@echo "\n\033[$(COLOR_TITLE)m########################################"
	@echo "################  MAKE BONUS ################"
	@echo "########################################\033[0m\n"
ifeq ($(d),1)
	@make --no-print-directory -sC includes/printf
else
	make -C includes/printf
endif
	$(CC) -o $(NAME_BONUS) $(FLAG) $(OPTION) $(OBJECTS_PREFIXED_B) -D_POSIX_C_SOURCE=199309L $(MINIAUDIO) $(MLX) $(MLX_FLAG) $(LIBFT)

all: $(NAME)

bonus: $(NAME_BONUS)

kek: $(NAME) norme extfunc valgrind

extfunc:
	@echo "\n\033[$(COLOR_TITLE)m########################################"
	@echo "#########  EXTERNAL FUNCTION  ##########"
	@echo "########################################\033[0m\n"
	@nm -gu $(NAME)
#| awk '!/malloc|exit|free|__|write|memcpy/ {++n;sub(/[ \t]+/, ""); printf "%s", $$0; if ($$0) printf "\t\033[$(COLOR_KO)mERROR!\033[0m\n\n"} END{if (n > 0) {printf "\033[$(COLOR_KO)mYou Fucking DONKEY, what are those forbidden functions !!!\033[0m\n\n";} else {printf "\033[$(COLOR_OK)mOK!, No forbidden functions in use !\033[0m\n\n"}}'

norme:
	@echo "\n\033[$(COLOR_TITLE)m########################################"
	@echo "#############  NORMINETTE  #############"
	@echo "########################################\033[0m\n"
ifeq ($(c), 1)
	@norminette $(NORME) | sed 's,OK!,\x1b[$(COLOR_OK)m&\x1b[0m,;s,Error.*,\x1b[$(COLOR_KO)m&\x1b[0m,' | sed '/WRONG_SCOPE_COMMENT/d'
else
	@norminette $(NORME) | sed 's,OK!,\x1b[$(COLOR_OK)m&\x1b[0m,;s,Error.*,\x1b[$(COLOR_KO)m&\x1b[0m,'
endif

valgrind:
	@echo "\n\033[$(COLOR_TITLE)m########################################"
	@echo "##############  VALGRIND  ##############"
	@echo "########################################\033[0m\n"
	@valgrind $(VALGRIND_F) ./$(NAME) resources/maps/map.ber

clean:
	@echo "\n\033[$(COLOR_TITLE)m########################################"
	@echo "##############  CLEANING  ##############"
	@echo "########################################\033[0m\n"
	@rm -rf $(OBJS_DIR)
	@rm -rf $(OBJS_DIR_B)
ifeq ($(d),1)
	@make --no-print-directory clean -sC includes/printf
else
	make clean -C includes/printf
endif

fclean: clean
	@rm -f $(NAME)
	@rm -f $(NAME_BONUS)
ifeq ($(d),1)
	@make --no-print-directory fclean -sC includes/printf
else
	make fclean -C includes/printf
endif

re: fclean all

.PHONY: all norme extfunc valgrind clean fclean re bonus
