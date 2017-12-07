
/*#include <SPI.h>
#include <SD.h>*/
#include "avem.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  /*if (!SD.begin(4 )) {
    Serial.println("initialization failed!");
    return;
  }*/
  Serial.println("initialization done.");

}

//File DB;

void loop() {
  // put your main code here, to run repeatedly:

}

void serialEvent() {
  
  char ch = Serial.read();
  if(ch == 119){ //w
    createAvemString();
  }
  else{
    Serial.println("read");
    //readFile();
  }
}

char* createAvemString(){
   char data[300];
   char idStr[10];
   int i = 0;
   
  AvemConfig av_conf(18975, 23, 453,1);
  Avem av(875,"Steffen", av_conf, 3);
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
  
  //Serial.println(data);
  addAvemToDB(data);
}



void addAvemToDB(const char* string){
  Serial.print(string);
  /*DB = SD.open("TEST.TXT", FILE_WRITE);

  // if the file opened okay, write to it:
  if (DB) {     
    Serial.print(string);
    DB.println(string);
    // close the file:
    DB.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening ");

  }*/
}

/*void readFile(){
  DB = SD.open("TEST.TXT");
  if (DB) {
    // read from the file until there's nothing else in it:
    while (DB.available()) {
      Serial.write(DB.read());
    }
    // close the file:
    DB.close();
  } else {
    // if the file didn't open, print an error:
    //Serial.println("error opening test.txt");
  }
}*/


