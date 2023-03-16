# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/15 15:14:03 by grenaud-          #+#    #+#              #
#    Updated: 2023/03/16 16:41:14 by grenaud-         ###   ########.fr        #
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
					parsing/get_next_line.c 

OBJS			= ${SRCS_LIST:.c=.o}

HEADER			= includes

LIBFT 			= libft
MLX 			= mlx

CC				= gcc
CFLAGS 			= -Wall -Wextra -Werror
LFLAGS			= -L libft -lft

METAL_MLX		= -framework OpenGL -framework AppKit -L./mlx -lmlx 

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
