#ifndef _SD_CARD_HELPER_H
#define _SD_CARD_HELPER_H
#define SEPARATOR '|'
#define AVEM_STR_SIZE 300
#define ID_STR_SIZE 10
#define DB_FILE_NAME "AVEM30.TXT"

#include <SPI.h>
#include <SD.h>
#include <RCSwitch.h>

RCSwitch sender = RCSwitch();
//#include "helper.h"
File DB;
int mainId = -1;

int getIdFromString(String fileString){
  bool afterSeparator = false;
  char idStr[ID_STR_SIZE];
  int notAvemStrCount = 0;
  
  char avemStr[AVEM_STR_SIZE];
  for(int i = 0; fileString[i]; i++){
    if(!afterSeparator && fileString[i] == SEPARATOR){
      afterSeparator = true;
      notAvemStrCount++;
      continue;
    }
    if(!afterSeparator){
      idStr[i] = fileString[i];
      idStr[(i+1)] = 0;
      notAvemStrCount++;
    }
    else{
      avemStr[(i-notAvemStrCount)] = fileString[i];
      avemStr[((i+1)-notAvemStrCount)] = 0;
    }
  }
  int id = atoi(idStr);
  return id;
}

int getMainId(){
  DB = SD.open(DB_FILE_NAME);
  if (DB) {
    while (DB.available() ) {
      String buffer = DB.readStringUntil('\n');
      int tempId = getIdFromString(buffer);
      Serial.println(tempId);
      if(tempId> mainId){
        mainId = tempId;
      }
      //Serial.write(DB.read());
    }
    // close the file:
    DB.close();
    return mainId;
  } else {
    Serial.print(" an error");
    return -1;
  }
}
