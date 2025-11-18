# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msobral- <msobral-@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/14 16:16:37 by msobral-          #+#    #+#              #
#    Updated: 2025/11/18 15:50:27 by msobral-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL = /bin/sh

SRCS := \
	test.c \
	get_next_line.c \
	get_next_line_utils.c \
	get_next_line.h

NAME := gnl_test

BS ?= 5

CFLAGS := -Wall -Wextra -Werror

LIST := 1 2 3 4 5 6

all: loop clean

compile:
	cc $(CFLAGS) -D BUFFER_SIZE=$(BS) $(SRCS)

loop:
	clear
	@printf '\e[35;1m-~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~-\e[0m\n';
	@printf '\e[35;1m-~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~-\e[0m\n';
	@for i in $(LIST); do \
		./test.sh $$i 1; \
	done
	@rm -f a.out *ch;

val:
	clear
	@printf '\e[35;1m-~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~-\e[0m\n';
	@printf '\e[35;1m-~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~-\e[0m\n';
	@for i in $(LIST); do \
		./test.sh $$i 2; \
	done
	@rm -f a.out *ch;

xcode:
	clear
	@printf '\e[35;1m-~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~-\e[0m\n';
	@printf '\e[35;1m-~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~-\e[0m\n';
	@for i in $(LIST); do \
		./test.sh $$i 3; \
	done
	@rm -f a.out *ch;

clean:
	@rm -f a.out *ch

.PHONY: all compile val xcode clean

# > /dev/null 2>&1
