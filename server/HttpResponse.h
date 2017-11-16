#ifndef _HTTP_RESPONSE_H
#define _HTTP_RESPONSE_H

#include "HttpHeader.h"

class HttpResponse {
  public:
    unsigned int statusCode = 500;
    HttpHeader header;
    char ready = 0;
    void send(WiFiClient &client, HttpResponse &p_response);
    void clear();
};

#endif
