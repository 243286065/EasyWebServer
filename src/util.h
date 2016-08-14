/*
 * util.h
 *
 *  Created on: 2016-8-4
 *      Author: lab401
 *      function:提供一些公共函數或者公共类
 */

#ifndef UTIL_H_
#define UTIL_H_

#include "ew_init_config_class.h"
#include "ew_getopt_util.h"
#include "ew_exit_status.h"
#include "ew_epoll.h"
#include "ew_mime_type.h"

#define PROGRAM_NAME	"EasyWebServer"
#define VERSION "1.0"

#define BUF_SIZE_TINY		32
#define BUF_SIZE_SMALL		128
#define BUF_SIZE_MIDDLE		512
#define BUF_SIZE_BIG		1024
#define BUF_SIZE_MAXSIZE	(16*1024)


/*show the program version*/
void showVersion();

/*show the server information when start*/
void showInfo_start(ew_init_config&);

/*print the log information*/
void log_error(const char*);

/*read config file*/
void read_conf(ew_init_config&);

/*make socket unblocking*/
void make_socket_non_blocking(int);

/*initlialize server socket and listen*/
int open_socket_listen(ew_init_config&);

/*convert string(char*) to lowercase*/
void convert_lowerCase(char*,int len);

/*string class*/
class ew_string{
public:
	int len;	//char size, not include '\0'
	const char* pos;
	ew_string(const char*,int);
	void trim();	//remove the blank space
};

/*send data to client*/
void send_data(int fd,char* buf);

/*convert time(char*) to time value(time_t)*/
time_t time_convert_to_timet(ew_string&);

/*convert time(time_t) to time value(char*)*/
void timet_convert_to_chars(time_t&,char*,int);

/*compare two time value.*/
int compare_time(time_t &,time_t &);

#endif /* UTIL_H_ */
