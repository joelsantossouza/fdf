# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/02 01:11:47 by joesanto          #+#    #+#              #
#    Updated: 2025/11/07 23:00:55 by joesanto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
FLAGS = -Wall -Wextra -Werror -g

NAME = parse_test parse_voxel_test

INCLUDES = $(addprefix -I, ../../../includes/ ../../../libs/libft ../../../libs/minilibx-linux/)
LIBS = ../../../libs/libft/libft.a ../../../libs/minilibx-linux/libmlx.a
SRCS = ../parse_fdf_file.c ../../utils/map_utils.c ../parse_voxel_file.c ../../utils/draw_utils.c

all: $(NAME)

%_test: %_test.o $(SRCS:.c=.o) $(LIBS)
	$(CC) $^ -lX11 -lXext -lm -o $@

%.o: %.c
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(addsufix .o, $(NAME))

fclean: clean
	rm -f $(NAME)

re: fclean all
