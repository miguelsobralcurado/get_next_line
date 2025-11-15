# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msobral- <msobral-@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/14 16:16:37 by msobral-          #+#    #+#              #
#    Updated: 2025/11/15 12:48:35 by msobral-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL = /bin/sh

SRCS := \
	test.c \
	get_next_line.c \
	get_next_line_utils.c \
	get_next_line.h

NAME := gnl_test

CFLAGS := -Wall -Wextra -Werror

LIST := 1 2 3 4 5

all: loop clean

loop:
	clear
	@printf '\e[35;1m-~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~-\e[0m\n';
	@printf '\e[35;1m-~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~-\e[0m\n';
	@for i in $(LIST); do \
		printf '\e[36;1mTest >>------> '"$$i"':\e[0m\n'; \
		sleep 1; \
		printf '\e[32;1;5mPlease insert the desired BUFFER_SIZE for test '"$$i"': \e[0m'; \
		read BS; \
		./spinner.sh & \
		SPIN_PID=$$!; \
		sleep 0.8; \
		printf '\e[33;1mCompiling with BUFFER_SIZE='"$$BS"' ...\e[0m\n'; \
		sleep 1.2; \
		cc $(CFLAGS) -D BUFFER_SIZE=$$BS $(SRCS); \
		printf '\e[34;1mRunning test '"$$i"' ...\e[0m'; \
		sleep 1; \
		kill $$SPIN_PID; \
		printf "\n"; \
		./a.out tests/test$$i.txt; \
		printf "\n"; \
		printf '\e[35;1m-~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~-\e[0m\n'; \
		./spinner.sh & \
		SPIN_PID=$$!; \
		sleep 5; \
		kill $$SPIN_PID; \
	done

val:
	clear
	@printf '\e[35;1m-~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~-\e[0m\n';
	@printf '\e[35;1m-~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~-\e[0m\n';
	@for i in $(LIST); do \
		printf '\e[36;1mValgrind Test >>------> '"$$i"':\e[0m\n'; \
		sleep 1; \
		printf '\e[32;1;5mPlease insert the desired BUFFER_SIZE for valgrind test '"$$i"': \e[0m'; \
		read BS; \
		./spinner.sh & \
		SPIN_PID=$$!; \
		sleep 0.8; \
		printf '\e[33;1mCompiling with BUFFER_SIZE='"$$BS"' ...\e[0m\n'; \
		sleep 1.2; \
		cc $(CFLAGS) -D BUFFER_SIZE=$$BS $(SRCS); \
		printf '\e[34;1mRunning valgrind full leak check test '"$$i"' ...\e[0m'; \
		sleep 1; \
		kill $$SPIN_PID; \
		printf "\n"; \
		valgrind --leak-check=full --show-leak-kinds=all ./a.out tests/test$$i.txt; \
		printf "\n"; \
		printf '\e[35;1m-~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~-\e[0m\n'; \
		./spinner.sh & \
		SPIN_PID=$$!; \
		sleep 5; \
		kill $$SPIN_PID; \
	done

clean:
	@rm -f a.out get_next_line.h.gch

.PHONY: all val clean

# > /dev/null 2>&1


#spinner() {
#    local s='|/-\\'  # Character set for the spinner
#    while true; do
#        for ((i=0; i<${#s}; i++)); do
#            printf "\r\033[33m%s\033[0m" "${s:i:1}"  # Print one character
#            sleep 0.1
#        done
#    done
#}