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

struct event ev;  
struct timeval tv;  
void time_cb(int fd, short event, void *argc)  
{  
    printf("timer wakeup sddsf!!!!  \n");  
    event_add(&ev, &tv); // reschedule timer  
}  
int main()  
{  
    struct event_base *base = event_init();  
    tv.tv_sec = 10; // 10s period  
    tv.tv_usec = 0;  
    evtimer_set(&ev, time_cb, NULL);  
    event_base_set(base, &ev);
    event_add(&ev, &tv);  
    event_base_dispatch(base);  
}  
