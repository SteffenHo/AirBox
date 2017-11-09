#include "http_helper.h"

void parse_http_request(HttpRequest &request, char* buffer, int &lineType) {
  Serial.println(buffer);
  Serial.println(lineType);

  if(lineType == 0) {
    char *p = strtok(buffer, " "); // read http-method
    request.method = get_method_type(p);

    p = strtok(NULL, " "); // read route

    //char* routeArray = (char*) malloc(size_of(char*));
    http_route_to_array(request.route, p);

    int routeCount = string_utils_count_char(p, '/');
    
    Serial.print("Route-Count: ");
    Serial.println(routeCount);
    Serial.print("Route: ");
    Serial.println(p);

    Serial.print("Method-Type: ");
    Serial.println((int) request.method);
    Serial.println("Ended parsing line");
  } else if(lineType == 2) {
    
  }

  lineType++;
}

void http_route_to_array(HttpStringArray &routeArray, char* buffer) {
  char *p = strtok(buffer, "/");
  int i=0;

  while (p != NULL)
  {
    url_decode(p, p);
    routeArray.add(p);
    p = strtok (NULL, "/");
  }

  Serial.println("Parsed Route");
}

void http_clear_request(HttpRequest &request) {
  request.method = HTTP_METHOD_UNKNOWN;
  request.route.clear();
}

char get_method_type(char* method_string) {
  if(!strcmp(method_string, "GET")) {
    return HTTP_METHOD_GET;
  }

  if(!strcmp(method_string, "OPTIONS")) {
    return HTTP_METHOD_OPTIONS;
  }

  if(!strcmp(method_string, "POST")) {
    return HTTP_METHOD_POST;
  }

  if(!strcmp(method_string, "DELETE")) {
    return HTTP_METHOD_DELETE;
  }

  if(!strcmp(method_string, "PATCH")) {
    return HTTP_METHOD_PATCH;
  }

  if(!strcmp(method_string, "PUT")) {
    return HTTP_METHOD_PUT;
  }

  return HTTP_METHOD_UNKNOWN;
}

