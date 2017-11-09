#include "HttpStringArray.h"

void HttpStringArray::updateSize(int p_size) {
  this->data = (char**) realloc(this->data, p_size * sizeof(char*));
  this->array_size = p_size;
}

HttpStringArray::HttpStringArray(int p_size) {
  Serial.println("construct string_array");
  this->updateSize(p_size);
}

int HttpStringArray::size() {
  return this->z_size;
}

char* HttpStringArray::get(int index) {
  if(index > size()) {
    return NULL;
  }
  
  return this->data[index];
}

bool HttpStringArray::set(int index, char* data) {
  if(index > this->size()) {
    return false;
  }

  this->data[index] = data;
}

void HttpStringArray::add(char* data) {
  this->updateSize(((this->size() / REALLOC_STEPS) * REALLOC_STEPS) + REALLOC_STEPS );
  this->data[this->z_size++] = data;
}

void HttpStringArray::clear() {
  this->updateSize(0);
  this->z_size = 0;
}

void HttpStringArray::print() {
  Serial.print("[");

  for(int i = 0, z = this->size(); i < z; i++) {
    Serial.print(this->get(i));

    if(i != z - 1) {
      Serial.print(", ");
    }
  }
  
  Serial.println("]");
}

HttpStringArray::~HttpStringArray() {
  Serial.println("destruct string_array");
}


