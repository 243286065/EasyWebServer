/*
 * ew_http_util.h
 *
 *  Created on: 2016-8-4
 *      Author: lab401
 *    Function:	提供http请求的对象封装类
 */

#ifndef EW_HTTP_UTIL_H_
#define EW_HTTP_UTIL_H_

#include <string>
#include <sys/stat.h>
#include <time.h>
#include <map>
#include "util.h"
#include "ew_init_config_class.h"

#define EW_HTTP_OK				200
#define EW_HTTP_NOT_MODIFIED	304
#define EW_HTTP_FORBIDDEN		403
#define EW_HTTP_NOT_FOUND		404
#define EW_HTTP_OTHER_ERROR		500

/*send respond head template function*/
void send_respond_head_common(int code, std::string& content_type,
		int keeplive, int fd, struct stat& file_info);

class respond_code_state_class {
public:
	respond_code_state_class();
	const char* getState(int code);
private:
	std::map<int, const char*> state_map;
};

class ew_http_respond_class {
public:
	std::string filename;
	int file_fd;
	struct stat file_info;
	int respond_code;
	std::string content_type;
	int keep_alive;
	ew_http_respond_class(std::string& filename_s, time_t rq_time);
	void send_respond_head(int fd);
	void sendfile_respond_body(int fd); //send file by sendfile
	void send_respond(int fd); //send respond
};

class ew_http_request_class {
public:
	int fd; //socket fd
	int epollFd;
	std::string *buf_s;
	std::string filename;
	const char *buf; //buf_s pointer
	ew_string *uri;
	ew_string *method;
	ew_string *http_protocol;
	int keepalive; //mark
	time_t value_IF_MODIFILE_SINCE;

	ew_http_respond_class *respond;

	ew_http_request_class(int sockfd);
	void http_request_init(char* buf_chars);
	void http_request_head_parser(ew_init_config& conf); //init members
	void http_request_send_respond();
	~ew_http_request_class();
};

#endif /* EW_HTTP_UTIL_H_ */
