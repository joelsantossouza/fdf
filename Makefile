# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/30 15:41:12 by joesanto          #+#    #+#              #
#    Updated: 2025/11/19 15:10:48 by joesanto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

LIBS_DIR = libs
SRCS_DIR = srcs
HEADERS_DIR = includes

UTILS_DIR = $(SRCS_DIR)/utils
UTILS = $(addprefix $(UTILS_DIR)/, events_utils.c draw_utils.c)

INITS_DIR = $(SRCS_DIR)/inits
INITS = $(addprefix $(INITS_DIR)/, init_app.c init_fdf.c init_img.c init_player.c)

FREE_DIR = $(SRCS_DIR)/free
FREE = $(addprefix $(FREE_DIR)/, free_app.c free_img.c free_map.c free_pic.c)

PARSERS_DIR = $(SRCS_DIR)/parsers
PARSERS = $(addprefix $(PARSERS_DIR)/, parse_fdf_file.c parse_voxel_file.c parse_picture.c \
		  parse_arguments.c)

DRAW_DIR = $(SRCS_DIR)/draw
DRAW = $(addprefix $(DRAW_DIR)/, bresenham_drawline.c xiaolinwu_drawline.c liangbarsky_clipping.c)

MOTIONS_DIR = $(SRCS_DIR)/motions
MOTIONS = $(addprefix $(MOTIONS_DIR)/, fdf_motions.c voxelspace_motions.c)

PHYSICS_DIR = $(SRCS_DIR)/physics
PHYSICS = $(addprefix $(PHYSICS_DIR)/, gravity.c voxelspace_physics.c)

EVENTS_DIR = $(SRCS_DIR)/events
EVENTS = $(addprefix $(EVENTS_DIR)/, global_events.c fdf_events.c voxelspace_events.c)

RENDERERS_DIR = $(SRCS_DIR)/renderers
RENDERERS = $(addprefix $(RENDERERS_DIR)/, render_fdf.c render_voxelspace.c)

LOOPS_DIR = $(SRCS_DIR)/loops
LOOPS = $(addprefix $(LOOPS_DIR)/, app_loop.c)

MAIN_DIR = $(SRCS_DIR)
MAIN = $(addprefix $(MAIN_DIR)/, main.c)

CC = cc
#FLAGS = -Wall -Wextra -Werror -g -O3 -Ofast -march=native -mtune=native -fopenmp -funroll-loops
FLAGS= -Wall -Wextra -Werror -g

LIBFT = libft/libft.a
MINILIBX = minilibx-linux/libmlx_Linux.a
LIBS = $(addprefix $(LIBS_DIR)/, $(LIBFT) $(MINILIBX))

HEADERS = $(addprefix $(HEADERS_DIR)/, fdf.h voxelspace.h stb_image.h) $(INITS_DIR)/inits.h \
		  $(EVENTS_DIR)/events.h $(PARSERS_DIR)/parsers.h
LINKING = -lm -lXext -lX11
INCLUDES= $(addprefix -I, $(dir $(LIBS)) $(HEADERS_DIR) $(EVENTS_DIR) $(PARSERS_DIR))
OBJS = $(UTILS:.c=.o) $(INITS:.c=.o) $(FREE:.c=.o) $(PARSERS:.c=.o) $(DRAW:.c=.o) \
	$(MOTIONS:.c=.o) $(PHYSICS:.c=.o) $(EVENTS:.c=.o) $(RENDERERS:.c=.o) $(LOOPS:.c=.o) \
	$(MAIN:.c=.o)

all: $(NAME)

$(NAME): $(LIBS) $(OBJS)
	$(CC) $(OBJS) $(LIBS) $(LINKING) -o $@

%.o: %.c $(HEADERS)
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

%$(LIBFT):
	@if [ ! -d "$(dir $@)" ]; then \
		git clone git@github.com:joelsantossouza/libft.git $(dir $@); \
	fi
	make -C $(dir $@)

%$(MINILIBX):
	@if [ ! -d "$(dir $@)" ]; then \
		git clone git@github.com:42paris/minilibx-linux.git $(dir $@); \
	fi
	make -C $(dir $@)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -rf $(LIBS_DIR)
	rm -f $(NAME)

re: fclean all
