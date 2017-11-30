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

void initSD(){
  Serial.println("begin");
  for(int i = 0; i< 20; i++){
    if (SD.begin(D8 )) {
      Serial.println("initialization done.");
      getMainId();
      return;
    }
    Serial.println("initialization failed!");
  }
  
}

void addAvemToDB(const char* string){
  Serial.println("save to DB");
 // Serial.println(string);

  DB = SD.open(DB_FILE_NAME, FILE_WRITE);

  // if the file opened okay, write to it:
  if (DB) {     
    Serial.println(string);
    DB.println(string);
    // close the file:
    DB.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening ");

  }
}

void sendAvem(const Avem &av){
  sender.enableTransmit(D2);  // An Pin 3

  sender.setProtocol(av.getProtocol());
  sender.setPulseLength(av.getPulseLength());
   sender.sendTriState(av.getTriState());
}

bool setAvemFromFile(String fileString, int pId){
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
  if(id!= pId){
    return false;
  }
  Serial.println(id);
  Serial.println(avemStr);
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(avemStr);

   
   int jsonId = root["id"];
   String jsonName = root["name"];
   int jsonDeviceId =  root["deviceId"];
   int jsonConfigDecimal =  root["config"]["decimal"];
   int jsonConfigBitLength =  root["config"]["bitLength"];
   int jsonConfigPulseLength = root["config"]["pulseLength"];
   int jsonConfigProtocol = root["config"]["protocol"];

   AvemConfig av_conf(jsonConfigDecimal, jsonConfigBitLength, jsonConfigPulseLength,jsonConfigProtocol);
   Avem av(jsonDeviceId,"default", av_conf, jsonDeviceId);
    
  sendAvem(av);
  return true;
}

bool readFile(int id){
  DB = SD.open(DB_FILE_NAME);
  if (DB) {
    // read from the file until there's nothing else in it:
    bool found = false;
    while (DB.available() && !found) {
      String buffer = DB.readStringUntil('\n');
      //Serial.println(buffer);
      //Serial.println("newLine");
      found = setAvemFromFile(buffer, id);
      //Serial.write(DB.read());
    }
    // close the file:
    DB.close();
  } else {
    // if the file didn't open, 
    Serial.print(" an error");
    //Serial.println("error opening test.txt");
  }
  return true;
}



#endif
