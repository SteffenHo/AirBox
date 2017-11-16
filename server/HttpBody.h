#ifndef _HTTP_BODY_H
#define _HTTP_BODY_H

#define MAX_BODY_SIZE 2024

class HttpBody {
  private:
    char data[MAX_BODY_SIZE] = "";
    int data_index = 0;
  public:
    bool write(char* buffer);
    void clear();
    const char* getRaw();
    int getCurrentIndex();
    int content_length = 0;
};

#endif
