#ifndef _HELPER_H
#define _HELPER_H

#include "avem.h"
#include "SDCardHelper.h"


char* createAvemString(const Avem &av ){
   char data[300];
   char idStr[10];
   int i = 0;
   
  //AvemConfig av_conf(18975, 23, 453,1);
  //Avem av(875,"Steffen", av_conf, 3);
  char *str = av.toJson();
  int jsonStrLen = strlen(str);
  itoa(av.getId(), idStr, 10); //nicht terminiert! daher loop
  int idStrLen = strlen(idStr);
  
 
  for(int j = 0;i<idStrLen; i++, j++){
    data[i] = idStr[j];
  }
  data[i++] = '|';
  for(int k = 0; i<idStrLen+jsonStrLen+2; i++, k++){
    data[i] = str[k];
  }
  data[i++] = 0;
  
  Serial.println(data);
  addAvemToDB(data);
  return data;
}





#endif

