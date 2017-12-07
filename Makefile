# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dguy-caz <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/17 16:13:57 by dguy-caz          #+#    #+#              #
#    Updated: 2017/06/17 19:49:33 by dguy-caz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= 	rtv1

SRCS		= 	srcs/main.c \
				srcs/rtv1.c \
				srcs/vectors_op1.c \
				srcs/vectors_op2.c \
				srcs/vectors_op3.c \
				srcs/user_interactions.c \
				srcs/colors.c \
				srcs/intersections.c \
				srcs/light_blocked.c \
				srcs/parsing.c \
				srcs/sphere.c \
				srcs/cone.c \
				srcs/cylinder.c \
				srcs/plane.c \
				srcs/light.c \
				srcs/torus.c \
				srcs/math_tools.c \
				srcs/parsing_tools.c \

OBJS		= 	$(patsubst srcs/%.c,objs/%.o,$(SRCS))

CC			= 	gcc
CFLAGS		= 	-Wall -Wextra -Werror
INC			= 	-I./includes/

LIBFT		= 	./libft/libft.a
LIBFTINC	= 	-I./libft/includes/
LIBFTLINK	= 	-L./libft -lft

MLX			= 	./minilibx_macos/libmlx.a
MLXINC		= 	-I./minilibx_macos/
MLXLINK		= 	-L./minilibx_macos -framework OpenGL -framework AppKit -Iminilibx_macos

.SILENT:

all:		$(NAME)

$(NAME): 	$(OBJS)
			make -C ./libft
			make -C ./minilibx_macos
			$(CC) $(CFLAGS) $(INC) $(LIBFT) $(LIBFTLINK) $(MLXLINK) $(MLX) -o $@ $^
			echo "\033[92m\n---> RTv1 program created ✓\n\033[0m"

objs/%.o: 	srcs/%.c
			mkdir -p objs
		 	$(CC) $(CFLAGS) $(INC) $(LIBFTINC) $(MLXINC) -c $< -o $@

clean:		
			/bin/rm -rf objs/
			make -C libft/ clean
			make -C minilibx_macos/ clean
			echo "\033[1;33m\n---> All .o files cleared\033[0m \033[92m✓\n\033[0m"

fclean:		clean
			/bin/rm -f $(NAME)
			make -C libft/ fclean
			echo "\033[1;33m---> Everything cleared\033[2;00m \033[92m✓\n\033[0m"

re : fclean all

.PHONY: all, clean, fclean, re
