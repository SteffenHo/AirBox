#ifndef _HTTP_HELPER_H
#define _HTTP_HELPER_H

#include "HttpStringArray.h"
#include "HttpBody.h"
#include "HttpHeader.h"

class HttpRequest {
  public:
    char method;
    HttpStringArray<HTTP_ROUTE_MAX_PARTS, HTTP_ROUTE_MAX_PART_SIZE> route;
    HttpStringArray<HTTP_ROUTE_MAX_PARTS, HTTP_ROUTE_MAX_PART_SIZE> params;
    HttpHeader header;
    HttpBody body;
    char ready = 0;
    char bodyReady = 0;
    char headerReady = 0;
};

#endif
