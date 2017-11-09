#ifndef _HTTP_STRING_ARRAY_H
#define _HTTP_STRING_ARRAY_H

class HttpStringArray {
  private:
    int z_size = 0;
    int array_size = 0;
    char** data = NULL;

    void updateSize(int p_size);

  public:
    HttpStringArray(int p_size = 0);
    ~HttpStringArray();
    
    char* get(int index);
    bool set(int index, char* data);
    void add(char* data);
    void clear();
    
    int size();
    void print();
};

#endif
