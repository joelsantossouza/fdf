# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/30 15:41:12 by joesanto          #+#    #+#              #
#    Updated: 2025/11/01 17:22:00 by joesanto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

PARSERS = 

OBJS = $(PARSERS:.c=.o)

CC = cc
FLAGS = -Wall -Wextra -Werror -O3 -g

LIBFT = libft.a
MINILIBX = libmlx_Linux.a
LIBS_DIR = libs
LIBS = $(addprefix $(LIBS_DIR)/, $(LIBFT) $(MINILIBX))

all: $(NAME)

$(NAME): $(OBJS) $(LIBS)
	$(CC) $(OBJS) $(LIBS) -o $@

%.o: %.c $(HEADERS)
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

%$(LIBFT):
	if [ ! -d "$(dir $@)" ]; then \
		git clone git@github.com:joelsantossouza/libft.git $(dir $@); \
	fi
	make -C $(dir $@)

%$(MINILIBX):
	if [ ! -d "$(dir $@)" ]; then \
		git clone git@github.com:42paris/minilibx-linux.git $(dir $@); \
	fi
	make -C $(dir $@)
