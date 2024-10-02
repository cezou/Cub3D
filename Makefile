# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pmagnero <pmagnero@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/18 11:28:17 by pmagnero          #+#    #+#              #
#    Updated: 2024/10/02 21:40:10 by pmagnero         ###   ########.fr        #
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

b	=	0

ifeq ($(d),1)
	DEBUG	=	-ggdb
	PG		=	-pg
else
    DEBUG	=	
    PG		=	
endif

ifdef WSL_DISTRO_NAME
	WSL		=	-DWSL=1
else
	WSL		=	
endif

CC	=	cc

VALGRIND_F	=	--leak-check=full --show-leak-kinds=all --trace-children=yes --track-fds=yes --suppressions=ignore.txt#--show-leak-kinds=all --log-fd=1 --trace-children=yes

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
		srcs/render/cub3D_render_player.c \
		srcs/render/cub3D_render.c \
		srcs/render/cub3D_scenes.c \
		srcs/render/cub3D_raycasting.c \
		srcs/render/cub3D_raycasting_sprites.c \
		srcs/render/cub3D_raycasting_sprites_utils.c \
		srcs/render/cub3D_raycasting_dda.c \
		srcs/render/cub3D_raycasting_dda_utils.c \
		srcs/render/cub3D_raycasting_floor_ceiling.c \
		srcs/render/cub3D_raycasting_skybox.c \
		srcs/render/cub3D_animations.c \
		srcs/render/cub3D_hud.c \
		srcs/menus/cub3D_menus_naviguation.c \
		srcs/utils/cub3D_time.c \
		srcs/utils/cub3D_math.c \
		srcs/utils/cub3D_utils.c \
		srcs/utils/cub3D_utils2.c \
		srcs/utils/cub3D_utils3.c \
		srcs/utils/cub3D_clear.c \
		srcs/utils/cub3D_random.c \
		srcs/init/cub3D_init.c \
		srcs/init/cub3D_init_player.c \
		srcs/init/cub3D_init_anim.c \
		srcs/init/cub3D_init_paths.c \
		srcs/init/cub3D_init_sounds.c \
		srcs/init/cub3D_init_window.c \
		srcs/movements/cub3D_movements.c \
		srcs/movements/cub3D_movements2.c \
		srcs/movements/key_management.c \
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
	@$(CC) -DDEBUG=1 -DMANDATORY=1 $(DEBUG) $(WSL) $(PG) $(FLAG) -c $< -o $@
else
	$(CC) -DMANDATORY=1 $(FLAG) $(WSL) -c $< -o $@
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
	@$(CC) -D_POSIX_C_SOURCE=199309L -DDEBUG=1 $(DEBUG) $(WSL) $(PG) $(FLAG) -c $< -o $@
else
	$(CC) -D_POSIX_C_SOURCE=199309L $(FLAG) $(WSL) -c $< -o $@
endif

$(NAME): $(OBJECTS_PREFIXED)
	@echo "\n\033[$(COLOR_TITLE)m########################################"
	@echo "################  MAKE  ################"
	@echo "########################################\033[0m\n"
ifdef WSL_DISTRO_NAME
	@echo "WSL DETECTED"
	@echo "Adding the DISPLAY variable to the environment to use Xming"
	@export DISPLAY=$(cat /etc/resolv.conf | grep nameserver | awk '{print $2}'):0.0
endif
ifeq ($(d),1)
	@make --no-print-directory -sC includes/printf
else
	make -C includes/printf
endif
	$(CC) -o $(NAME) $(FLAG) $(OPTION) $(OBJECTS_PREFIXED) $(MINIAUDIO) $(MLX) $(MLX_FLAG) $(LIBFT)

$(NAME_BONUS): $(OBJECTS_PREFIXED_B)
	@echo "\n\033[$(COLOR_TITLE)m########################################"
	@echo "############ MAKE BONUS ################"
	@echo "########################################\033[0m\n"
ifdef WSL_DISTRO_NAME
	@echo "WSL DETECTED"
	@echo "Adding the DISPLAY variable to the environment to use Xming"
	@export DISPLAY=$(cat /etc/resolv.conf | grep nameserver | awk '{print $2}'):0.0
endif
ifeq ($(d),1)
	@make --no-print-directory -sC includes/printf
else
	make -C includes/printf
endif
	$(CC) -o $(NAME_BONUS) $(FLAG) $(OPTION) $(OBJECTS_PREFIXED_B) -D_POSIX_C_SOURCE=199309L $(MINIAUDIO) $(MLX) $(MLX_FLAG) $(LIBFT)

all: $(NAME)

bonus: $(NAME_BONUS)

ifeq ($(b), 0)
kek: $(NAME) norme extfunc valgrind
else
kek: $(NAME_BONUS) norme extfunc valgrind
endif

extfunc:
	@echo "\n\033[$(COLOR_TITLE)m########################################"
	@echo "#########  EXTERNAL FUNCTION  ##########"
	@echo "########################################\033[0m\n"
ifeq ($(b), 0)
	@nm -gu $(NAME_BONUS) | awk '!/malloc|exit|free|__|write|memcpy|X|pthread/ {++n;sub(/[ \t]+/, ""); printf "%s", $$0; if ($$0) printf "\t\033[$(COLOR_KO)mERROR!\033[0m\n\n"} END{if (n > 0) {printf "\033[$(COLOR_KO)mYou Fucking DONKEY, what are those forbidden functions !!!\033[0m\n\n";} else {printf "\033[$(COLOR_OK)mOK!, No forbidden functions in use !\033[0m\n\n"}}'
else
	@nm -gu $(NAME) | awk '!/malloc|exit|free|__|write|memcpy|X|pthread/ {++n;sub(/[ \t]+/, ""); printf "%s", $$0; if ($$0) printf "\t\033[$(COLOR_KO)mERROR!\033[0m\n\n"} END{if (n > 0) {printf "\033[$(COLOR_KO)mYou Fucking DONKEY, what are those forbidden functions !!!\033[0m\n\n";} else {printf "\033[$(COLOR_OK)mOK!, No forbidden functions in use !\033[0m\n\n"}}'
endif
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
ifeq ($(b), 0)
	@valgrind $(VALGRIND_F) --log-file=valgrind.log ./$(NAME) resources/maps/test.cub 800 600
else
	@valgrind $(VALGRIND_F) --log-file=valgrind_bonus.log ./$(NAME_BONUS) resources/maps/subject.cub 800 600
endif

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
