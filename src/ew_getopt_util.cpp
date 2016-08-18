/*
 * ew_getopt_util.cpp
 *
 *  Created on: 2016-8-4
 *      Author: lab401
 */

#include "ew_getopt_util.h"
#include <stdio.h>
#include <stdlib.h>

#include "util.h"
#include "ew_exit_status.h"
/*show the help information*/
static void usage() {
	fprintf(stderr, "easyweb [option]... \n"
		"   -c|--conf    Specify config file. Default ./easyweb.conf . \n"
		"   -?|-h|--help    Get help information. \n"
		"   -v|-V|--version    Show the program version. \n"
		"   -p|-P|--port    Set the listen port of web server.  Default 8080. \n"
		"   -l|-L|--log     Set the log file path. Default log/log.txt. \n"
		"   -d|-D|--dir     Set the web root dir path. Default web/ . \n"
		"   -t|-T|--threadnum   Set the threadpool size. Default 10. \n"
		"   -w|-W|--maxconnect  Set the max size of the socket connet wait queue. \n");
}
/*parse the argvs*/
void parse_argv(int argc, char* argv[], ew_init_config& conf_argv) {
	int opt = 0;
	int options_index = 0;
	/*
	 if (argc == 1) {
	 usage();
	 exit(0);
	 }*/
	while ((opt = getopt_long(argc, argv, "vVc:?hp:P:l:L:d:D:t:T:w:W:",
			long_options, &options_index)) != -1) {
		switch (opt) {
		case 0:
			break;
		case 'c':
			conf_argv.set_conf_file(optarg);
			printf("conf:%s\n", optarg);
			break;
		case 'v':
		case 'V':
			showVersion();
			exit(EW_EXIT_OK);
		case 'h':
		case '?':
			usage();
			exit(EW_EXIT_OK);
		case 'p':
		case 'P':
			conf_argv.set_port(atoi(optarg));
			break;
		case 'l':
		case 'L':
			conf_argv.set_log_file(optarg);
			break;
		case 'd':
		case 'D':
			conf_argv.set_root_dir(optarg);
			break;
		case 't':
		case 'T':
			conf_argv.set_threadnum(atoi(optarg));
			break;
		case 'w':
		case 'W':
			conf_argv.set_maxConnect(atoi(optarg));
			break;
		}
	}

	if (optind < argc) {
		log_error("non-option ARGV-elements: ");
		while (optind < argc)
			log_error(argv[optind++]);
		exit(EW_EXIT_OPT_ERR);
	}
}

