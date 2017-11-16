#include "http_helper.h"
#include "HttpHeader.h"

#define CHAR_NEW_LINE 13

char* body_buffer;
bool body_buffer_in_string;

void parse_http_request(HttpRequest &request, char* buffer, int &lineType) {
  if(lineType == 0) {
    char *p = strtok(buffer, " "); // read http-method
    request.method = get_method_type(p);

    p = strtok(NULL, " "); // read route

    //char* routeArray = (char*) malloc(size_of(char*));
    http_route_to_array(request.route, p);

    int routeCount = string_utils_count_char(p, '/');

    lineType = 1;
    Serial.print("Route-Count: ");
    Serial.println(routeCount);
    Serial.print("Route: ");
    Serial.println(p);

    Serial.print("Method-Type: ");
    Serial.println((int) request.method);
    Serial.println("Ended parsing line");
  } else if(lineType == 1) {
    if(buffer[0] == CHAR_NEW_LINE) {
      request.headerReady = 1;

      const char* content_length = request.header.get("content-length");
      if(content_length && content_length[0] != '0') {
        request.body.content_length = (int) strtol(content_length, (char **)NULL, 10);
      } else {
        request.ready = true;
      }
      
      lineType = 2;
      return;
    }

    char *p = strtok(buffer, ":");
    char *p2 = strtok(NULL, ":");

    request.header.set(p, p2);
  } else if(lineType == 2) {
    request.body.write(buffer);
  }
}

void http_route_to_array(HttpStringArray &routeArray, char* buffer) {
  char *p = strtok(buffer, "/");

  while (p != NULL)
  {
    url_decode(p, p);
    string_to_lower(p, p);
    routeArray.add(p);
    p = strtok (NULL, "/");
  }
}

void http_clear_request(HttpRequest &request, int &p_line_type) {
  p_line_type = 0;
  request.ready = false;
  request.method = HTTP_METHOD_UNKNOWN;
  request.route.clear();
  request.body.clear();
  request.header.clear();
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
