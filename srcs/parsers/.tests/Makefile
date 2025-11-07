# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/02 01:11:47 by joesanto          #+#    #+#              #
#    Updated: 2025/11/07 17:31:37 by joesanto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
FLAGS = -Wall -Wextra -Werror -g

NAME = parse_test

INCLUDES = $(addprefix -I, ../../../includes/ ../../../libs/libft)
LIBS = ../../../libs/libft/libft.a
SRCS = ../parse_fdf_file.c ../../utils/map_utils.c ../parse_voxel_file.c

all: $(NAME)

%_test: %_test.o $(SRCS:.c=.o) $(LIBS)
	$(CC) $^ -lm -o $@

%.o: %.c
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(addsufix .o, $(NAME))

fclean: clean
	rm -f $(NAME)

re: fclean all
