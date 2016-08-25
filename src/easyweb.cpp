#include <iostream>
using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <signal.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sched.h>
#include <sys/sysinfo.h>
#include <pthread.h>
#include <errno.h>
#include <vector>

#include "util.h"
#include "ew_http_util.h"
#include "log.h"

#define CONF_FILE_DEFAULT   "./easyweb.conf"
#define MAX_EVENTS			1024
#define TIME_OUT_EPOLL		10

ew_init_config conf;
vector<pid_t> sub_process_list; //store sub worker process PID
char buf[BUF_SIZE_BIG];
char log_buf[BUF_SIZE_SMALL];

/*Load opt command and config file*/
static void init(int argc, char* argv[]) {
	parse_argv(argc, argv, conf);
	if (!conf.get_conf_file()) {
		conf.set_conf_file(CONF_FILE_DEFAULT);
	}
	read_conf(conf);
	showInfo_start(conf);
	//init msg
	msg_init();
}

/*deal child process exit signal*/
void sig_child(int signo) {
	pid_t pid;
	int stat;
	while ((pid = waitpid(-1, &stat, WNOHANG)) > 0) {
		fprintf(stdout, "EasyWeb-> [INFO] worker process has terminated:%d \n",
				pid);
		perror("process error");
	}
}

/*SIGINT--master process exit*/
void sig_int(int signo) {
	int size = sub_process_list.size();
	int pid = getpid();
	if (pid == sub_process_list[0]) { //master process
		for (int i = 1; i < size; ++i) {
			kill(sub_process_list[i], SIGINT);
		}
	}
	fprintf(stdout, "EasyWeb-> [INFO]process exit:%d", pid);
	exit(EW_EXIT_OK);
}

/*worker process handler*/
void worker(int);

/*master process job--log*/
void* log(void*);

int main(int argc, char* argv[]) {
	//Load opt command and config file
	init(argc, argv);
	signal(SIGCHLD, sig_child);

	/*set signal handle for SIGPIPE*/
	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_IGN; //ignore
	sa.sa_flags = 0;
	if (sigaction(SIGPIPE, &sa, NULL)) //-1:error
	{
		//log
		return EW_EXIT_SIGPIPE_ERR;
	}

	/*initialize listening socket*/
	int serverFd = open_socket_listen(conf);

	/*create child processes base the CPU cores*/
	sub_process_list.push_back(getpid());
	int all_processor_num = get_nprocs();
	cpu_set_t mask;
	for (size_t i = 0; i < conf.get_processorNum(); ++i) {
		pid_t pid = fork();
		if (pid == 0) { //Child
			//set special processor to run the worker process
			CPU_ZERO(&mask);
			CPU_SET(i%all_processor_num,&mask);
			if (sched_setaffinity(0, sizeof(mask), &mask) < 0) {
				perror("sched_setaffinity");
			}
			rename_proc_title(argc,argv,"EasyWebServer worker");
			worker(serverFd);
			return EW_EXIT_OK;
		}
		sub_process_list.push_back(pid);
	}
	/*parent process*/
	rename_proc_title(argc,argv,"EasyWebServer master");
	if (conf.get_processorNum() == 0) {
		worker(serverFd);
	}

	pthread_t id;
	if (pthread_create(&id, NULL, log, NULL) < 0) {
		exit(EW_PTHREAD_CREATE_ERR);
	}
	while (1) {
		//fprintf(stdout,"EasyWeb-> [INFO] master process chcek \n");
		sleep(10);
	}
	return EW_EXIT_OK;
}

void* log(void*) {
	log_info_recv(conf);
}

/*worker process handler*/
void worker(int serverFd) {
	pid_t pid = getpid();
	fprintf(stdout, "EasyWeb-> [INFO] worker process has created:%d \n", pid);

	struct sockaddr_in clientaddr;
	socklen_t add_len = sizeof(clientaddr); //initialize the clientaddr len
	memset(&clientaddr, 0, sizeof(clientaddr));

	/*creat epoll*/
	int epollFd = ew_epoll_create(0);
	/*add server socket to epoll*/

	struct epoll_event event, events[MAX_EVENTS];
	ew_http_request_class listen_http_rq(serverFd);
	event.events = EPOLLIN | EPOLLET;
	event.data.ptr = (void*) &listen_http_rq;
	ew_epoll_add(epollFd, serverFd, &event);

	char buf[BUF_SIZE_MAXSIZE];
	int pos, len;

	while (1) {
		/*epoll_wait*/
		int nfds = ew_epoll_wait(epollFd, events, MAXEVENTS, -1);
		/*deal all events*/
		for (int i = 0; i < nfds; ++i) {
			//fprintf(stdout, "i:%d	nfds:%d	%d\n", i, nfds, pid);
			buf[0] = '\0';
			struct epoll_event event_t = events[i];
			ew_http_request_class *rq =
					(ew_http_request_class *) (event_t.data.ptr);
			if (rq->fd <= 0)
				continue;
			if (rq->fd == serverFd) { //server socket
				int clientFd;
				//fprintf(stdout, "epoll serverFd	%d\n", pid);
				while ((clientFd = accept(serverFd, (sockaddr*) &clientaddr,
						&add_len)) > 0) {
					if (clientFd <= 0) {
						//log
						//						fprintf(
						//								stderr,
						//								"EasyWeb-> [ERROR]socket accpet failed by woker process:%d \n",
						//								pid);
						continue;
					}
					/*set client socket un-blocking*/
					make_socket_non_blocking(clientFd);
					/*add the client socket to epoll*/
					//event.data.fd = clientFd;
					event_t.events = EPOLLIN | EPOLLET;
					ew_http_request_class *new_http_rq =
							new ew_http_request_class(clientFd);
					event_t.data.ptr = (void*) new_http_rq;
					ew_epoll_add(epollFd, new_http_rq->fd, &event_t);
					sprintf(log_buf, "new connection from [%s]", inet_ntoa(
							clientaddr.sin_addr));
					log_info_send("INFO", log_buf);
				}
			} else if ((event_t.events & EPOLLERR) || (event_t.events
					&EPOLLHUP)) {
				//ew_http_request_class *rq =(ew_http_request_class *) (events[i].data.ptr);
				fprintf(stderr, "EasyWeb-> [ERROR] epoll error fd:%d \n",
						rq->fd);
				ew_epoll_del(epollFd, rq->fd, &(event_t));
				close(rq->fd);
				delete rq;
				continue;
			} else {
				if (event_t.events & EPOLLIN) { //http socket
					//ew_http_request_class *rq =
					//		(ew_http_request_class *) (events[i].data.ptr);
					//accept data
					//fprintf(stdout, "EPOLLIN	%d\n", pid);
					int clientFd = rq->fd;
					if (clientFd < 0)
						continue;
					pos = 0;
					len = 0;
					//fprintf(stdout,"~~~~~~~~~~~~~");
					while ((len = read(clientFd, buf + pos, BUF_SIZE_MAXSIZE
							- 1 - pos)) > 0) {
						pos += len;
					}
					if (len == -1 && errno != EAGAIN) {
						//log
						fprintf(
								stderr,
								"EasyWeb-> [ERROR]receve data failed by woker process:%d \n",
								pid);
						buf[0] = '\0';
						continue;
					} else if (len == 0) { //client has close
						//fprintf(stderr, "2[FD:%d]\n", clientFd);
						ew_epoll_del(epollFd, clientFd, &(event_t));
						close(clientFd);
						delete rq;
						continue;
					}
					//fprintf(stdout, "EasyWeb-> FD:%d[request data] %s\n",
					//		clientFd, buf);
					/*change epoll mod to send data*/
					//event.data.fd = clientFd;
					event_t.events = event_t.events | EPOLLOUT;
					//ew_http_request_class *rq=(ew_http_request_class *)event.data.ptr;
					rq->http_request_init(buf);
					ew_epoll_modify(epollFd, clientFd, &event_t);
					buf[0] = '\0';
				}
				if (event_t.events & EPOLLOUT) {
					/*send data*/
					//ew_http_request_class *rq =
					//		(ew_http_request_class *) (events[i].data.ptr);
					int fd = rq->fd;
					//sprintf(
					//		buf,
					//		"HTTP/1.1 200 OK\r\n"
					//			"Server: "PROGRAM_NAME" \r\n"
					//	"Content-Type: text/html\r\n\r\n"
					//"<html><head><title>Welcome</title></head><body><font size=+5>Hello!<br/>EasyWebServer!</font></body></html>");
					pos = 0;
					len = 0;
					len = strlen(buf);
					int n = len;
					while (n > 0) {
						pos = write(fd, buf + len - n, n);
						if (pos == -1 && errno != EAGAIN) {
							fprintf(
									stderr,
									"EasyWeb-> [ERROR]send data failed by woker process:%d \n",
									pid);
							break;
						}
						n -= pos;
						//fprintf(stdout, "len:%d	pos:%d n:%d	FD:%d\n", len, pos,
						//		n, fd);
					}
					//fprintf(stdout, "EasyWeb-> [INFO]send:%s\n", buf);
					buf[0] = '\0';
					//fprintf(stdout, "end	%d\n", pid);
					rq->http_request_head_parser(conf);
					rq->http_request_send_respond();
					//fprintf(stderr,"3[FD:%d]\n",fd);
					//fprintf(stderr,"！！！statu=%d\n",rq->statu);
					if(rq->statu==2){
						ew_epoll_del(epollFd, fd, &(event_t));
						close(fd);
						delete rq;
					}
				}
			}
		}
	}

}
