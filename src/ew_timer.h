/*
 * ew_timer.h
 *
 *  Created on: 2016-8-6
 *      Author: lab401
 */

#ifndef EW_TIMER_H_
#define EW_TIMER_H_

#define TIMEOUT_DEFAULT_EXPIRE		500	/*ms*/
#define TIMEOUT_DEFAULT_MARK		-1

typedef void (*timer_handler_func)(int fd);

typedef struct ew_timer_node_s {
	size_t key; //time value

	timer_handler_func handler;
} ew_timer_node;

int ew_timer_init();

/*find the last time*/
size_t ew_find_timer();

/*update timer*/
void ew_timer_update();

#endif /* EW_TIMER_H_ */
