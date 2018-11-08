cmake_minimum_required(VERSION 3.12)
project(GameServer)

set(dir_inc  src/include)  #所有头文件放到此处
set(dir_src  ./src)  #所有源文件放到此处
set(dir_obj  ./obj) #所有中间件文件放到此处
set(dir_bin  ./bin) #生成的文件放到此处
set(dir_3rd  ./3party) #第三方库的头文件放到此处
set(dir_lib  ./lib) #第三方库文件的链接库放到此处

set(dir_protobuf  /usr/local/protobuf/include)
set(dir_usrlocal  /usr/local/include)

set(dir_usrlib  /usr/local/lib)
set(dir_protobuflib  /usr/local/protobuf/lib)

set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_FLAGS -pthread)

include_directories(${dir_inc})
include_directories(${dir_protobuf})

set(oracle_include /opt/oracle/instantclient_18_3/sdk/include)
include_directories(oracle_include)
set(PROC_LIBRARY_PATH /opt/oracle/instantclient_18_3)
#link_libraries(${PROC_LIBRARY_PATH})

#link_directories(/usr/lib)
#link_libraries(${dir_protobuflib})
#include_directories(/usr/include)



#include_directories(/usr/include/event2)     src/main/HeartBeat.pb.cc   src/main/person.pb.cc
#include_directories(/usr/local/include)
#link_libraries(hh  -lprotobuf -pthread  -levent -levent_pthreads)

set(
        SOURCE_FILES
        src/Base/MoudlesCollection.cc
        src/main/myevents.cc
        src/main/MarshalEndian.cc
        src/main/wrap.cc
        src/main/BaseMessage.cc
        src/main/threadpool.cc
        src/Business/BusinessMoudle.cc
        src/Business/PersonBusiness.cc
        src/Business/HeartBeatBusiness.cc
        src/main/HeartBeat.pb.cc
        src/main/person.pb.cc
        src/main/register.pb.cc
        src/Business/RegisterBusiness.cpp)



set(SOURCE_FILES src/main/main.cpp ${SOURCE_FILES})

add_executable(GameServer ${SOURCE_FILES})

# 第三方库位置可以通过命令pkg-config --cflags --libs opencv查看
#target_link_libraries(GameServer -I/usr/local/include/opencv -I/usr/local/include
#        -L/usr/local/lib -lopencv_calib3d -lopencv_contrib -lopencv_core -lopencv_features2d
#        -lopencv_flann -lopencv_gpu -lopencv_highgui -lopencv_imgproc -lopencv_legacy
#        -lopencv_ml -lopencv_nonfree -lopencv_objdetect -lopencv_ocl -lopencv_photo
#        -lopencv_stitching -lopencv_superres -lopencv_ts -lopencv_video -lopencv_videostab
#        -lrt -lpthread -lm -ldl)

# 第三方库位置可以通过命令pkg-config --cflags --libs opencv查看

target_link_libraries(GameServer -g -Wall -I${dir_inc} -I${dir_3rd} -pthread -I${dir_protobuf} -L${dir_protobuflib} -L${PROC_LIBRARY_PATH} -luuid -lclntsh -lprotobuf -levent -levent_pthreads -std=c++11)
#target_link_libraries(GameServer -g -Wall -pthread  -levent -levent_pthreads -lprotobuf -std=c++11)
