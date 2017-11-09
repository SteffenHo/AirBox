#ifndef _HTTP_HELPER_H
#define _HTTP_HELPER_H


#define HTTP_METHOD_UNKNOWN 0
#define HTTP_METHOD_GET 1
#define HTTP_METHOD_POST 2
#define HTTP_METHOD_DELETE 3
#define HTTP_METHOD_PUT 4
#define HTTP_METHOD_PATCH 5 
#define HTTP_METHOD_OPTIONS 6

struct http_request {
  char method;
};

class http_string_array {
  private:
    int pSize = 0;
    char** data;

  public:
    int size() {
      return this->pSize;
    };
  
    char* get(int index) {
      if(index > size()) {
        return NULL;
      }
  
      return this->data[index];
    };

    void set(int index, char* data) {
      
    };

    void add(char* data) {
      
    };
};

#endif
