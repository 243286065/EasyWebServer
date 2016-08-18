/*
 * ew_epoll.cpp
 *
 *  Created on: 2016-8-4
 *      Author: lab401
 */
#include "ew_epoll.h"
#include "ew_exit_status.h"
#include <stdlib.h>
#include <errno.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static struct epoll_event *events;

int ew_epoll_create(int flags) {
	int fd = epoll_create1(flags);
	if (fd < 1) {
		//log
		exit(EW_EXIT_EPOLL_CREATE1_ERR);
	}
	//	events = (struct epoll_event*) malloc(sizeof(struct epoll_event)
	//			* MAXEVENTS);
	//	if (events == NULL) {
	//		//log
	//		exit(EW_EXIT_EPOLL_MALLOC_ERR);
	//	}
	return fd;
}

void ew_epoll_add(int epollFd, int fd, struct epoll_event *event) {
	int rs = epoll_ctl(epollFd, EPOLL_CTL_ADD, fd, event);
	if (rs < 0) {
		//log
		fprintf(stderr, "[error] worker epoll_ctl add error = %s.\n", strerror(
				errno));
		exit(EW_EXIT_EPOLL_ADD_ERR);
	}
}

void ew_epoll_modify(int epollFd, int fd, struct epoll_event *event) {
	int rs = epoll_ctl(epollFd, EPOLL_CTL_MOD, fd, event);
	if (rs < 0) {
		//log
		fprintf(stderr,
				"EasyWeb-> [ERROR]epoll_modify failed by woker process:%d \n",
				getpid());
		exit(EW_EXIT_EPOLL_MOD_ERR);
	}
}

void ew_epoll_del(int epollFd, int fd, struct epoll_event *event) {
	int rs = epoll_ctl(epollFd, EPOLL_CTL_DEL, fd, event);
	if (rs < 0) {
		//log
		fprintf(
				stderr,
				"EasyWeb-> [ERROR]epoll_del [FD:%d] failed by woker process:%d \n",
				fd, getpid());
		perror("EPOLL_CTL_DEL ERR:");
		exit(EW_EXIT_EPOLL_DEL_ERR);
	}
}

int ew_epoll_wait(int epollFd, struct epoll_event *events, int maxevents,
		int timeout) {
	int rs = epoll_wait(epollFd, events, maxevents, timeout);
	if (rs == 0) {
		//log
		fprintf(stderr,
				"EasyWeb-> [ERROR]epoll_wait failed by woker process:%d \n",
				getpid());
		exit(EW_EXIT_EPOLL_WAIT_ERR);
	}
}
