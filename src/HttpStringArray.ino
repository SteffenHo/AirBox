#include <string.h>
#include "HttpStringArray.h"

template<int E, int L>
int HttpStringArray<E, L>::size() {
  return this->curIndex;
}

template<int E, int L>
char* HttpStringArray<E, L>::get(int index) {
  if(index > size()) {
    return NULL;
  }
  
  return this->data[index];
}

template<int E, int L>
bool HttpStringArray<E, L>::set(int index, char* data) {
  if(index > this->size() || index >= E) {
    return false;
  }

  int length = strlen(data);
  
  for(int i = 0; i <= length; i++) {
    this->data[index][i] = data[i];
  }

  return true;
}


template<int E, int L>
void HttpStringArray<E, L>::add(char* data) {
  if(this->set(this->curIndex, data)) {
    this->curIndex++;
  }
}

template<int E, int L>
void HttpStringArray<E, L>::clear() {
  this->curIndex = 0;
}

template<int E, int L>
void HttpStringArray<E, L>::print() {
  Serial.print("[");
  
  for(int i = 0, z = this->size(); i < z; i++) {
    Serial.print(this->get(i));

    if(i != z - 1) {
      Serial.print(", ");
    }
  }
  
  Serial.println("]");
}


