# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msobral- <msobral-@student.42lisboa.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/14 16:16:37 by msobral-          #+#    #+#              #
#    Updated: 2025/11/17 12:51:42 by msobral-         ###   ########.fr        #
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
		kill $$SPIN_PID > /dev/null 2>&1 & \
		wait $$SPIN_PID 2>/dev/null; \
		printf "\n"; \
		./a.out tests/test$$i.txt; \
		printf "\n"; \
		printf '\e[35;1m-~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~-\e[0m\n'; \
		if [ "$$i" < 5 ]; then \
			./spinner.sh & \
			SPIN_PID=$$!; \
		fi; \
		sleep 5; \
		if [ "$$i" < 5 ]; then \
			kill $$SPIN_PID > /dev/null 2>&1; \
			wait $$SPIN_PID 2>/dev/null; \
		fi; \
	done
	@rm -f *ch;

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
		kill $$SPIN_PID > /dev/null 2>&1 & \
		wait $$SPIN_PID 2>/dev/null; \
		printf "\n"; \
		valgrind --leak-check=full --show-leak-kinds=all ./a.out tests/test$$i.txt; \
		printf "\n"; \
		printf '\e[35;1m-~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~-\e[0m\n'; \
		./spinner.sh & \
		SPIN_PID=$$!; \
		sleep 5; \
		kill $$SPIN_PID > /dev/null 2>&1 & \
		wait $$SPIN_PID 2>/dev/null; \
	done
	@rm -f *ch;

xcode:
	clear
	@printf '\e[35;1m-~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~-\e[0m\n';
	@printf '\e[35;1m-~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~-\e[0m\n';
	@for i in $(LIST); do \
		printf '\e[36;1mXcode Leaks Test >>------> '"$$i"':\e[0m\n'; \
		sleep 1; \
		printf '\e[32;1;5mPlease insert the desired BUFFER_SIZE for leaks test '"$$i"': \e[0m'; \
		read BS; \
		./spinner.sh & \
		SPIN_PID=$$!; \
		sleep 0.8; \
		printf '\e[33;1mCompiling with BUFFER_SIZE='"$$BS"' ...\e[0m\n'; \
		sleep 1.2; \
		cc $(CFLAGS) -D BUFFER_SIZE=$$BS $(SRCS); \
		printf '\e[34;1mRunning Xcode at exit leaks test '"$$i"' ...\e[0m'; \
		sleep 1; \
		kill $$SPIN_PID > /dev/null 2>&1 & \
		wait $$SPIN_PID 2>/dev/null; \
		printf "\n"; \
		leaks --atExit -- ./a.out tests/test$$i.txt; \
		printf "\n"; \
		printf '\e[35;1m-~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~-\e[0m\n'; \
		./spinner.sh & \
		SPIN_PID=$$!; \
		sleep 5; \
		kill $$SPIN_PID > /dev/null 2>&1 & \
		wait $$SPIN_PID 2>/dev/null; \
	done
	@rm -f *ch;

clean:
	@rm -f a.out *ch

.PHONY: all val xcode clean

# > /dev/null 2>&1
