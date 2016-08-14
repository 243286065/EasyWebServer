/*
 * ew_init_config_class.cpp
 *
 *  Created on: 2016-8-4
 *      Author: lab401
 */

#include "ew_init_config_class.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/sysinfo.h>

ew_init_config::ew_init_config() :
	conf_file(NULL), log_file(NULL), root_dir(NULL), threadnum(0),
			maxConnect(0), port(0) {
	processorNum = get_nprocs();
	//processorNum=1;
}

static char* new_set_method_chars(char* loc, const char* get) {
	size_t len = strlen(get);
	delete loc;
	loc = (char*) malloc(len + 1);
	strcpy(loc, get);
	loc[len] = '\0';
	return loc;
}

void ew_init_config::set_conf_file(const char* conf) {
	conf_file = new_set_method_chars(conf_file, conf);
}

void ew_init_config::set_log_file(const char* log) {
	log_file = new_set_method_chars(log_file, log);
}

void ew_init_config::set_root_dir(const char* rootdir) {
	root_dir = new_set_method_chars(root_dir, rootdir);
}

void ew_init_config::set_threadnum(const size_t num) {
	threadnum = num;
}

void ew_init_config::set_maxConnect(const size_t num) {
	maxConnect = num;
}

void ew_init_config::set_port(const short num) {
	port = num;
}

short ew_init_config::get_port() {
	return port;
}

char* ew_init_config::get_log_file() {
	return log_file;
}

char* ew_init_config::get_conf_file() {
	return conf_file;
}

char* ew_init_config::get_root_dir() {
	return root_dir;
}

size_t ew_init_config::get_threadnum() {
	return threadnum;
}

size_t ew_init_config::get_maxConnect() {
	return maxConnect;
}

size_t ew_init_config::get_processorNum() {
	return processorNum;
}

ew_init_config::~ew_init_config() {
	delete conf_file;
	delete log_file;
	delete root_dir;
}
