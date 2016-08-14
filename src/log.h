/*
 * log.h
 *
 *  Created on: 2016-8-14
 *      Author: lab401
 *    Function:	记录日志
 */

#ifndef LOG_H_
#define LOG_H_

#include <sys/msg.h>
#include <unistd.h>
#include <stdlib.h>
#include "ew_exit_status.h"

#define BUF_SIZE	128

struct msg_st{
	time_t timestamp;			//time info
	char msg[BUF_SIZE];			//info text
};

static int msgid=msgget((key_t)1234,0666 |IPC_CREAT);

/*store info*/
/**
 * type:"ERROR"|"INFO"|"WARNING"
 */
void log_info_send(const char* type,const char* log);

#endif /* LOG_H_ */
