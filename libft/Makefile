# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: grenaud- <grenaud-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/01 15:33:28 by grenaud-          #+#    #+#              #
#    Updated: 2023/04/05 12:25:30 by grenaud-         ###   ########.fr        #
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

SRC_DIR		=	./

SRCS		=	ft_atoi.c\
				ft_bzero.c\
				ft_calloc.c\
				ft_isalnum.c\
				ft_isalpha.c\
				ft_isascii.c\
				ft_isdigit.c\
				ft_isprint.c\
				ft_itoa.c\
				ft_memchr.c\
				ft_memcmp.c\
				ft_memcpy.c\
				ft_memmove.c\
				ft_memset.c\
				ft_putchar_fd.c\
				ft_putendl_fd.c\
				ft_putnbr_fd.c\
				ft_putstr_fd.c\
				ft_split.c\
				ft_strchr.c\
				strchr_gnl.c\
				ft_strdup.c\
				ft_strjoin.c\
				strjoin_gnl.c\
				ft_strlcat.c\
				ft_strlcpy.c\
				ft_strlen.c\
				ft_strmapi.c\
				ft_strncmp.c\
				ft_strnstr.c\
				ft_strrchr.c\
				ft_strtrim.c\
				ft_substr.c\
				ft_tolower.c\
				ft_toupper.c\
				ft_striteri.c\
				ft_lstnew.c\
				ft_lstadd_front.c\
				ft_lstsize.c\
				ft_lstlast.c\
				ft_lstadd_back.c\
				ft_lstdelone.c\
				ft_lstclear.c\
				ft_lstiter.c\
				ft_lstmap.c\
				wr_collector.c\
				ft_putstr.c\

BONUS_SRC	=	ft_lstnew.c\
				ft_lstadd_front.c\
				ft_lstsize.c\
				ft_lstlast.c\
				ft_lstadd_back.c\
				ft_lstdelone.c\
				ft_lstclear.c\
				ft_lstiter.c\
				ft_lstmap.c\

OBJS        =	${SRCS:.c=.o}

BONUS_OBJS	=	${BONUS_SRC:.c=.o}

NAME        = libft.a

CC            = gcc

CFLAGS        = -Wall -Wextra -Werror

AR_RCS        = ar rcs

all:            ${NAME}

.c.o:
				@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}
				@printf "$(G) $(REVR) " $(X)

${NAME}:        ${OBJS}
				@echo $(BOLD)[libft compiled]$(BOLD)
				@${AR_RCS} ${NAME} ${OBJS}

bonus:			${BONUS_OBJS}
				@${AR_RCS} ${NAME} ${BONUS_OBJS}

clean:
				@rm -f ${OBJS} ${BONUS_OBJS}

fclean:			clean
				@rm -f ${NAME}

re:                fclean all

.PHONY:            all clean fclean re bonus