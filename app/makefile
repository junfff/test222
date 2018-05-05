#obj=test.o tools.o
target=mkApp
# makefile中自己维护的变量
# makefile中函数的使用
src=$(wildcard ./*.c)
obj=$(patsubst ./%.c, ./%.o, $(src) )
CC = gcc
CPPFLAGS = -I
$(target):$(obj)
	$(CC) $(obj) -o $(target) -Iinclude -Llib -lMyCale
%.o:%.c
	$(CC) -c $^ -Iinclude -Llib -lMyCale -o $@

.PHONY:clean
clean:
	rm $(obj) $(target) -f
hello:
	echo "helle makefile !!"
