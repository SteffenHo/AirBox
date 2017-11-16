#ifndef _HTTP_RESPONSE_H
#define _HTTP_RESPONSE_H

#include "HttpHeader.h"

#define MAX_RESPONSE_BODY_SIZE 2048

class HttpResponse {
  public:
    unsigned int statusCode = 500;
    HttpHeader header;
    char body[MAX_RESPONSE_BODY_SIZE];
    char ready = 0;
    void send(WiFiClient &client, HttpResponse &p_response);
    void clear();
};

#endif
