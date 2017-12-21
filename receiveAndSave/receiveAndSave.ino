#define DEV 1
#include "avem.h"
#include <RCSwitch.h>
#include "helper.h"
#include "SDCardHelper.h"
#define RECEIVER_PIN 2

RCSwitch receiver = RCSwitch();
bool receiverIsActive = false;
bool sendIsActive =  false;
bool isProcessingTask = false;
bool isSdInitialized = false;

void setup() {
  // put your setup code here, to run once:
 delay(100);
 Serial.begin(115200);
 delay(100);
 receiver.enableReceive(RECEIVER_PIN);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  if(initSD()) {
    isSdInitialized = true;
    // ESP.restart();
  }
}

void loop() {
#ifdef DEV
  serialEvent();
#endif
  
  if (receiver.available()) {
    if(receiverIsActive && !isProcessingTask) {
      isProcessingTask = true;
      
      if(mainId > 0) {
        mainId++;
        
        Avem a(mainId, "test",  2, receiver.getReceivedValue(), receiver.getReceivedBitlength(), receiver.getReceivedDelay(),receiver.getReceivedProtocol());
        createAvemString(a);
      } else {
#ifdef DEV
        Serial.println("error Id to small");
#endif
      }
     
      isProcessingTask = false;
    }
    receiver.resetAvailable();
  }
}


#ifdef DEV
void serialEvent() {
  if(Serial.available()) {
    char ch = Serial.read();
    Serial.println(ch);
    if(!isProcessingTask){
      if(ch == 115) //s
      {
        receiverIsActive = true;
        sendIsActive = false;
      }
      else if(ch == 116) //t
      {
        receiverIsActive = false;
      }
      else if(ch == 109) //m
      {
        sendIsActive = true;
        receiverIsActive = false;
      }
      else if(ch == 111) // o
      {
        sendIsActive = false;
      }
    }
    
    if(sendIsActive && !isProcessingTask) {
      isProcessingTask = true;
      if(ch == 97) //a
      { 
        isProcessingTask = !readFile(2); //an
      }
      else if(ch == 98)//b 
      { 
       isProcessingTask = !readFile(3); //aus
      }
      isProcessingTask = false;
    }
  }
}
#endif

