#include "HttpHeader.h"

const char* HttpHeader::get(const char* p_name) {
  int index = getIndex(p_name);

  if(index < 0 || index >= MAX_HEADER_ENTRIES) {
    return 0;
  }

  return entries[index].getValue();
}

const HttpHeaderEntry* HttpHeader::get(int index) {
  if(index < 0 || index >= MAX_HEADER_ENTRIES) {
    return NULL;
  }

  return &entries[index];
}

int HttpHeader::getIndex(const char* p_name) {
  for(int i = 0; i < this->size; i++) {
    if(strcasecmp(p_name, entries[i].getName()) == 0) {
      return i;
    }
  }

  return -1;
}

int HttpHeader::set(const char* p_name, const char* p_value) {
  int index = getIndex(p_name);
  
  if(index >= 0) {
    return entries[index].set(p_name, p_value);
  }

  int success = entries[this->size++].set(p_name, p_value);

  if(!success) {
    this->size--;
  }

  return success;
}

void HttpHeader::clear() {
  this->size = 0;
}

void HttpHeader::print() {
  Serial.println('[');
  
  for(int i = 0; i < this->size; i++) {
    Serial.print("  ");
    this->entries[i].print();
  }

  Serial.println(']');
}

int HttpHeader::getSize() const {
  return this->size;
}

HttpHeaderEntry::HttpHeaderEntry() {
  this->name[0] = 0;
  this->value[0] = 0;
  this->empty = 1;
}

HttpHeaderEntry::HttpHeaderEntry(const char* p_name, const char* p_value) {
  set(p_name, p_value);
}

int HttpHeaderEntry::set(const char* p_name, const char* p_value) {
  if(p_name == NULL || p_value == NULL) {
    return 0;
  }
  
  if(strlen(p_name) >= MAX_HEADER_KEY_LENGTH) {
    return 0;
  }

  if(strlen(p_value) >= MAX_HEADER_VALUE_LENGTH) {
    return 0;
  }

  strcpy(this->name, p_name);
  string_copy_header(this->value, p_value);
  this->empty = 0;

  return 1;
}

const char* HttpHeaderEntry::getName() const {
  return this->name;
}

const char* HttpHeaderEntry::getValue() const {
  return this->value;
}

void HttpHeaderEntry::print() {
  Serial.print('{');
  Serial.print(getName());
  Serial.print(':');
  Serial.print(getValue());
  Serial.println('}');
}

