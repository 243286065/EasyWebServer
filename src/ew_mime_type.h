/*
 * ew_mime_type.h
 *
 *  Created on: 2016-8-4
 *      Author: lab401
 *    Function:	提供文件格式类型定义
 */

#ifndef EW_MIME_TYPE_H_
#define EW_MIME_TYPE_H_

#include <map>
#include "util.h"

class ew_mime_type_class {
public:
	int size;
	std::map<const char*, const char*> types;
	ew_mime_type_class() :
		size(0) {
	}
	const char* findType(char*, int);
};

static ew_mime_type_class mime_type;
static void init_types();

ew_mime_type_class& get_mime_types();


#endif /* EW_MIME_TYPE_H_ */
