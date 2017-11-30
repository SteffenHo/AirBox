#ifndef _HTTP_RESPONSE_H
#define _HTTP_RESPONSE_H

#include "HttpHeader.h"

class HttpResponse {
  protected:
    bool ready = false;
  public:
    unsigned int statusCode = RESPONSE_DEFAULT_STATUS_CODE;
    HttpHeader header;
    char body[MAX_RESPONSE_BODY_SIZE];
    void send(WiFiClient &client);
    void clear();
    void end();
    bool isReady();
};

#endif
