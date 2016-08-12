/*
 * ew_exit_status.h
 *
 *  Created on: 2016-8-4
 *      Author: lab401
 *      function:提供退出状态宏定义
 */

#ifndef EW_EXIT_STATUS_H_
#define EW_EXIT_STATUS_H_

#define EW_EXIT_OK					0
#define EW_EXIT_OPT_ERR				1
#define EW_EXIT_SIGPIPE_ERR			2
#define EW_EXIT_SOCKET_INIT_ERR		3
#define EW_EXIT_SOCKET_SETOPT_ERR	4
#define EW_EXIT_SOCKET_BIND_ERR		5
#define EW_EXIT_SOCKET_LISTEN_ERR	6
#define EW_EXIT_FCNTL_FGETFL_ERR	7
#define EW_EXIT_FCNTL_FSETFL_ERR	8
#define EW_EXIT_EPOLL_CREATE1_ERR	9
#define EW_EXIT_EPOLL_MALLOC_ERR	10
#define EW_EXIT_EPOLL_ADD_ERR		11
#define EW_EXIT_EPOLL_MOD_ERR		12
#define EW_EXIT_EPOLL_DEL_ERR		13
#define EW_EXIT_EPOLL_WAIT_ERR		14
#define EW_EXIT_SIGCHLD_ERR			15

#endif /* EW_EXIT_STATUS_H_ */
