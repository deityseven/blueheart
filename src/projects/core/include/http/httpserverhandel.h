#ifndef HTTPSERVERHANDLE_H
#define HTTPSERVERHANDLE_H

#include <http/httplib.h>

class HttpServerHandle
{
public:
	virtual void operator()(const httplib::Request& request, httplib::Response& response) = 0;
};

#endif // !CONFIG_FILE_H