
#include <SPI.h>
#include <SD.h>
#include "avem.h"
#define SEPARATOR '|'
#define AVEM_STR_SIZE 300
#define ID_STR_SIZE 10

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  if (!SD.begin(D8 )) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

}

File DB;

void loop() {
  // put your main code here, to run repeatedly:

}

void serialEvent() {
  
  char ch = Serial.read();
  if(ch == 119){ //w
    //createAvemString();
  }
  else{
    Serial.println("read");
    readFile();
  }
}
void readFile(){
  DB = SD.open("TEST.TXT");
  if (DB) {
    // read from the file until there's nothing else in it:
    while (DB.available()) {
      String buffer = DB.readStringUntil('\n');
      Serial.println(buffer);
      Serial.println("newLine");
      setAvemFromFile(buffer);
      //Serial.write(DB.read());
    }
    // close the file:
    DB.close();
  } else {
    // if the file didn't open, 
    Serial.print(" an error");
    //Serial.println("error opening test.txt");
  }
}

Avem setAvemFromFile(String fileString){
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
  Serial.println(id);
  Serial.println(avemStr);
}


