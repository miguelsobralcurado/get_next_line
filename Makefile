# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msobral- <msobral-@student.42lisboa.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/14 16:16:37 by msobral-          #+#    #+#              #
#    Updated: 2025/11/14 23:51:59 by msobral-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL = /bin/sh

SRCS := \
	get_next_line.c \
	get_next_line_utils.c \
	get_next_line.h

NAME := gnl_test

CFLAGS := -Wall -Wextra -Werror

LIST := 1 2 3 4 5

all: loop clean

loop:
	clear
	@echo $$'\\033[35;1m-~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~-\\033[0m';
	@for i in $(LIST); do \
		printf $$'\\033[35;1m-~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~-\\033[0m\n'; \
		printf $$'\\033[36;1mTest >>------> '"$$i"$$':\\033[0m\n'; \
		./spinner.sh & \
		SPIN_PID=$$!; \
		printf $$'\\033[32;1;5m  Please insert the desired BUFFER_SIZE for test '"$$i"$$': \\033[0m'; \
		read BS; \
		kill $SPIN_PID > /dev/null 2>&1; \
		printf $$'\\033[33;1mCompiling with BUFFER_SIZE='"$$BS"$$' ...\\033[0m\n'; \
		gcc $(CFLAGS) -D BUFFER_SIZE=$$BS $(SRCS); \
		printf $$'\\033[34;1mRunning test '"$$i"$$' ...\\033[0m\n'; \
		./a.out tests/test$$i.txt; \
		printf "\n"; \
	done

clean:
	@rm -f a.out

.PHONY: all clean

#
#spinner() {
#    local s='|/-\\'  # Character set for the spinner
#    while true; do
#        for ((i=0; i<${#s}; i++)); do
#            printf "\r\033[33m%s\033[0m" "${s:i:1}"  # Print one character
#            sleep 0.1
#        done
#    done
#}