#Makefile file  
dir_inc = ./include #所有头文件放到此处  
dir_src = ./scr #所有源文件放到此处  
dir_obj = ./obj #所有中间件文件放到此处  
dir_bin = ./bin #生成的文件放到此处  
dir_3rd = ./3party #第三方库的头文件放到此处  
dir_lib = ./lib #第三方库文件的链接库放到此处  
  
.PHONY : clean all 
src = $(wildcard ./src/*.c ./src/*.cpp)    
obj = $(patsubst ./lib/%.o, ./src/%.c , $(src))  
  
alltarget = $(wildcard *.c)  
target = $(patsubst %.c, %, $(alltarget)) #生成的文件名  

bin_target = ${dir_bin}/${target}  
CC = g++  
CXXFLAGS = -g -Wall -I$(dir_inc) -I$(dir_3rd) -pthread -lmysqlclient
LDFLAGS = -L${dir_lib}  
libs= -lopencv_core -lopencv_highgui #链接库模块，使用空格隔开多个文件  
  
all:$(target)
${target} : ${obj}  
	$(CC) $(obj) $@.c -o $@ $(LDFLAGS) $(CXXFLAGS)  
	mv $@ ./bin/$@  
%.o:%.c  
	$(CC) $(CXXFLAGS) -c $< -o $@  
.phony:clean  
clean:  
	find ${dir_obj} -name *.o -exec rm -rf {}\;
