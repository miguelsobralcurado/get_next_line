#!/bin/sh
# --------------------------------------------------------------
# Rotating spinner – works with any POSIX‑sh (dash, ash, …)
# --------------------------------------------------------------
# Define the spinner function using sh-compatible syntax
while :; do
	printf '\r\e[33m|\e[0m'   # |
	sleep 0.1
	printf '\r\e[33m/\e[0m'   # /
	sleep 0.1
	printf '\r\e[33m-\e[0m'   # -
	sleep 0.1
	printf '\r\e[33m\\\e[0m'  # \ (double backslash)
	sleep 0.1
done