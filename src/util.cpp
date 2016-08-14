/*
 * util.cpp
 *
 *  Created on: 2016-8-4
 *      Author: lab401
 */

#include "util.h"
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

/*show the program version*/
void showVersion() {
	fprintf(stdout, "Programe version: "VERSION" \n");
}

/*show the server information when start*/
void showInfo_start(ew_init_config& conf) {
	fprintf(stdout,
			"	*********************************************************\n");
	fprintf(stdout, "	*							*\n");
	fprintf(stdout, "	* WelCome " PROGRAM_NAME" !				*\n"
	"	*							*\n"
	"	* port=%d; threadnum=%zd; maxConnect=%zd; 		*\n"
	"	* root_dir=%s; log_file=%s 		*\n"
	"	* base on the config file:%s 		*\n"
	"	*							*\n"
	"	*********************************************************\n\n",
			conf.get_port(), conf.get_threadnum(), conf.get_maxConnect(),
			conf.get_root_dir(), conf.get_log_file(), conf.get_conf_file());
}

/*print the log information*/
void log_error(const char* info) {
	fprintf(stderr, "%s\n", info);
	exit(EW_EXIT_OPT_ERR);
}

/*read config file*/
void read_conf(ew_init_config& conf) {
	FILE *fp = fopen(conf.get_conf_file(), "r");
	if (!fp) {
		log_error("cannot open config file!");
	}
	int maxlen = BUF_SIZE_MIDDLE;
	char buf[maxlen];
	int line_len = 0;
	while (fgets(buf, maxlen, fp)) {
		line_len = strlen(buf);
		char* delim_pos = strstr(buf, "=");
		if (!delim_pos)
			continue;
		if (buf[line_len - 1] == '\n') {
			buf[line_len - 1] = '\0';
			line_len--;
		}
		if (buf[line_len - 1] == '\r') {
			buf[line_len - 1] = '\0';
			line_len--;
		}
		if (!conf.get_root_dir()
				&& strncmp("root_dir", buf, strlen("root_dir")) == 0)
			conf.set_root_dir(delim_pos + 1);
		if (conf.get_port() == 0 && strncmp("port", buf, strlen("port")) == 0)
			conf.set_port(atoi(delim_pos + 1));
		if (conf.get_threadnum() == 0 && strncmp("threadnum", buf, strlen(
				"threadnum")) == 0)
			conf.set_threadnum(atoi(delim_pos + 1));
		if (conf.get_maxConnect() == 0 && strncmp("maxConnect", buf, strlen(
				"maxConnect")) == 0)
			conf.set_maxConnect(atoi(delim_pos + 1));
		if (!conf.get_log_file()
				&& strncmp("log_file", buf, strlen("log_file")) == 0)
			conf.set_log_file(delim_pos + 1);

	}
}
/*make socket listen*/
int open_socket_listen(ew_init_config& conf) {
	short port = conf.get_port();
	if (port < 5000) {
		port = 8080;
	}
	int serverfd, optval = 1;
	struct sockaddr_in serveraddr;

	/*initialize a socket*/
	if ((serverfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		//log
		exit(EW_EXIT_SOCKET_INIT_ERR);
	}

	/*allow reuse the port which in "TIME_WAIT"*/
	if (setsockopt(serverfd, SOL_SOCKET, SO_REUSEADDR, (const void*) &optval,
			sizeof(optval)) < 0) {
		//log
		exit(EW_EXIT_SOCKET_SETOPT_ERR);
	}

	/*set non-blocking*/
	make_socket_non_blocking(serverfd);

	/*initialize the server socket addr*/
	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons((unsigned short) port);
	if (bind(serverfd, (struct sockaddr*) &serveraddr, sizeof(serveraddr)) < 0) {
		//log
		exit(EW_EXIT_SOCKET_BIND_ERR);
	}

	/*listen*/
	if (listen(serverfd, conf.get_maxConnect()) < 0) {
		//log
		exit(EW_EXIT_SOCKET_LISTEN_ERR);
	} else {
		fprintf(stdout, "EasyWeb-> Http Server is working on port:%d\n", port);
	}

	return serverfd;
}

/*make socket unblocking*/
void make_socket_non_blocking(int fd) {
	int flags, rs;
	flags = fcntl(fd, F_GETFL, 0);
	if (flags < 0) {
		//log
		exit(EW_EXIT_FCNTL_FGETFL_ERR);
	}

	flags |= O_NONBLOCK;
	rs = fcntl(fd, F_SETFL, flags);
	if (rs < 0) {
		//log
		exit(EW_EXIT_FCNTL_FSETFL_ERR);
	}
}

/*ew_string class*/
ew_string::ew_string(const char* p, int size = 0) :
	pos(p), len(size) {
	if (len == 0) {
		len = strlen(p);
	}
}
void ew_string::trim() {
	const char *s = pos;
	while (*s == ' ') {
		s++;
		len--;
	}
	pos = s;
	s = pos + len - 1;
	while (*s == ' ' && len > 0) {
		s--;
		len--;
	}
}

/*convert string(char*) to lowercase*/
void convert_lowerCase(char* str, int len) {
	char* p = str;
	while (len--) {
		*p = tolower(*p);
	}
}

/*send data to client*/
void send_data(int fd, char* buf) {
	int pos = 0, len = 0;
	len = strlen(buf);
	int n = len;
	while (n > 0) {
		pos = write(fd, buf + len - n, n);
		if (pos == -1 && errno != EAGAIN) {
			fprintf(stderr, "EasyWeb-> [ERROR]send data failed [%s:%d], \n",
					__FILE__, __LINE__);
			break;
		}
		n -= pos;
	}
}

/*convert time(char*) to time value(time_t)*/
time_t time_convert_to_timet(ew_string& time_char) {
	time_char.trim();
	char time_buf[time_char.len + 1];
	strncpy(time_buf, time_char.pos, time_char.len);
	//fprintf(stderr, "-----%s\n", time_buf);
	time_buf[time_char.len] = '\0';
	struct tm tm;
	strptime(time_buf, "%a, %d %b %Y %H:%M:%S GMT", &tm);
	time_t time_s = mktime(&tm);
	return time_s;
}

/*convert time(time_t) to time value(char*)*/
void timet_convert_to_chars(time_t& time_s, char* buf,int len) {
	struct tm tm;
	localtime_r(&time_s, &tm);
	//fprintf(stderr,"convert:%d %d\n",time_s,len);
	strftime(buf, len, "%a, %d %b %Y %H:%M:%S GMT", &tm);
}

/*compare two time value.*/
int compare_time(time_t &t1, time_t &t2) {
	double time_diff = difftime(t1, t2);
	if (time_diff < -1e-6)
		return -1;
	else if (time_diff > 1e-6)
		return 1;
	else
		return 0;
}

