#include "HttpRouter.h"

int HttpRouter::add(HttpRoute &route) {
  if(this->routeIndex >= HTTP_ROUTER_MAX_ROUTES) {
    return 0;
  }
  
  this->routes[this->routeIndex++] = route;
}

int HttpRoute::setRoute(const char* route) {
  if(strlen(route) >= HTTP_ROUTER_ROUTE_BUFFER) {
    return 0;
  }
  
  char route_buffer[HTTP_ROUTER_ROUTE_BUFFER];
  strcpy(route_buffer, route);

  char *p = strtok(route_buffer, "/");

  while (p != NULL)
  {
    url_decode(p, p);
    string_to_lower(p, p);
    this->routeArray.add(p);
    p = strtok (NULL, "/");
  }

  this->routeArray.print();
  
  return 1;
}

void HttpRoute::setCallback(http_route_callback callback) {
  this->callback = callback;
}

void HttpRoute::call(HttpRequest &request, HttpResponse &response) {
  this->callback(request, response);
}

bool HttpRoute::validateAndCall(HttpRequest &request, HttpResponse &response) {
  int route_size = this->routeArray.size();
  
  if(route_size > request.route.size()) {
    return 0;
  }
    
  for(int i = 0; i < route_size; i++) {
    if(this->routeArray.get(i)[0] == ':') {
      request.params.add(request.route.get(i));
      continue;
    }

    char* requestRoute = request.route.get(i);
    char* route = this->routeArray.get(i);
    
    int requestRouteLength = strlen(requestRoute);
    int routeLength = strlen(route);
    
    if(requestRouteLength != routeLength) {
      return 0;
    }
    
    for(int j, z = requestRouteLength; j < z; j++) {
      if(tolower(requestRoute[j]) != route[j]) {
        return 0;
      }
    }
  }

  this->call(request, response);

  return 1;
}

bool HttpRouter::process(HttpRequest &request, HttpResponse &response) {
  Serial.println("Start processing routing.");

  int route_size = this->routeIndex;
  
  for(int i = 0; i < route_size; i++) {
    if(this->routes[i].validateAndCall(request, response)) {
      return 1;
    }
  }

  return 0;
}

