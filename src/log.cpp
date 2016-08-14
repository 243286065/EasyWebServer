/*
 * log.cpp
 *
 *  Created on: 2016-8-14
 *      Author: lab401
 */
#include "log.h"
#include <errno.h>

/*store info*/

void log_info_send(const char* type,const char* log){
	if(msgid==-1){
		exit(EW_EXIT_MSGGET_ERR);
	}
	struct msg_st log_t;
	log_t.timestamp=get_current_time_sec();
	sprintf(log_t.msg,"[%s]%s\n",type,log);
	//send data
	int state=0;
	if((state=msgsnd(msgid,(void*)&log_t,BUF_SIZE,ICP_NOWAIT))<0){
		exit(EW_EXIT_MSGSENT_ERR);
	}else if(state==0&&erro)
}
