# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/30 15:41:12 by joesanto          #+#    #+#              #
#    Updated: 2025/11/01 20:44:42 by joesanto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

LIBS_DIR = libs
SRCS_DIR = srcs

PARSERS = $(addprefix parsers/, parse_fdf.c)

OBJS = $(addprefix $(SRCS_DIR)/, $(PARSERS:.c=.o))

CC = cc
FLAGS = -Wall -Wextra -Werror -O3 -g

LIBFT = libft/libft.a
MINILIBX = minilibx-linux/libmlx_Linux.a
LIBS = $(addprefix $(LIBS_DIR)/, $(LIBFT) $(MINILIBX))
INCLUDES=$(addprefix -I, $(dir $(LIBS)))

all: $(NAME)

$(NAME): $(LIBS) $(OBJS)
	$(CC) $(OBJS) $(LIBS) -o $@

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
