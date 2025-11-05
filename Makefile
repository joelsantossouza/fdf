# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/30 15:41:12 by joesanto          #+#    #+#              #
#    Updated: 2025/11/05 17:28:48 by joesanto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

LIBS_DIR = libs
SRCS_DIR = srcs
HEADERS_DIR = includes

UTILS = $(addprefix utils/, map_utils.c draw_utils.c)

PARSERS = $(addprefix parsers/, parse_fdf.c)

DRAW = $(addprefix draw/, bresenham_drawline.c xiaolinwu_drawline.c liangbarsky_clipping.c)

RENDERERS = $(addprefix renderers/, render_fdf.c)

CC = cc
#FLAGS = -Wall -Wextra -Werror -g -O3 -Ofast -march=native -mtune=native -fopenmp -funroll-loops -fprefetch-loop-arrays -flto
FLAGS= -Wall -Wextra -Werror -g

LIBFT = libft/libft.a
MINILIBX = minilibx-linux/libmlx_Linux.a
LIBS = $(addprefix $(LIBS_DIR)/, $(LIBFT) $(MINILIBX))

LINKING = -lm
INCLUDES= $(addprefix -I, $(dir $(LIBS)) includes)
HEADERS = $(addprefix $(HEADERS_DIR)/, fdf.h)
OBJS = $(addprefix $(SRCS_DIR)/, $(PARSERS:.c=.o) $(UTILS:.c=.o) $(RENDERERS:.c=.o) \
$(DRAW:.c=.o))

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
