# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/02 01:11:47 by joesanto          #+#    #+#              #
#    Updated: 2025/11/18 20:30:11 by joesanto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
FLAGS = -Wall -Wextra -Werror -g

NAME = render_fdf_test

INCLUDES = $(addprefix -I, ../../../includes/ ../../../libs/libft ../../../libs/minilibx-linux ../../events ../../parsers)
LIBS = ../../../libs/libft/libft.a ../../../libs/minilibx-linux/libmlx_Linux.a
SRCS = ../../draw/bresenham_drawline.c ../../utils/draw_utils.c ../../draw/xiaolinwu_drawline.c ../render_fdf.c \
../../parsers/parse_fdf_file.c ../../free/free_map.c ../../draw/liangbarsky_clipping.c ../../motions/fdf_motions.c \
../render_voxelspace.c ../../parsers/parse_voxel_file.c ../../physics/gravity.c ../../motions/player_motions.c \
../../events/global_events.c ../../parsers/parse_picture.c ../../loops/app_loop.c ../../events/voxelspace_events.c \
../../utils/events_utils.c ../../events/fdf_events.c ../../physics/player_physics.c ../../free/free_pic.c \
../../utils/render_utils.c ../../parsers/parse_arguments.c ../../inits/init_img.c ../../free/free_img.c ../../inits/init_fdf.c

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
