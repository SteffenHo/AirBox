#include "http_helper.h"

void parse_http_request(struct http_request &request, char* buffer, int &lineType) {
  Serial.println(buffer);
  Serial.println(lineType);

  if(lineType == 0) {
    char *p = strtok(buffer, " "); // read http-method
    request.method = get_method_type(p);

    p = strtok(NULL, " "); // read route

    //char* routeArray = (char*) malloc(size_of(char*));
    //http_route_to_array(routeArray, p);

    int routeCount = string_utils_count_char(p, '/');
    http_string_array routeArray;
    routeArray.set(0, "Test");
    //routeArray.get(0) = "test";
    //routeArray.get(1) = "hi";
    
    Serial.print("Route-Count: ");
    Serial.println(routeCount);
    Serial.print("Route: ");
    Serial.println(p);

    Serial.print("Method-Type: ");
    Serial.println((int) request.method);
  } else if(lineType == 2) {
    
  }

  lineType++;
}

void http_route_to_array(char* routeArray, char* buffer) {
  char *p = strtok(buffer, " ");
  char *array[3];
  
  int i=0;

  while (p != NULL)
  {
      array[i++] = p;
      p = strtok (NULL, " ");
  }

  Serial.println("Parsed Route");

  for (i = 0; i < 3; ++i) {
      Serial.printf("%s\n", array[i]);
  }

  request.method = get_method_type(array[0]);

  Serial.print("Method-Type: ");
  Serial.println((int) request.method);
}

void http_clear_request(struct http_request &request) {
  request.method = HTTP_METHOD_UNKNOWN;
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

