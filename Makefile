# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/15 15:14:03 by grenaud-          #+#    #+#              #
#    Updated: 2023/04/05 16:11:57 by grenaud-         ###   ########.fr        #
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
					parsing/parsing_fd.c \
					parsing/listobj_util.c \
					parsing/fd_data_init.c \
					parsing/check_line.c \
					parsing/msg_error.c \
					parsing/fd_obj_init.c \
					parsing/utils.c \

OBJS			= ${SRCS_LIST:.c=.o}

HEADER			= includes

LIBFT 			= libft
MLX 			= mlx

CC				= gcc
CFLAGS 			= -Wall -Wextra -Werror -g
LFLAGS			= -L libft -lft

METAL_MLX		= -framework OpenGL -framework AppKit -L./mlx -lmlx -g
DANGER			= -fsanitize=address

RM				= rm -f

all:			$(NAME)

$(NAME):		$(OBJS)
				@echo $(BOLD)[MiniRT compiled]$(BOLD)$(X)
				@make -s -C $(MLX)
				@echo $(BOLD)[MLX is ready!]$(BOLD)
				@echo $(BOLD)[Compilation libft start...]$(BOLD)
				@make -s -C $(LIBFT)
				@$(CC) $(CFLAGS) $(LFLAGS) $(METAL_MLX) -I $(HEADER) $(OBJS) -o $(NAME)

danger:			$(OBJS)
				@echo $(R)$(BOLD)[Compiling with fsanitize=address]$(BOLD)$(R)
				@echo $(BOLD)[MiniRT compiled]$(BOLD)$(X)
				@make -s -C $(MLX)
				@echo $(BOLD)[MLX is ready!]$(BOLD)
				@echo $(BOLD)[Compilation libft start...]$(BOLD)
				@make -s -C $(LIBFT)
				@$(CC) $(CFLAGS) $(LFLAGS) $(METAL_MLX) $(DANGER) -I $(HEADER) $(OBJS) -o $(NAME)

%.o: %.c
				@$(CC) $(CFLAGS) -I $(HEADER) -o $@ -c $<
				@printf "$(G) $(REVR) " $(X)

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
