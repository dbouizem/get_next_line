# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/17 01:29:02 by dbouizem          #+#    #+#              #
#    Updated: 2025/05/25 16:15:07 by dbouizem         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = gnl_test
CC = gcc
CFLAGS = -Wall -Wextra -Werror -DBUFFER_SIZE=42

SRCS = \
		main.c \
		get_next_line.c \
		get_next_line_utils.c \

OBJS = $(SRCS:.c=.o)

SRCS_BONUS = \
		get_next_line_bonus.c \
		get_next_line_utils_bonus.c \

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

all: $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	@rm -f $(OBJS)

fclean : clean
	@rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re
