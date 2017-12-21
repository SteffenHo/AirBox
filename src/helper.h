#ifndef _HELPER_H
#define _HELPER_H

#include "avem.h"
#include "SDCardHelper.h"

void createAvemString(const Avem &av ){
   char data[AVEM_SERIALIZE_BUFFER_SIZE];
   char idStr[10];
   int i = 0;

  char str[AVEM_SERIALIZE_BUFFER_SIZE];
  av.toJson(str, AVEM_SERIALIZE_BUFFER_SIZE);
  
  int jsonStrLen = strlen(str);
  itoa(av.getId(), idStr, 10);
  int idStrLen = strlen(idStr);
 
  for(int j = 0;i<idStrLen; i++, j++){
    data[i] = idStr[j];
  }
  
  data[i++] = '|';
  
  for(int k = 0; i<idStrLen+jsonStrLen+2; i++, k++){
    data[i] = str[k];
  }
  data[i++] = 0;
  
  addAvemToDB(data);
}





#endif

