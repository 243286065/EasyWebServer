/*
 * log.cpp
 *
 *  Created on: 2016-8-14
 *      Author: lab401
 */
#include "log.h"
#include "util.h"
#include <errno.h>
#include <fcntl.h>

/*init msg queue*/
void msg_init(){
	msgid=msgget((key_t)1234,0666 |IPC_CREAT);
	//delete for clear msg
	if(msgctl(msgid,IPC_RMID,0)==-1){
		exit(EW_EXIT_MSGRMID_ERR);
	}
	msgid=msgget((key_t)1234,0666 |IPC_CREAT);
}

/*send log info*/
void log_info_send(const char* type, const char* log) {
	if (msgid == -1) {
		exit(EW_EXIT_MSGGET_ERR);
	}
	struct msg_st log_t;
	time_t timestamp = get_current_time_sec();
	timet_convert_to_chars(timestamp,log_t.msg,BUF_SIZE);
	log_t.msg_type=1;
	sprintf(log_t.msg, "%s: [%s] %s\n",log_t.msg,type, log);
	//send data
	int state = 0;
	if ((state = msgsnd(msgid, (void*) &log_t, BUF_SIZE, IPC_NOWAIT)) < 0) {
		//exit(EW_EXIT_MSGSENT_ERR);
	}
}

/*recive log info*/
void log_info_recv(ew_init_config& conf) {
	if (msgid == -1) {
		exit(EW_EXIT_MSGGET_ERR);
	}
	struct msg_st log_t;

	int file_fd=open(conf.get_log_file(),O_WRONLY|O_CREAT|O_APPEND,S_IRUSR|S_IWUSR);

	if(file_fd<0){
		fprintf(stderr,"EasyWebServer-> [ERROR]can't wirte log info to local file!\n");
	}
	FILE* fp=fdopen(file_fd,"w");
	if(!fp){
		perror("log");
	}
	//get log msg from msg queue
	while (1) {
		int len = 0;
		if ((len = msgrcv(msgid, (void*) &log_t, BUF_SIZE, 1, IPC_NOWAIT))
				== -1) {	//no msg
			//perror("log");
			//exit(EW_EXIT_MSGRECV_ERR);
			usleep(10000);
		} else {
			if (len != 0){
				//fprintf(stderr, "%s\n", log_t.msg);
				if(file_fd>0){
					//write(file_fd,log_t.msg,strlen(log_t.msg)+1);
					fwrite(log_t.msg,strlen(log_t.msg),1,fp);
					fflush(fp);
				}
			}
		}

		//printf("123\n");
	}
}

