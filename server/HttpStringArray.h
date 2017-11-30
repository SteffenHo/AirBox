#ifndef _HTTP_STRING_ARRAY_H
#define _HTTP_STRING_ARRAY_H

#define REALLOC_STEPS 4

template<int E, int L>
class HttpStringArray {
  private:
    int curIndex = 0;
    char data[E][L];

  public:
    char* get(int index);
    bool set(int index, char* data);
    void add(char* data);
    void clear();
    
    int size();
    void print();
};

#endif
