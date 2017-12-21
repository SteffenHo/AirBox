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
    http_route_to_array(request.route, p, false);

    int routeCount = string_utils_count_char(p, '/');

    lineType = 1;
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

void http_route_to_array(HttpStringArray<HTTP_ROUTE_MAX_PARTS, HTTP_ROUTE_MAX_PART_SIZE> &routeArray, char* buffer, bool routeToLower) {
  char *p = strtok(buffer, "/");

  while (p != NULL)
  {
    url_decode(p, p);

    if(routeToLower) {
      string_to_lower(p, p);
    }
    
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
  request.params.clear();
}

char get_method_type(const char* method_string) {
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

const char* http_get_status_message(unsigned int status_code) {
  switch(status_code) {
    case 200:
      return "OK";
    case 400:
      return "Bad Request";
    case 404:
      return "Not Found";
    case 500:
      return "Internal Server Error";
    default:
      return "Internal Server Error";
  }
}

void http_helper_loop() {
  WiFiClient client = server.available();
  if (client) {
    memset(linebuf, 0, sizeof(linebuf));
    
    charcount = 0;
    response.clear();
    http_clear_request(request, line_type);
    
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        linebuf[charcount] = c;
        charcount++;

        int requestEnded = (line_type > 1 && (request.body.getCurrentIndex() + charcount) >= request.body.content_length);
        if(requestEnded) {
          request.bodyReady = true;
          request.ready = true;
        }

        if(c == '\n' || requestEnded) {
          parse_http_request(request, linebuf, line_type);

          if(request.ready) {
            process_request(request, response);
          }
         
          memset(linebuf, 0, sizeof(linebuf));
          charcount=0;
        }
      }

      if(response.isReady()) {
        response.send(client);
        break;
      }
    }
    // give the web browser time to receive the data
    delay(1);

    // close the connection:
    client.stop();
  }
}

void process_request(HttpRequest &request, HttpResponse &response) {
  if(!router.process(request, response)) {
    response.statusCode = 404;
    response.end();
  }

  if(request.ready) {
    Serial.println("---------- REQUEST ----------");
    
    Serial.print("Route: ");
    request.route.print();

    Serial.print("Method-Type: ");
    Serial.println((int) request.method);

    Serial.println("Headers:");
    request.header.print();

    Serial.println("Body:");
    if(request.bodyReady) {
      Serial.println(request.body.getRaw());
    } else {
      Serial.println("-- no body --");
    }
  }
}


