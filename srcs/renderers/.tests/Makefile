# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/02 01:11:47 by joesanto          #+#    #+#              #
#    Updated: 2025/11/03 23:01:54 by joesanto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
FLAGS = -Wall -Wextra -Werror -g

NAME = bresenham_drawline_test

INCLUDES = $(addprefix -I, ../../../includes/ ../../../libs/libft ../../../libs/minilibx-linux)
LIBS = ../../../libs/libft/libft.a ../../../libs/minilibx-linux/libmlx_Linux.a
SRCS = ../bresenham_drawline.c ../../utils/renderer_utils.c

all: $(NAME)

%_test: %_test.o $(SRCS:.c=.o) $(LIBS)
	$(CC) $^ -lX11 -lXext -o $@

%.o: %.c
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(addsufix .o, $(NAME))

fclean: clean
	rm -f $(NAME)

re: fclean all
