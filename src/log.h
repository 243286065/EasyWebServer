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
#include "ew_init_config_class.h"

#define BUF_SIZE	128

struct msg_st {
	long msg_type;
	char msg[BUF_SIZE]; //info text
};

static int msgid;

/*init msg queue*/
void msg_init();

/*send log info*/
/**
 * type:"ERROR"|"INFO"|"WARNING"
 */
void log_info_send(const char* type, const char* log);

/*recive log info*/
void log_info_recv(ew_init_config& conf);

#endif /* LOG_H_ */
