# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dguy-caz <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/17 16:13:57 by dguy-caz          #+#    #+#              #
#    Updated: 2017/12/12 19:59:04 by hdelanoe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= 	rt
LIBFT 		= 	libft/libft.a
PRINTF 		= 	ft_printf/libftprintf.a
MLX			= 	minilibx_macos/libmlx.a

SRCS		= 	srcs/main.c \
				srcs/ray_tracer.c \
				srcs/texture.c \
				srcs/cast_ray.c \
				srcs/basic_intersection.c \
				srcs/check_intersection.c \
				srcs/solution.c \
				srcs/torus.c \
				srcs/triangle.c \
				srcs/quad.c \
				srcs/errors.c \
				srcs/perlin_noise.c \
				srcs/ft_remove_if.c \
				srcs/interactions/user_interactions.c \
				srcs/interactions/mouse.c \
				srcs/interactions/inputs.c \
				srcs/interactions/interface.c \
				srcs/interactions/copy_delete.c \
				srcs/render/anti_aliasing.c \
				srcs/render/pixelization.c \
				srcs/render/filter.c \
				srcs/matrix/camera.c \
				srcs/matrix/matrix_rotation.c \
				srcs/matrix/matrix_translation.c \
				srcs/parsing/parsing.c \
				srcs/parsing/parse_material.c \
				srcs/parsing/parsing_tools.c \
				srcs/parsing/get_parsing.c \
				srcs/parsing/create_object.c \
				srcs/parsing/create_light.c \
				srcs/color/colors.c \
				srcs/color/cel_shading.c \
				srcs/color/colors_op1.c \
				srcs/color/colors_op2.c \
				srcs/vector/vectors_op1.c \
				srcs/vector/vectors_op2.c \
				srcs/vector/vectors_op3.c \
				srcs/render/multithread.c \

OBJS		= 	$(patsubst srcs/%.c,objs/%.o,$(SRCS))

CC			= 	gcc
CFLAGS		= 	-Wall -Wextra -Werror
INC			= 	-I./includes/

LIBFTINC	= 	-I./libft/includes/
LIBFTLINK	= 	-L./libft -lft

MLXINC		= 	-I./minilibx_macos/
MLXLINK		= 	-L./minilibx_macos -framework OpenGL -framework AppKit -Iminilibx_macos

all:		$(NAME)

$(NAME):	$(OBJS)
			@ make -C ./libft all
			@ make -C ./ft_printf all
			@ $(CC) $(CFLAGS) $(LIBFT) $(PRINTF) $(MLX) $(LIBFTLINK) $(MLXLINK) -o $@ $^
			@ echo "\n\033[1;33m---> Libft created\033[0m \033[92m✓\033[0m"
			@ echo "\n\033[92m---> RTv1 program created ✓\033[0m"

objs/%.o: 	srcs/%.c
			@ mkdir -p objs
			@ mkdir -p objs/parsing
			@ mkdir -p objs/color
			@ mkdir -p objs/vector
			@ mkdir -p objs/matrix
			@ mkdir -p objs/render
			@ mkdir -p objs/interactions
		 	@ $(CC) $(CFLAGS) $(INC) $(LIBFTINC) $(MLXINC) -c $< -o $@

clean:		
			@ /bin/rm -rf objs/
			@ make -C libft/ clean
			@ make -C ./ft_printf clean
			@ echo "\033[1;33m---> All .o files cleared\033[0m \033[92m✓\033[0m"

fclean:		clean
			@ /bin/rm -f $(NAME)
			@ make -C libft/ fclean
			@ make -C ./ft_printf fclean
			@ echo "\n\033[1;33m---> Everything cleared\033[2;00m \033[92m✓\033[0m"
re : fclean all

.PHONY: clean, fclean, re
