#include "HttpBody.h"

bool HttpBody::write(char* buffer) {
  int length = strlen(buffer) + 1;
  int new_length = this->data_index + length;

  if(new_length > MAX_BODY_SIZE) {
    return false;
  }
  
  for(int i = 0; i < length; i++) {
    this->data[this->data_index++] = buffer[i];
  }

  this->data_index--;
  
  return true;
}

void HttpBody::clear() {
  this->data[0] = 0;
}

const char* HttpBody::getRaw() {
  return this->data;
}

