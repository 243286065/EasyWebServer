/*
 * ew_getopt_util.h
 *
 *  Created on: 2016-8-4
 *  Author: lab401
 *  function:提供解析程序可选命令参数的工具函数
 */

#ifndef EW_GETOPT_UTIL_H_
#define EW_GETOPT_UTIL_H_

#include <stdio.h>
#include <getopt.h>

#include "ew_init_config_class.h"
#include "util.h"

/*command argvs option*/
static const struct option long_options[] =
{
    {"help", no_argument, NULL, '?'},
    {"version", no_argument, NULL, 'v'},
    //{"conf", optional_argument, NULL, 'c'},
    {"conf", required_argument, NULL, 'c'},
    {"port", required_argument, NULL, 'p'},
    {"log", required_argument, NULL, 'l'},
    {"dir", required_argument, NULL, 'd'},
    {"tthreadnum", required_argument, NULL, 't'},
    {"maxconnect", required_argument, NULL, 'w'},
    {NULL, 0, NULL, 0}
};

/*show the help information*/
static void usage();

/*parse the argvs*/
void parse_argv(int argc, char* argv[],ew_init_config &);

#endif /* EW_GETOPT_UTIL_H_ */
