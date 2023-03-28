# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/15 15:14:03 by grenaud-          #+#    #+#              #
#    Updated: 2023/03/28 15:21:29 by grenaud-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


Y = "\033[33m"
R = "\033[31m"
G = \033[32m
B = "\033[34m"
X = "\033[0m"
UP = "\033[A"
CUT = "\033[K"
REVR = \033[7m
BOLD = "\033[1m"

NAME			= miniRT

SRCS_LIST		= \
					miniRT.c \
					parsing/ft_atod.c \
					parsing/get_next_line.c \
					parsing/list_utils1.c \
					parsing/list_utils2.c \
					parsing/list_utils3.c \
					parsing/dico.c \
					parsing/dico_1.c \
					parsing/dico_2.c \
					parsing/dico_4.c \
					parsing/parsing_fd.c \
					parsing/list_cy.c \

OBJS			= ${SRCS_LIST:.c=.o}

HEADER			= includes

LIBFT 			= libft
MLX 			= mlx

CC				= gcc
CFLAGS 			= -Wall -Wextra -Werror -g
LFLAGS			= -L libft -lft

METAL_MLX		= -framework OpenGL -framework AppKit -L./mlx -lmlx -g -fsanitize=address

RM				= rm -f

all:			$(NAME)

$(NAME):		$(OBJS)
				@echo $(Y)$(BOLD)[Compilation MLX start...]$(BOLD)$(Y)
				@make -s -C $(MLX)
				@echo $(BOLD)[MLX is ready!]$(BOLD)
				@echo $(BOLD)[Compilation libft start...]$(BOLD)
				@make -s -C $(LIBFT)
				@$(CC) $(CFLAGS) $(LFLAGS) $(METAL_MLX) -I $(HEADER) $(OBJS) -o $(NAME)

%.o: %.c
				@$(CC) $(CFLAGS) -I $(HEADER) -o $@ -c $<

clean:
				@$(RM) $(OBJS)
				@make clean -C $(MLX)
				@make clean -C $(LIBFT)

fclean:			clean
				@$(RM) $(NAME)
				@$(RM) libmlx.dylib
				@$(RM) img.bmp
				@make fclean -C $(LIBFT)

re:				fclean all

.PHONY: 		all fclean clean re
