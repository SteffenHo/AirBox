#include "http_helper.h"
#include "WifiClientHandler.h"
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

WifiClientHandler* clientHandlers[MAX_CLIENTS] = { NULL };
void http_helper_loop(void(*callback)(HttpRequest&, HttpResponse&)) {
  WiFiClient newClient = server.available();
  if (newClient) {
    Serial.println("new client");
    // Find the first unused space
    for (int i=0 ; i < MAX_CLIENTS ; ++i) {
        if (NULL == clientHandlers[i]) {
            clientHandlers[i] = new WifiClientHandler(newClient);
            break;
        }
     }
  }

    // Check whether each client has some data
  for (int i=0 ; i<MAX_CLIENTS ; ++i) {
    // If the client is in use, and has some data...
    if (clientHandlers[i] != NULL && clientHandlers[i]->getClient() != NULL) {
      WifiClientHandler* clientHandler = clientHandlers[i];
      WiFiClient* client = clientHandler->getClient();
      
      if (!client->connected() || clientHandler->shouldConnectionClose()) {
        client->flush();
        client->stop();
        delete clientHandlers[i];
        clientHandlers[i] = NULL;
        
        return;
      }

      if(clientHandler->request.ready) {
        Serial.println(">>>>REQUEST READY<<<<<<");

        process_request(clientHandler->request, clientHandler->response);
      }

      if(clientHandler->response.isReady()) {
        clientHandler->response.send(*client);

        clientHandler->response.clear();
        client->flush();
        client->stop();
        delete clientHandlers[i];
        clientHandlers[i] = NULL;
        
        return;
      }
      
      if (client->available() ) {
        // Read the data 
        char newChar = client->read();

        clientHandler->linebuf[clientHandler->charcount++] = newChar;

        if(newChar == '\n' || newChar == '\r') {
          clientHandler->linebuf[clientHandler->charcount] = 0;
          parse_http_request(clientHandler->request, clientHandler->linebuf, clientHandler->lineType);
         
          memset(clientHandler->linebuf, 0, sizeof(clientHandler->linebuf));
          clientHandler->charcount=0;
        }
      }
    }
  }
}

void process_request(HttpRequest &request, HttpResponse &response) {
  if(!router.process(request, response)) {
    response.body[0] = 0;
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


