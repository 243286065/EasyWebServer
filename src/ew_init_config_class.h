/*
 * ew_init_config_class.h
 *
 *  Created on: 2016-8-4
 *      Author: lab401
 *      function:提供保存全局配置的类
 */

#ifndef EW_INIT_CONFIG_CLASS_H_
#define EW_INIT_CONFIG_CLASS_H_

#include <iostream>
/*the program config struct*/
class ew_init_config {
private:
	char* conf_file; //config file
	char* log_file; //log file
	char* root_dir; //the web root dir path
	size_t threadnum; //the max size of threadpool
	size_t maxConnect; //accpet queue size
	size_t processorNum; //processor numbers
	short port; //server listen port
public:
	ew_init_config();
	void set_conf_file(const char*);
	void set_log_file(const char*);
	void set_root_dir(const char*);
	void set_threadnum(const size_t);
	void set_maxConnect(const size_t);
	void set_port(const short);
	short get_port();
	char* get_log_file();
	char* get_conf_file();
	char* get_root_dir();
	size_t get_threadnum();
	size_t get_processorNum();
	size_t get_maxConnect();
	~ew_init_config();
};

#endif /* EW_INIT_CONFIG_CLASS_H_ */
