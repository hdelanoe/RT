# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdelanoe <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/09 12:06:00 by hdelanoe          #+#    #+#              #
#    Updated: 2017/11/10 19:51:41 by hdelanoe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	libftprintf.a
LIBFT = ../libft/libft.a

SRC =	ft_convert.c \
		ft_count_flag.c \
		ft_printf.c \
		ft_putc.c \
		ft_putd.c \
		ft_putf.c \
		ft_puto.c \
		ft_putp.c \
		ft_putmod.c \
		ft_puts.c \
		ft_putu.c \
		ft_putx.c \
		ft_vfprintf.c \
		../libft/ft_utoa.c \
		../libft/ft_strlen.c \
		../libft/ft_strisnum.c \
		../libft/ft_strdup.c \
		../libft/ft_strdel.c \
		../libft/ft_strcmp.c \
		../libft/ft_size_bin.c \
		../libft/ft_putwchar.c \
		../libft/ft_putstr.c \
		../libft/ft_putchar.c \
		../libft/ft_memset.c \
		../libft/ft_ltoa_base.c \
		../libft/ft_llutoa.c \
		../libft/ft_lltoa.c \
		../libft/ft_lftoa.c \
		../libft/ft_itoa_base.c \
		../libft/ft_itoa.c \
		../libft/ft_isdigit.c \
		../libft/ft_ftoa.c \
		../libft/ft_bzero.c \
		../libft/ft_atoi.c \
		../libft/ft_memalloc.c \
		../libft/ft_strstr.c \
		../libft/ft_strncmp.c \

OBJ = $(SRC:.c=.o)
CC = gcc
FLAGS = -Wall -Wextra -Werror -g -O2
RM = rm -rf
INC = -I includes/
FT = -I ../libft/
LFT = -C ../libft/
CG = \033[92m
CY =  \033[93m
CE = \033[0m

all: $(NAME)
$(NAME): $(OBJ)
	@echo "\033[K$(CY)[PRINTF] :$(CE) $(CG)Creating Library$(CE)\033[1A";
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "\033[K$(CY)[PRINTF] :$(CE) $(CG)PRINTF Compiled!$(CE)";
%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@
	@echo "\033[K$(CY)[PRINTF] :$(CE) $(CG)Compiling $<$(CE) \033[1A";
clean:
	@$(RM) $(OBJ)
fclean: clean
	@$(RM) $(NAME)
	@echo "\033[K$(CY)[PRINTF] :$(CE) $(CG)Cleaning Library$(CE)";
re: fclean all
