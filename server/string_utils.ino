int string_utils_count_char(const char* charArray, char search) {
  int i = 0, p = 0;
  
  while(charArray[p]) {
    if(charArray[p] == search) {
      i++;
    }

    p++;
  }

  return i;
}

