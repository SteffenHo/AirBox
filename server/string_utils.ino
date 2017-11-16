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

void string_copy_header(char* new_string, const char* string) {
  int length = strlen(string);
  
  for(int i = 0, j = 0; i <= length; i++) {
    if(string[i] == '\n') {
      continue;
    }

    if(j == 0 && string[i] == ' ') {
      continue;
    }

    new_string[j++] = string[i];
  }
}

