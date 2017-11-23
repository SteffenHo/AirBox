#include "HttpResponse.h"

void HttpResponse::send(WiFiClient &client) {
  Serial.println("client send");
  // set HTTP-protocol, status-code and status-message
  client.print("HTTP/1.1 ");
  client.print(this->statusCode);
  client.print(' ');
  client.println(http_get_status_message(p_response.statusCode));

  this->header.set("Content-Type", "application/json");
  this->header.set("Content-Length", strlen(this->body));
  this->header.set("Connection", "close");

  // set headers
  for(int i = 0, j = response.header.getSize(); i < j; i++) {
    const HttpHeaderEntry* entry = this->header.get(i);
    client.print(entry->getName());
    client.print(": ");
    client.println(entry->getValue());
  }

  // start body
  client.println();
  
  client.println(this->body);

/*
  client.println("<!DOCTYPE HTML><html><head>");
  client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"></head>");
  client.println("<h1>ESP32 - Web Server</h1>");
  client.println("<p>LED #1 <a href=\"on1\"><button>ON</button></a>&nbsp;<a href=\"off1\"><button>OFF</button></a></p>");
  client.println("<p>LED #2 <a href=\"on2\"><button>ON</button></a>&nbsp;<a href=\"off2\"><button>OFF</button></a></p>");
  client.println("</html>");
  */
}

void HttpResponse::clear() {
  this->ready = 0;
  this->header.clear();
  this->statusCode = 500;
}

