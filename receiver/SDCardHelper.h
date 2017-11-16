#ifndef _SD_CARD_HELPER_H
#define _SD_CARD_HELPER_H
#define AVEMFILE "avem.txt"
#define JSON_LENGTH 200
#include "avem.h"
#include <SPI.h>
#include <SD.h>

File DB;


void initSD(){
  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
}


void addAvemToDB(Avem data){
  DB = SD.open(AVEMFILE, FILE_WRITE);

  // if the file opened okay, write to it:
  if (DB) {
     int id = data.getId();
    // String jsonStr = data.toJson();
    String saveString = prepareAvemDate(id, data);
    Serial.print(saveString);
    DB.println(saveString);
    // close the file:
    DB.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening ");
    Serial.println("AVEMFILE");
  }
}

void readFile(){
  DB = SD.open(AVEMFILE);
  if (DB) {
    Serial.println(AVEMFILE);

    // read from the file until there's nothing else in it:
    while (DB.available()) {
      Serial.write(DB.read());
    }
    // close the file:
    DB.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}



#endif

