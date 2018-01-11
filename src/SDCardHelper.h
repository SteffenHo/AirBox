#ifndef _SD_CARD_HELPER_H
#define _SD_CARD_HELPER_H

#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include <RCSwitch.h>

RCSwitch sender = RCSwitch();
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

#ifdef __DEV__
      Serial.println(tempId);
#endif
      
      if(tempId> mainId){
        mainId = tempId;
      }
    }
    
    // close the file:
    DB.close();
    return mainId;
  } else {
    Serial.print("cannot open DB");
    mainId = 1; // danger!
    return 0;
  }
}

bool initSD(){
  if (SD.begin()) {
#ifdef __DEV__
      Serial.println("initialization done.");
      Serial.printf("Total space: %lluMB\n", SD.totalBytes() / (1024 * 1024));
      Serial.printf("Used space: %lluMB\n", SD.usedBytes() / (1024 * 1024));
#endif
      getMainId();
      return true;
    }

#ifdef __DEV__
    Serial.println("initialization failed!");
#endif

  return false;
}

bool addAvemToDB(const char* string){
  DB = SD.open(DB_FILE_NAME, FILE_APPEND);

  // if the file opened okay, write to it:
  if (DB) {
#ifdef __DEV__
    Serial.println(string);
#endif

    DB.println(string);
    // close the file:
    DB.close();
    return true;
  } else {
    // if the file didn't open, print an error:
#ifdef __DEV__
    Serial.println("error opening ");
#endif

    return false;
  }
}

void sendAvem(const Avem &av){
  sender.enableTransmit(SEND_PIN);

  sender.setProtocol(av.getProtocol());
  sender.setPulseLength(av.getPulseLength());
  sender.send(av.getDecimal(), av.getBitLength());
  //sender.sendTriState(av.getTriState());
}

Avem setAvemFromFile(String fileString, int pId){
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
  if(id != pId){
    return Avem::EMPTY;
  }
  
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(avemStr);
   
  int jsonId = root["id"];
  String jsonName = root["name"];
  int jsonDeviceId = root["deviceId"];
  int jsonConfigDecimal = root["config"]["decimal"];
  int jsonConfigBitLength = root["config"]["bitLength"];
  int jsonConfigPulseLength = root["config"]["pulseLength"];
  int jsonConfigProtocol = root["config"]["protocol"];

  AvemConfig av_conf(jsonConfigDecimal, jsonConfigBitLength, jsonConfigPulseLength,jsonConfigProtocol);
  Avem av(jsonDeviceId, jsonName.c_str(), av_conf, jsonDeviceId);

  //sendAvem(av);
  return av;
}

bool readFileToString(char* body) {
  DB = SD.open(DB_FILE_NAME);
  if (DB) {
    // read from the file until there's nothing else in it:
    
    while (DB.available()) {
      String buffer = DB.readStringUntil('\n');
      
      bool afterSeparator = false;
      int notAvemStrCount = 0;
      
      char avemStr[AVEM_STR_SIZE];
      for(int i = 0; buffer[i]; i++){
        if(!afterSeparator && buffer[i] == SEPARATOR){
          afterSeparator = true;
          continue;
        }
        
        if(!afterSeparator){
          notAvemStrCount++;
        } else {
          avemStr[(i-notAvemStrCount)] = buffer[i];
          avemStr[((i+1)-notAvemStrCount)] = 0;
        }

        strcpy(avemStr, body);
      }
    }

    return true;
  } else {
    // if the file didn't open
#ifdef __DEV__
    Serial.print("an error occured while reading file");
#endif
  }

  return false;
}

Avem readFile(int id){
  DB = SD.open(DB_FILE_NAME);
  if (DB) {
    // read from the file until there's nothing else in it:
    
    while (DB.available()) {
      String buffer = DB.readStringUntil('\n');
      Avem found = setAvemFromFile(buffer, id);

      if(&found != 0 && !found.isEmpty()) {
        // close the file:
        DB.close();
        
        return found;
      }
    }
  } else {
    // if the file didn't open
#ifdef __DEV__
    Serial.print("an error occured while reading file");
#endif
  }

  return Avem::EMPTY;
}



#endif
