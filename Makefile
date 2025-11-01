# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/30 15:41:12 by joesanto          #+#    #+#              #
#    Updated: 2025/11/01 15:13:05 by joesanto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

PARSERS = 

CC = cc
FLAGS = -Wall -Wextra -Werror -O3 -g

LIBFT = libft.a
MINILIBX = libmlx_Linux.a
LIBS = $(LIBFT) $(MINILIBX)

all: $(NAME)

$(NAME): $(OBJS) $(LIBS)
	$(CC) $(OBJS) $(LIBS) -o $@

%.o: %.c $(HEADERS)
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):

