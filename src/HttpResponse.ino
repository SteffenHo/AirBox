#include "HttpResponse.h"

void HttpResponse::send(WiFiClient &client) {
  // set HTTP-protocol, status-code and status-message
  client.print("HTTP/1.1 ");
  client.print(this->statusCode);
  client.print(' ');
  client.println(http_get_status_message(this->statusCode));

  if(this->header.getIndex("Content-Type") == -1) {
    this->header.set("Content-Type", "application/json");
  }
  
  this->header.set("Content-Length", strlen(this->body));
  this->header.set("Connection", "close");
  this->header.set("Access-Control-Allow-Origin", CORS_ALLOWED_ORIGINS);
  this->header.set("Access-Control-Allow-Methods", CORS_ALLOWED_METHODS);
  this->header.set("Access-Control-Allow-Headers", CORS_ALLOWED_HEADERS);

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

  // give the web browser time to receive the data
  delay(1);
  
  // close the connection:
  client.stop();
}

void HttpResponse::clear() {
  this->ready = false;
  this->header.clear();
  this->body[0] = 0;
  this->statusCode = 500;
}

void HttpResponse::end() {
  this->ready = true;
}

bool HttpResponse::isReady() {
  return this->ready;
}

