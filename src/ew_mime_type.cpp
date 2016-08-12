/*
 * ew_mime_type.cpp
 *
 *  Created on: 2016-8-4
 *      Author: lab401
 */
#include "ew_mime_type.h"

static void init_types() {
	if (mime_type.size == 0) {
		mime_type.types.insert(std::make_pair(".html", "text/html"));
		mime_type.types.insert(std::make_pair(".xml", "text/xml"));
		mime_type.types.insert(
				std::make_pair(".xhtml", "application/xhtml+xml"));
		mime_type.types.insert(std::make_pair(".txt", "text/plain"));
		mime_type.types.insert(std::make_pair(".rtf", "application/rtf"));
		mime_type.types.insert(std::make_pair(".pdf", "application/pdf"));
		mime_type.types.insert(std::make_pair(".word", "application/msword"));
		mime_type.types.insert(std::make_pair(".png", "image/png"));
		mime_type.types.insert(std::make_pair(".gif", "image/gif"));
		mime_type.types.insert(std::make_pair(".jpg", "image/jpg"));
		mime_type.types.insert(std::make_pair(".jpeg", "image/jpeg"));
		mime_type.types.insert(std::make_pair(".au", "audio/basic"));
		mime_type.types.insert(std::make_pair(".mpeg", "video/mpeg"));
		mime_type.types.insert(std::make_pair(".mpg", "video/mpeg"));
		mime_type.types.insert(std::make_pair(".avi", "video/x-msvideo"));
		mime_type.types.insert(std::make_pair(".gz", "application/x-gzip"));
		mime_type.types.insert(std::make_pair(".tar", "application/x-tar"));
		mime_type.types.insert(std::make_pair(".css", "text/css"));
		mime_type.size = mime_type.types.size();
	}
}

const char* ew_mime_type_class::findType(char* str, int len) {
	convert_lowerCase(str, len);
	std::map<const char*, const char*>::iterator f = types.find(str);
	if (f == types.end())
		return types[".txt"];
	else
		return f->second;
}

ew_mime_type_class& get_mime_types() {
	init_types();
	return mime_type;
}

