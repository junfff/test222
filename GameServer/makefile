#Makefile file  
dir_inc = ./include  #所有头文件放到此处  
dir_src = ./src  #所有源文件放到此处  
dir_obj = ./obj #所有中间件文件放到此处  
dir_bin = ./bin #生成的文件放到此处  
dir_3rd = ./3party #第三方库的头文件放到此处  
dir_lib = ./lib #第三方库文件的链接库放到此处  
dir_protobuf = /usr/local/protobuf/include
dir_protobuflib = /usr/local/protobuf/lib
dir_usrlocal = /usr/local/include
dir_usrlib = /usr/local/lib 

.PHONY : clean all 
src = $(wildcard ./src/*.c, ./src/*.cc)   
src_main = $(wildcard ./*.c, ./*.cpp)   
obj = $(patsubst ./lib/%.o, ./src/%.c , $(src)) 

alltarget = $(wildcard *.c, wildcard *.cpp)  
target = $(patsubst %.cpp, %, $(alltarget)) #生成的文件名  

CC = g++  
protobuf_flags = -I$(dir_protobuf) -L$(dir_protobuflib) -lprotobuf -I$(dir_usrlocal) -I$(dir_usrlib)
CXXFLAGS = -g -Wall -I$(dir_inc) -I$(dir_3rd) -pthread -I$(dir_protobuf) -L$(dir_protobuflib) -lprotobuf -levent -levent_pthreads
LDFLAGS = -L${dir_lib}  
libs= -lopencv_core -lopencv_highgui #链接库模块，使用空格隔开多个文件  

all:$(target)
${target} : ${obj}  
	$(CC) $(obj) $@.cpp -o $@ $(LDFLAGS) $(CXXFLAGS)  
	mv $@ ./bin/$@  
%.o:%.c  
	$(CC) $(CXXFLAGS) -c $< -o $@  
%.o:%.cc  
	$(CC) $(CXXFLAGS) -c $< -o $@  
	.phony:clean  
	clean:  
	find ${dir_obj} -name *.o -exec rm -rf {}\;
