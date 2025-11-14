# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/02 01:11:47 by joesanto          #+#    #+#              #
#    Updated: 2025/11/14 20:38:22 by joesanto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
FLAGS = -Wall -Wextra -Werror -g

NAME = render_fdf_test render_voxelspace_test physics_test

INCLUDES = $(addprefix -I, ../../../includes/ ../../../libs/libft ../../../libs/minilibx-linux)
LIBS = ../../../libs/libft/libft.a ../../../libs/minilibx-linux/libmlx_Linux.a
SRCS = ../../draw/bresenham_drawline.c ../../utils/draw_utils.c ../../draw/xiaolinwu_drawline.c ../render_fdf.c \
../../parsers/parse_fdf_file.c ../../utils/map_utils.c ../../draw/liangbarsky_clipping.c ../../motions/rotate.c \
../render_voxelspace.c ../../parsers/parse_voxel_file.c ../../physics/gravity.c ../../motions/player_motions.c \
../../utils/events_utils.c ../../parsers/parse_picture.c ../../loops/voxelspace_loops.c

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
