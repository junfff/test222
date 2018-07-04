/*================================================================
 *   Copyright (C) 2018 LiuJunFeng Ltd. All rights reserved.
 *   
 *   文件名称：server.cpp
 *   创 建 者：LiuJunFeng
 *   创建日期：2018年07月03日 10:46(Tuesday) 
 *   描    述：
 *
 ================================================================*/

#include <event.h>
//#include <event2/event.h>
//#include <event2/event_compat.h>

struct time_hand
{
	struct event ev;
	struct timeval tv;
};
void timer_cb(int fd, short event, void *arg)
{
	time_hand *th = (time_hand *)arg;
	printf("timer wakeup!!\n");

	//event_base_got_exit(th->ev.ev_base);
    event_add(&th->ev, &th->tv); // reschedule timer
}

int main()
{
	time_hand th;
	//struct timeval timeout;
	th.tv.tv_sec = 1;
	th.tv.tv_usec = 0;

	event_enable_debug_mode();
	//初始化 Reactor 实例
	struct event_base *base = event_init();


	//初始化事件event，设置回调函数和关注的事件
	//void event_set(struct event *ev, int fd, short event, void (*cb)(int, short, void *), void *arg)
	//ev：执行要初始化的event对象；
	//fd：该event绑定的“句柄”，对于信号事件，它就是关注的信号；
	//event：在该fd上关注的事件类型，它可以是EV_READ, EV_WRITE, EV_SIGNAL；
	//cb：这是一个函数指针，当fd上的事件event发生时，调用该函数执行处理，它有三个参数，调用时由event_base负责传入，按顺序，实际上就是event_set时的fd, event和arg；
	//arg：传递给cb函数指针的参数；
	//事实上这等价于调用event_set(&ev, -1, 0, timer_cb, NULL);
	//struct event ev;  事件设置
	evtimer_set(&th.ev, timer_cb, &th);

	//设置event从属的event_base   event 绑定到 base
	//这一步相当于指明event要注册到哪个event_base实例上；
	event_base_set(base, &th.ev);


	//基本信息都已设置完成，只要简单的调用event_add()函数即可完成，其中timeout是定时值；
	//这一步相当于调用Reactor::register_handler()函数注册事件。
	//event_add(&th.ev, &th.tv);

	//程序进入无限循环，等待就绪事件并执行事件处理
	printf("start dispatch...\n");
	int ret = event_base_dispatch(base);
	printf("on finish !!!ret = %d\n",ret);

	return 0;
}
