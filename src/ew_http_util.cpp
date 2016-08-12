/*
 * ew_http_util.cpp
 *
 *  Created on: 2016-8-6
 *      Author: lab401
 */
#include "ew_http_util.h"
#include "util.h"
#include "ew_mime_type.h"
#include <sys/sendfile.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

respond_code_state_class::respond_code_state_class() {
	state_map.insert(std::make_pair(EW_HTTP_OK, "OK"));
	state_map.insert(std::make_pair(EW_HTTP_NOT_FOUND, "NOT FOUND"));
	state_map.insert(std::make_pair(EW_HTTP_NOT_MODIFIED, "NOT MODIFIED"));
	state_map.insert(std::make_pair(EW_HTTP_FORBIDDEN, "FORBIDDEN"));
	state_map.insert(std::make_pair(EW_HTTP_OTHER_ERROR, "SERVER ERROR"));
}

const char* respond_code_state_class::getState(int code) {
	return state_map[code];
}

static respond_code_state_class respond_code_state;

/*403 404 500 respond pages*/
static void send_special_page_body(int fd, int code) {
	char* buf = new char[BUF_SIZE_BIG];
	sprintf(buf, "<html>\n"
		"<head>\n"
		"<title>Welcome to EasyWebServer!</title>\n"
		"<style>\n"
		"body{width:35em;margin:50 auto;font-family:Tahoma,Verdana,Arial,sans-serif;}\n"
		"</style>\n"
		"</head>\n"
		"<body>\n"
		"<h1>%d %s</h1>\n"
		"</body>\n", code,respond_code_state.getState(code));
	send_data(fd, buf);
	delete[] buf;
}

/*send respond head template function*/
void send_respond_head_common(int code, std::string& content_type,
		int keeplive, int fd) {
	char* head = new char[BUF_SIZE_MIDDLE];
	sprintf(head, "HTTP/1.1 %d %s\r\n", code, respond_code_state.getState(code));
	sprintf(head, "%sServer: "PROGRAM_NAME"\r\n",head);
	if (keeplive == 1)
		sprintf(head, "%sConnection: keep-alive\r\n",head);
//	sprintf(head, "Content-type: %s\r\n\r\n", content_type.c_str());
	sprintf(head, "%sContent-Type: text/html\r\n\r\n",head);
	send_data(fd, head);
	delete[] head;
}

ew_http_respond_class::ew_http_respond_class(std::string& filename_s) :
	filename(filename_s), keep_alive(0) {

	int rs = stat(filename.c_str(), &file_info);
	if (rs == -1) {
		if (errno == ENOENT) //no exit
		{
			//send 404 page
			respond_code = EW_HTTP_NOT_FOUND;
			return;
		} else {
			respond_code = EW_HTTP_OTHER_ERROR;
			return;
		}
	} else if (!(file_info.st_mode & S_IRUSR)) { //can't read file
		respond_code = EW_HTTP_FORBIDDEN;
		return;
	} else {
		respond_code = EW_HTTP_OK;
	}
	file_fd = open(filename.c_str(), O_RDONLY);
}

void ew_http_respond_class::send_respond_head(int fd) {
	send_respond_head_common(respond_code, content_type, keep_alive, fd);
}

void ew_http_respond_class::send_respond(int fd) {
	//char* body=new char[BUF_SIZE_BIG*4];		//read 4KB data
	//delete[] body;
	send_respond_head(fd);
	switch (respond_code) {
	case EW_HTTP_OK:
		sendfile_respond_body(fd);
		break;
	default:
		send_special_page_body(fd, respond_code);
		break;
	}
}

void ew_http_respond_class::sendfile_respond_body(int fd) {
	sendfile(fd, file_fd, NULL, file_info.st_size);
	close(file_fd);
	//	if (keep_alive == 0) {
	//		close(fd);
	//	}
}

ew_http_request_class::ew_http_request_class(int sockfd) :
	fd(sockfd), buf_s(NULL), buf(NULL), uri(NULL), method(NULL), respond(NULL),
			http_protocol(NULL) {
}

ew_http_request_class::~ew_http_request_class() {
	delete buf_s;
	delete respond;
	delete uri;
	delete method;
	delete http_protocol;
}

void ew_http_request_class::http_request_init(char* buf_chars) {
	buf_s = new std::string(buf_chars);
	buf = buf_s->c_str();
}

void ew_http_request_class::http_request_head_parser(ew_init_config& conf) {
	const char* pos, *nextpos;
	int len = 0;
	pos = buf;
	while (*pos == ' ') {
		pos++;
	}
	len = pos - buf;
	nextpos = pos;
	while (*nextpos != ' ') {
		nextpos++;
	}
	method = new ew_string(buf + len, nextpos - pos);
	pos = nextpos;
	while (*pos == ' ') {
		pos++;
	}
	len = pos - buf;
	nextpos = pos;
	while (*nextpos != ' ') {
		nextpos++;
	}
	uri = new ew_string(buf + len, nextpos - pos);
	pos = nextpos;
	while (*pos == ' ') {
		pos++;
	}
	len = pos - buf;
	nextpos = pos;
	while ((*nextpos != ' ') && (*nextpos != '\r') && (*nextpos != '\n')) {
		nextpos++;
	}
	http_protocol = new ew_string(buf + len, nextpos - pos);
	pos = nextpos;
	//	while(*pos=' '||*pos='\r'||*pos='\n'){
	//		pos++;
	//	}
	if (strstr(pos, "Connection") && strstr(pos, "keep-alive")) {
		keepalive = 1;
	}
	filename = std::string(conf.get_root_dir()) + std::string(uri->pos,
			uri->len);
	if (filename[filename.size() - 1] == '/') {
		filename += "index.html";
	}
	respond = new ew_http_respond_class(filename);
	respond->keep_alive = keepalive;
}

void ew_http_request_class::http_request_send_respond() {
	respond->send_respond(fd);
}
