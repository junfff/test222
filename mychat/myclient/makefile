
target=myclient

src=$(wildcard ./src/*.c) main.c
obj=$(patsubst ./lib/%.o, ./src/%.c, $(src))
CC = gcc
CPPFLAGS = -I

$(target):$(obj)
	$(CC) $(obj) -o $(target) -Iinclude -g -lm

%.o:%.c
	$(CC) -c $< -o $@ -Iinclude
  
