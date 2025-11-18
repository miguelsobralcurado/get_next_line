# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test.sh                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msobral- <msobral-@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/17 14:23:23 by msobral-          #+#    #+#              #
#    Updated: 2025/11/17 17:43:36 by msobral-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/sh

i=$1
test_type=$2

if [ $2 -eq 1 ]; then
	printf '\e[36;1mTest >>------> '$i':\e[0m\n';
	sleep 1;
	printf '\e[32;1mPlease insert the desired BUFFER_SIZE for test '$i': \e[0m';
	read BS;
	./spinner.sh & SPIN_PID=$!;
	sleep 0.8;
	printf '\e[33;1mCompiling with BUFFER_SIZE='$BS' ...\e[0m\n';
	sleep 1.2;
	make compile BS=$BS --no-print-directory;
	printf '\e[34;1mRunning test '$i' ...\e[0m'
	sleep 1;
	kill $SPIN_PID > /dev/null 2>&1 & wait $SPIN_PID 2>/dev/null;
	printf "\n";
	if [ $i -eq 6 ]; then
		./a.out;
	else
		./a.out tests/test$i.txt;
	fi;
	printf "\n";
	printf '\e[35;1m-~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~-\e[0m\n';
	if [ $i -lt 6 ]; then
		./spinner.sh & SPIN_PID=$!;
	fi;
	sleep 5;
	if [ $i -lt 6 ]; then
		kill $SPIN_PID > /dev/null 2>&1 & wait $SPIN_PID 2>/dev/null;
	fi;
fi;
if [ $2 -eq 2 ]; then
	printf '\e[36;1mValgrind Test >>------> '$i':\e[0m\n';
	sleep 1;
	printf '\e[32;1mPlease insert the desired BUFFER_SIZE for valgrind test '$i': \e[0m';
	read BS;
	./spinner.sh & SPIN_PID=$!;
	sleep 0.8;
	printf '\e[33;1mCompiling with BUFFER_SIZE='$BS' ...\e[0m\n';
	sleep 1.2;
	make compile BS=$BS --no-print-directory;
	printf '\e[34;1mRunning valgrind full leak check test '$i' ...\e[0m'
	sleep 1;
	kill $SPIN_PID > /dev/null 2>&1 & wait $SPIN_PID 2>/dev/null;
	printf "\n";
	valgrind --leak-check=full --show-leak-kinds=all ./a.out tests/test$i.txt;
	printf "\n";
	printf '\e[35;1m-~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~-\e[0m\n';
	if [ $i -lt 6 ]; then
		./spinner.sh & SPIN_PID=$!;
	fi;
	sleep 5;
	if [ $i -lt 6 ]; then
		kill $SPIN_PID > /dev/null 2>&1 & wait $SPIN_PID 2>/dev/null;
	fi;
fi;
if [ $2 -eq 3 ]; then
	printf '\e[36;1mXcode Leaks Test >>------> '$i':\e[0m\n';
	sleep 1;
	printf '\e[32;1mPlease insert the desired BUFFER_SIZE for leaks test '$i': \e[0m';
	read BS;
	./spinner.sh & SPIN_PID=$!;
	sleep 0.8;
	printf '\e[33;1mCompiling with BUFFER_SIZE='$BS' ...\e[0m\n';
	sleep 1.2;
	make compile BS=$BS --no-print-directory;
	printf '\e[34;1mRunning Xcode at exit leaks test '$i' ...\e[0m'
	sleep 1;
	kill $SPIN_PID > /dev/null 2>&1 & wait $SPIN_PID 2>/dev/null;
	printf "\n";
	leaks --atExit -- ./a.out tests/test$i.txt;
	printf "\n";
	printf '\e[35;1m-~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~--~-\e[0m\n';
	if [ $i -lt 6 ]; then
		./spinner.sh & SPIN_PID=$!;
	fi;
	sleep 5;
	if [ $i -lt 6 ]; then
		kill $SPIN_PID > /dev/null 2>&1 & wait $SPIN_PID 2>/dev/null;
	fi;
fi;
