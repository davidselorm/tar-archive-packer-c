CC = gcc
CFLAGS = -Wall -Wextra -O2 -std=c99
all:
	$(CC) $(CFLAGS) -o tar_packer tar.c
