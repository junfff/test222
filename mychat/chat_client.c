#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <mychat.h>

int main(int argc,char *argv[])
{
   //1 获得自己的pid和 name 填充 struct s msg
   //2非阻塞属性创建私有FIFO
   //3打开服务器公共FIFO，把自己的信息向服务器注册
   //4非阻塞读私有FIFO
   //read返回-1 继续轮询
   //read返回>0 协议包解析
   //num为1 聊天信息解析 打印到输出端聊天信息
   //num为2 服务端更新在线列表信息 打印到输出端
   //5设置标准输入为非阻塞属性 读标准输入
   //read 返回-1 继续轮询
   //read 返回>1 字符串解析 填充struct c msg
   //向服务器公共FIFO 写msg
   //6 轮询

   return 0;
}
