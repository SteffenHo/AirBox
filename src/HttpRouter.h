#include "http_helper.h"
#include "HttpResponse.h"

#ifndef _HTTP_ROUTER_H
#define _HTTP_ROUTER_H

typedef void (*http_route_callback)(HttpRequest &request, HttpResponse &response);

class HttpRoute {
  private:
    HttpStringArray<HTTP_ROUTE_MAX_PARTS, HTTP_ROUTE_MAX_PART_SIZE> routeArray;
    char method = HTTP_METHOD_GET; 
    http_route_callback callback = NULL;
  public:
    int setRoute(const char* route);
    void setMethod(const char* method);
    void setCallback(http_route_callback callback);
    void call(HttpRequest &request, HttpResponse &response);
    bool validateAndCall(HttpRequest &request, HttpResponse &response);
};

class HttpRouter {
  private:
    HttpRoute routes[HTTP_ROUTER_MAX_ROUTES];
    int routeIndex = 0;
  public:
  int routeIndex2 = 1;
    int add(HttpRoute &route);
    bool process(HttpRequest &request, HttpResponse &response);
};

#endif
