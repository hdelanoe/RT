# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dguy-caz <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/17 17:20:35 by dguy-caz          #+#    #+#              #
#    Updated: 2017/05/05 01:30:45 by dguy-caz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CFLAGS = -Wall -Wextra -Werror

SRC = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
		ft_memchr.c ft_memcmp.c ft_strlen.c ft_strdup.c ft_strlcat.c \
	  	ft_strcpy.c ft_strncpy.c ft_strcat.c ft_strncat.c ft_strchr.c \
	  	ft_strrchr.c ft_strstr.c ft_strnstr.c ft_strcmp.c ft_strncmp.c \
	  	ft_atoi.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
	  	ft_isprint.c ft_toupper.c ft_tolower.c ft_memalloc.c ft_memdel.c \
		ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c \
		ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c \
		ft_strjoin.c ft_strtrim.c ft_itoa.c ft_putendl.c ft_putendl_fd.c \
		ft_putchar.c ft_putchar_fd.c ft_putstr.c ft_putstr_fd.c ft_putnbr.c \
		ft_putnbr_fd.c ft_strsplit.c ft_lstnew.c ft_lstdelone.c ft_lstdel.c \
		ft_lstadd.c ft_lstiter.c ft_lstmap.c ft_nbwords.c ft_lenwords.c \
		ft_strrev.c ft_range.c ft_strupcase.c ft_strlowcase.c get_next_line.c \
		ft_atod.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@ ar rc $(NAME) $(OBJ)
	@ ranlib $(NAME)

$(OBJ): $(SRC)
	@ gcc -c $(SRC) $(CFLAGS)

clean:
	@ rm -rf $(OBJ)

fclean: clean
	@ rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re
