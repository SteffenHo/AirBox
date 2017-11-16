#ifndef _HTTP_HEADER_H
#define _HTTP_HEADER_H

#define MAX_HEADER_ENTRIES 25
#define MAX_HEADER_KEY_LENGTH 64
#define MAX_HEADER_VALUE_LENGTH 512

class HttpHeaderEntry {
  public:
    HttpHeaderEntry();
    HttpHeaderEntry(const char* p_name, const char* p_value);
    int set(const char* p_name, const char* p_value);
    const char* getValue();
    const char* getName();
    void print();
  private:
    char name[MAX_HEADER_KEY_LENGTH];
    char value[MAX_HEADER_VALUE_LENGTH];
    char empty;
};

class HttpHeader {
  public:
    int set(const char* p_name, const char* p_value);
    const char* get(const char* p_name);
    int getIndex(const char* p_name);
    void clear();
    void print();
  private:
    int size;
    HttpHeaderEntry entries[MAX_HEADER_ENTRIES];
};

#endif
