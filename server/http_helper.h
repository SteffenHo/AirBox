#ifndef _HTTP_HELPER_H
#define _HTTP_HELPER_H

#include "HttpStringArray.h"

#define HTTP_METHOD_UNKNOWN 0
#define HTTP_METHOD_GET 1
#define HTTP_METHOD_POST 2
#define HTTP_METHOD_DELETE 3
#define HTTP_METHOD_PUT 4
#define HTTP_METHOD_PATCH 5 
#define HTTP_METHOD_OPTIONS 6

class HttpRequest {
  public:
    char method;
    HttpStringArray parameter;
};

#endif
