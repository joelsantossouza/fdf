# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/25 12:13:42 by joesanto          #+#    #+#              #
#    Updated: 2025/10/24 22:42:02 by joesanto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TEST=$(patsubst %.c, %, $(SRCS))

SRCS=$(wildcard *_test.c)
OBJS=$(SRCS:.c=.o)
INCLUDES=-I.. -I../ft_printf
CC=cc
FLAGS=-Wall -Wextra -Werror -g
EXTRA=
LIB=ft
LIB_DIR=..

.SECONDARY: $(OBJS) $(LIB_DIR)/lib$(LIB).a

all: $(TEST)

%_test: %_test.o $(LIB_DIR)/lib$(LIB).a
	$(CC) $< -latf-c -L$(LIB_DIR) -l$(LIB) -o $@

%_test.o: %_test.c
	$(CC) $(FLAGS) $(EXTRA) $(INCLUDES) -c $< -o $@

$(LIB_DIR)/lib%.a: $(wildcard $(LIB_DIR)/*.c)
	make bonus -C ..

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(TEST)

re: fclean all

FIND=$(shell find .. -maxdepth 1 -name "*.c" -exec basename {} .c \;)
missing:
	@echo "---> TESTS MISSING <---\n"
	@for file in $(FIND); do \
		if echo "$(SRCS)" | grep -qv "$${file}_test.c"; then \
		echo "> $${file}_test.c"; \
		fi; \
	done
	@echo "\nTotal of Tests: $(words $(TEST))/$(words $(FIND))"

