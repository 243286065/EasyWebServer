/*
 * ew_epoll.h
 *
 *  Created on: 2016-8-4
 *      Author: lab401
 *    Function:	提供epoll相关函数
 */

#ifndef EW_EPOLL_H_
#define EW_EPOLL_H_

#include <sys/epoll.h>
#define MAXEVENTS	10000
#define TIMEOUT		10

int ew_epoll_create(int);
void ew_epoll_add(int,int,struct epoll_event *);
void ew_epoll_modify(int,int,struct epoll_event *);
void ew_epoll_del(int,int,struct epoll_event *);
int ew_epoll_wait(int,struct epoll_event *,int,int);

#endif /* EW_EPOLL_H_ */
